mod ast;
mod ast_builder;
mod codegen;
mod comptime;
mod diagnostic;
mod jit;
mod parser;
mod shell_codegen;
mod shell_runtime;
mod smt;
mod typeck;
mod view_runtime;
mod verify;

use std::collections::HashMap;
use std::fs;
use std::path::PathBuf;

use anyhow::{Context, Result};
use clap::{Parser as ClapParser, Subcommand};
use colored::*;
use pest::Parser;

use parser::{BunkerParser, Rule};
use ast_builder::build_ast;
use codegen::Compiler;
use diagnostic::{Diagnostic, DiagnosticOutput, SourceLocation, codes, type_error_to_diagnostic, verify_error_to_diagnostic};

/// Output format for compiler diagnostics
#[derive(Clone, Copy, PartialEq, Eq, clap::ValueEnum)]
enum OutputFormat {
    /// Human-readable colored text (default)
    Text,
    /// Machine-readable JSON for AI feedback loops
    Json,
}

#[derive(ClapParser)]
#[command(name = "bunker")]
#[command(author = "Bunker Corporation")]
#[command(version = "0.1.0")]
#[command(about = "The Bunker Language Compiler", long_about = None)]
struct Cli {
    /// Output format for diagnostics
    #[arg(long, value_enum, default_value = "text", global = true)]
    format: OutputFormat,

    #[command(subcommand)]
    command: Commands,
}

#[derive(Subcommand)]
enum Commands {
    /// Build a .bkr file
    Build {
        /// The input file to compile
        #[arg(value_name = "FILE")]
        input: PathBuf,

        /// Output file path
        #[arg(short, long, value_name = "FILE")]
        output: Option<PathBuf>,

        /// Emit intermediate representation
        #[arg(long, value_name = "TYPE")]
        emit: Option<String>,

        /// Target profile (metal, performance, reactive, fortress)
        #[arg(long, default_value = "performance")]
        profile: String,

        /// Use Z3 SMT solver for contract verification (requires --features smt)
        #[arg(long)]
        smt: bool,
    },

    /// Check a .bkr file without compiling
    Check {
        /// The input file to check
        #[arg(value_name = "FILE")]
        input: PathBuf,

        /// Use Z3 SMT solver for contract verification (requires --features smt)
        #[arg(long)]
        smt: bool,
    },

    /// Parse and print the AST
    Parse {
        /// The input file to parse
        #[arg(value_name = "FILE")]
        input: PathBuf,
    },

    /// Run a `.bkr` file (Kernel JIT or Shell simulation)
    Run {
        /// The input file to run
        #[arg(value_name = "FILE")]
        input: PathBuf,

        /// Shell entry message (used when no Kernel `fn main() -> i32`)
        #[arg(long, default_value = "start")]
        message: String,

        /// Shell entry agent (optional)
        #[arg(long)]
        agent: Option<String>,

        /// Message args as `name=value` (repeatable)
        #[arg(long = "arg", value_name = "NAME=VALUE")]
        args: Vec<String>,

        /// Max Shell steps before aborting
        #[arg(long, default_value_t = 50_000)]
        max_steps: usize,
    },
}

fn main() -> Result<()> {
    let cli = Cli::parse();
    let format = cli.format;

    // Disable colored output when using JSON format
    if format == OutputFormat::Json {
        colored::control::set_override(false);
    }

    match cli.command {
        Commands::Build { input, output, emit, profile, smt } => {
            build_file(&input, output.as_deref(), emit.as_deref(), &profile, smt, format)
        }
        Commands::Check { input, smt } => check_file(&input, smt, format),
        Commands::Parse { input } => parse_file(&input, format),
        Commands::Run {
            input,
            message,
            agent,
            args,
            max_steps,
        } => run_file(&input, &message, agent.as_deref(), &args, max_steps, format),
    }
}

fn build_file(
    input: &PathBuf,
    output: Option<&std::path::Path>,
    emit: Option<&str>,
    _profile: &str,
    use_smt: bool,
    format: OutputFormat,
) -> Result<()> {
    let file_path = input.display().to_string();

    if format == OutputFormat::Text {
        println!("{} {}", "Compiling".green().bold(), input.display());
    }

    let source = match fs::read_to_string(input) {
        Ok(s) => s,
        Err(e) => {
            if format == OutputFormat::Json {
                let diag = Diagnostic::error(
                    codes::PARSE_ERROR,
                    format!("Failed to read file: {}", e),
                    SourceLocation::with_context(&file_path, "file read"),
                );
                let output = DiagnosticOutput::new(&file_path, vec![diag]);
                println!("{}", output.to_json());
                std::process::exit(1);
            }
            return Err(anyhow::anyhow!("Failed to read file: {}", e));
        }
    };

    let pairs = match BunkerParser::parse(Rule::file, &source) {
        Ok(p) => p,
        Err(e) => {
            if format == OutputFormat::Json {
                let diag = Diagnostic::error(
                    codes::PARSE_ERROR,
                    format!("Parse error: {}", e),
                    SourceLocation::with_context(&file_path, "parsing"),
                );
                let output = DiagnosticOutput::new(&file_path, vec![diag]);
                println!("{}", output.to_json());
                std::process::exit(1);
            }
            return Err(anyhow::anyhow!("Failed to parse file: {}", e));
        }
    };

    // Build the AST
    let file_pair = pairs.into_iter().next().unwrap();
    let mut ast = match build_ast(file_pair) {
        Ok(a) => a,
        Err(e) => {
            if format == OutputFormat::Json {
                let diag = Diagnostic::error(
                    codes::PARSE_ERROR,
                    format!("AST build error: {}", e),
                    SourceLocation::with_context(&file_path, "AST building"),
                );
                let output = DiagnosticOutput::new(&file_path, vec![diag]);
                println!("{}", output.to_json());
                std::process::exit(1);
            }
            return Err(anyhow::anyhow!("AST build error: {}", e));
        }
    };

    // Count what we have
    let kernel_count = ast.kernels.len();
    let shell_count = ast.shells.len();
    let view_count = ast.views.len();

    let fn_count: usize = ast.kernels.iter()
        .map(|k| k.items.iter().filter(|i| matches!(i, ast::KernelItem::Function(_) | ast::KernelItem::ComptimeFn(_))).count())
        .sum();

    let agent_count: usize = ast.shells.iter()
        .map(|s| s.agents.len())
        .sum();

    // Compile-time constant folding pass
    let comptime_stats = comptime::fold_comptime_calls(&mut ast);

    if emit == Some("ast") {
        println!("\n{}", "AST:".cyan().bold());
        println!("{:#?}", ast);
        return Ok(());
    }

    println!(
        "\n{} {} with {} kernel(s), {} shell(s), {} view(s)",
        "Parsed successfully:".green().bold(),
        input.file_name().unwrap().to_string_lossy(),
        kernel_count,
        shell_count,
        view_count
    );

    if kernel_count > 0 {
        println!("  {} function(s) in kernel", fn_count);
    }
    if shell_count > 0 {
        println!("  {} agent(s) in shell", agent_count);
    }
    if comptime_stats.calls_folded > 0 {
        println!(
            "  {} comptime call(s) folded at compile time",
            comptime_stats.calls_folded
        );
    }

    // Collect all diagnostics
    let mut diagnostics: Vec<Diagnostic> = Vec::new();

    // Type checking
    let type_errors = typeck::check_file(&ast)?;
    for err in &type_errors {
        diagnostics.push(type_error_to_diagnostic(err, &file_path));
    }

    // Contract verification (Kernel attributes) - verbose output
    let verify_errors = verify::verify_file_with_mode(&ast, use_smt, true)?;
    for err in &verify_errors {
        diagnostics.push(verify_error_to_diagnostic(err, &file_path));
    }

    // Output errors if any
    if !diagnostics.is_empty() {
        if format == OutputFormat::Json {
            let output = DiagnosticOutput::new(&file_path, diagnostics);
            println!("{}", output.to_json());
        } else {
            println!("\n{} {} error(s):\n", "Error:".red().bold(), diagnostics.len());
            for diag in &diagnostics {
                println!("  {} in {}", diag.message.red(),
                    diag.location.context.as_deref().unwrap_or("unknown"));
            }
        }
        std::process::exit(1);
    }

    // Code generation
    if kernel_count > 0 || shell_count > 0 {
        println!("\n{}", "Generating code...".cyan().bold());
        
        let mut compiler = Compiler::new()?;
        
        for kernel in &ast.kernels {
            compiler.compile_kernel(kernel)?;
        }
        
        for shell in &ast.shells {
            compiler.compile_shell(shell)?;
        }
        
        let object_code = compiler.finish()?;
        
        // Determine output path
        let output_path = if let Some(out) = output {
            out.to_path_buf()
        } else {
            input.with_extension("o")
        };
        
        fs::write(&output_path, &object_code)
            .with_context(|| format!("Failed to write output: {}", output_path.display()))?;
        
        println!(
            "{} {} ({} bytes)",
            "Generated:".green().bold(),
            output_path.display(),
            object_code.len()
        );
        
        // If output ends with .exe, try to link
        if output_path.extension().map(|e| e == "exe").unwrap_or(false) {
            println!(
                "\n{} To create an executable, link with your system linker:",
                "Note:".yellow().bold()
            );
            println!("  Windows: link /ENTRY:main {} /OUT:program.exe", output_path.display());
            println!("  Linux:   ld -o program {}", output_path.display());
        }
    } else {
        println!(
            "\n{} No kernel to compile (Shell/View-only file)",
            "Note:".yellow().bold()
        );
    }

    Ok(())
}

fn check_file(input: &PathBuf, use_smt: bool, format: OutputFormat) -> Result<()> {
    let file_path = input.display().to_string();

    if format == OutputFormat::Text {
        println!("{} {}", "Checking".blue().bold(), input.display());
    }

    let source = match fs::read_to_string(input) {
        Ok(s) => s,
        Err(e) => {
            if format == OutputFormat::Json {
                let diag = Diagnostic::error(
                    codes::PARSE_ERROR,
                    format!("Failed to read file: {}", e),
                    SourceLocation::with_context(&file_path, "file read"),
                );
                let output = DiagnosticOutput::new(&file_path, vec![diag]);
                println!("{}", output.to_json());
                std::process::exit(1);
            }
            return Err(anyhow::anyhow!("Failed to read file: {}", e));
        }
    };

    let pairs = match BunkerParser::parse(Rule::file, &source) {
        Ok(p) => p,
        Err(e) => {
            if format == OutputFormat::Json {
                let diag = Diagnostic::error(
                    codes::PARSE_ERROR,
                    format!("Parse error: {}", e),
                    SourceLocation::with_context(&file_path, "parsing"),
                );
                let output = DiagnosticOutput::new(&file_path, vec![diag]);
                println!("{}", output.to_json());
                std::process::exit(1);
            }
            return Err(anyhow::anyhow!("Failed to parse file: {}", e));
        }
    };

    // Build AST
    let file_pair = pairs.into_iter().next().unwrap();
    let mut ast = match build_ast(file_pair) {
        Ok(a) => a,
        Err(e) => {
            if format == OutputFormat::Json {
                let diag = Diagnostic::error(
                    codes::PARSE_ERROR,
                    format!("AST build error: {}", e),
                    SourceLocation::with_context(&file_path, "AST building"),
                );
                let output = DiagnosticOutput::new(&file_path, vec![diag]);
                println!("{}", output.to_json());
                std::process::exit(1);
            }
            return Err(anyhow::anyhow!("AST build error: {}", e));
        }
    };

    // Compile-time constant folding pass
    let comptime_stats = comptime::fold_comptime_calls(&mut ast);
    if format == OutputFormat::Text && comptime_stats.calls_folded > 0 {
        println!(
            "{} Folded {} comptime call(s)",
            "Comptime:".magenta().bold(),
            comptime_stats.calls_folded
        );
    }

    // Collect all diagnostics
    let mut diagnostics: Vec<Diagnostic> = Vec::new();

    // Type check
    let type_errors = typeck::check_file(&ast)?;
    for err in &type_errors {
        diagnostics.push(type_error_to_diagnostic(err, &file_path));
    }

    // Contract verification (Kernel attributes)
    let verify_errors = verify::verify_file_with_mode(&ast, use_smt, false)?;
    for err in &verify_errors {
        diagnostics.push(verify_error_to_diagnostic(err, &file_path));
    }

    // Output results
    if !diagnostics.is_empty() {
        if format == OutputFormat::Json {
            let output = DiagnosticOutput::new(&file_path, diagnostics);
            println!("{}", output.to_json());
        } else {
            println!("{} {} error(s) found:\n", "Error:".red().bold(), diagnostics.len());
            for diag in &diagnostics {
                println!("  {} in {}", diag.message.red(),
                    diag.location.context.as_deref().unwrap_or("unknown"));
            }
        }
        std::process::exit(1);
    }

    // Success
    if format == OutputFormat::Json {
        let output = DiagnosticOutput::new(&file_path, vec![]);
        println!("{}", output.to_json());
    } else {
        println!("{} No errors found.", "Success:".green().bold());
    }

    Ok(())
}

fn parse_file(input: &PathBuf, format: OutputFormat) -> Result<()> {
    if format == OutputFormat::Text {
        println!("{} {}\n", "Parsing".blue().bold(), input.display());
    }

    let source = fs::read_to_string(input)
        .with_context(|| format!("Failed to read file: {}", input.display()))?;

    print_ast(&source)?;
    Ok(())
}

fn parse_run_args(args: &[String]) -> Result<HashMap<String, String>> {
    let mut map = HashMap::new();
    for item in args {
        let (k, v) = item
            .split_once('=')
            .ok_or_else(|| anyhow::anyhow!("Invalid --arg value (expected name=value): {item}"))?;
        map.insert(k.trim().to_string(), v.trim().to_string());
    }
    Ok(map)
}

fn run_file(
    input: &PathBuf,
    message: &str,
    agent: Option<&str>,
    args: &[String],
    max_steps: usize,
    format: OutputFormat,
) -> Result<()> {
    let file_path = input.display().to_string();

    if format == OutputFormat::Text {
        println!("{} {}", "Running".cyan().bold(), input.display());
    }

    let source = match fs::read_to_string(input) {
        Ok(s) => s,
        Err(e) => {
            if format == OutputFormat::Json {
                let diag = Diagnostic::error(
                    codes::PARSE_ERROR,
                    format!("Failed to read file: {}", e),
                    SourceLocation::with_context(&file_path, "file read"),
                );
                let output = DiagnosticOutput::new(&file_path, vec![diag]);
                println!("{}", output.to_json());
                std::process::exit(1);
            }
            return Err(anyhow::anyhow!("Failed to read file: {}", e));
        }
    };

    let pairs = match BunkerParser::parse(Rule::file, &source) {
        Ok(p) => p,
        Err(e) => {
            if format == OutputFormat::Json {
                let diag = Diagnostic::error(
                    codes::PARSE_ERROR,
                    format!("Parse error: {}", e),
                    SourceLocation::with_context(&file_path, "parsing"),
                );
                let output = DiagnosticOutput::new(&file_path, vec![diag]);
                println!("{}", output.to_json());
                std::process::exit(1);
            }
            return Err(anyhow::anyhow!("Failed to parse file: {}", e));
        }
    };

    // Build AST
    let file_pair = pairs.into_iter().next().unwrap();
    let mut ast = match build_ast(file_pair) {
        Ok(a) => a,
        Err(e) => {
            if format == OutputFormat::Json {
                let diag = Diagnostic::error(
                    codes::PARSE_ERROR,
                    format!("AST build error: {}", e),
                    SourceLocation::with_context(&file_path, "AST building"),
                );
                let output = DiagnosticOutput::new(&file_path, vec![diag]);
                println!("{}", output.to_json());
                std::process::exit(1);
            }
            return Err(anyhow::anyhow!("AST build error: {}", e));
        }
    };

    // Compile-time constant folding pass
    let _comptime_stats = comptime::fold_comptime_calls(&mut ast);

    // Collect all diagnostics
    let mut diagnostics: Vec<Diagnostic> = Vec::new();

    // Type check (Kernel-only today)
    let type_errors = typeck::check_file(&ast)?;
    for err in &type_errors {
        diagnostics.push(type_error_to_diagnostic(err, &file_path));
    }

    // Contract verification (Kernel attributes)
    let verify_errors = verify::verify_file(&ast)?;
    for err in &verify_errors {
        diagnostics.push(verify_error_to_diagnostic(err, &file_path));
    }

    // Output errors if any
    if !diagnostics.is_empty() {
        if format == OutputFormat::Json {
            let output = DiagnosticOutput::new(&file_path, diagnostics);
            println!("{}", output.to_json());
        } else {
            println!("{} {} error(s) found:\n", "Error:".red().bold(), diagnostics.len());
            for diag in &diagnostics {
                println!("  {} in {}", diag.message.red(),
                    diag.location.context.as_deref().unwrap_or("unknown"));
            }
        }
        std::process::exit(1);
    }

    // Prefer Kernel entrypoint if present; otherwise, fall back to a Shell simulation.
    // Supported main() return types: i32, i64, f64, bool
    let has_kernel_main = ast.kernels.iter().any(|k| {
        k.items.iter().any(|item| match item {
            ast::KernelItem::Function(f) | ast::KernelItem::ComptimeFn(f) => {
                f.name == "main"
                    && f.params.is_empty()
                    && matches!(
                        f.return_type,
                        Some(ast::Type::I32 | ast::Type::I64 | ast::Type::F64 | ast::Type::Bool)
                    )
            }
            _ => false,
        })
    });

    let options = shell_runtime::RunOptions {
        entry_agent: agent.map(|s| s.to_string()),
        entry_message: message.to_string(),
        entry_args: parse_run_args(args)?,
        max_steps,
    };

    if has_kernel_main {
        let result = jit::run_kernel_main_flex(&ast)?;
        jit::reset_jit_arena(); // Clean up JIT allocations
        println!("{} {}", "Result:".green().bold(), result);
    } else if !ast.views.is_empty() {
        view_runtime::run(&ast, &options)?;
        jit::reset_jit_arena(); // Clean up any Shell→Kernel JIT allocations
    } else if !ast.shells.is_empty() {
        shell_runtime::run(&ast, &options)?;
        jit::reset_jit_arena(); // Clean up any Shell→Kernel JIT allocations
    } else {
        return Err(anyhow::anyhow!(
            "No runnable entrypoint found (expected Kernel `fn main() -> <i32|i64|f64|bool>` or a Shell handler for \"start\")"
        ));
    }
    Ok(())
}

fn print_ast(source: &str) -> Result<()> {
    let pairs = BunkerParser::parse(Rule::file, source)?;

    fn print_pair(pair: pest::iterators::Pair<Rule>, indent: usize) {
        let indent_str = "  ".repeat(indent);
        let rule = pair.as_rule();
        let span = pair.as_str();

        // Skip whitespace and comments
        if matches!(rule, Rule::WHITESPACE | Rule::COMMENT) {
            return;
        }

        // For simple tokens, show the value
        let display = if span.len() < 40 && !span.contains('\n') {
            format!("{:?} = {:?}", rule, span)
        } else {
            format!("{:?}", rule)
        };

        println!("{}{}", indent_str, display);

        for inner in pair.into_inner() {
            print_pair(inner, indent + 1);
        }
    }

    for pair in pairs {
        print_pair(pair, 0);
    }

    Ok(())
}
