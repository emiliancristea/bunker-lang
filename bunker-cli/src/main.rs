mod ast;
mod ast_builder;
mod builtins;
mod codegen;
mod comptime;
mod diagnostic;
mod jit;
mod parser;
mod shell_codegen;
mod shell_runtime;
mod smt;
mod typeck;
mod verify;
mod view_runtime;

use std::collections::{HashMap, HashSet};
use std::env;
use std::fs;
use std::path::{Path, PathBuf};
use std::time::{SystemTime, UNIX_EPOCH};

use anyhow::{Context, Result};
use clap::{Parser as ClapParser, Subcommand};
use colored::*;
use pest::Parser;
use serde::Serialize;

use ast_builder::build_ast;
use codegen::Compiler;
use diagnostic::{
    codes, parse_error_to_diagnostic, type_error_to_diagnostic_with_source,
    verify_error_to_diagnostic_with_source, Diagnostic, DiagnosticOutput, SourceLocation,
};
use parser::{BunkerParser, Rule};

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

    /// Check Bunker-written compiler sources and report self-hosting blockers
    SelfHostCheck {
        /// Directory containing Bunker self-hosting sources
        #[arg(value_name = "DIR", default_value = "self-host")]
        dir: PathBuf,

        /// Use Z3 SMT solver for contract verification (requires --features smt)
        #[arg(long)]
        smt: bool,
    },

    /// Compile a .bkr file through the Bunker-written compiler prototype
    SelfHostCompile {
        /// The Bunker source file to compile through self-host/bkrc.bkr
        #[arg(value_name = "FILE")]
        input: PathBuf,

        /// Output C file path
        #[arg(short, long, value_name = "FILE", default_value = "self_host_output.c")]
        output: PathBuf,

        /// Bunker-written compiler entrypoint
        #[arg(long, value_name = "FILE", default_value = "self-host/bkrc.bkr")]
        compiler: PathBuf,
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
        Commands::Build {
            input,
            output,
            emit,
            profile,
            smt,
        } => {
            github_actions_only("bunker build")?;
            build_file(
                &input,
                output.as_deref(),
                emit.as_deref(),
                &profile,
                smt,
                format,
            )
        }
        Commands::Check { input, smt } => check_file(&input, smt, format),
        Commands::Parse { input } => parse_file(&input, format),
        Commands::SelfHostCheck { dir, smt } => self_host_check(&dir, smt, format),
        Commands::SelfHostCompile {
            input,
            output,
            compiler,
        } => {
            github_actions_only("bunker self-host-compile")?;
            self_host_compile(&input, &output, &compiler, format)
        }
        Commands::Run {
            input,
            message,
            agent,
            args,
            max_steps,
        } => {
            github_actions_only("bunker run")?;
            run_file(&input, &message, agent.as_deref(), &args, max_steps, format)
        }
    }
}

fn github_actions_only(command: &str) -> Result<()> {
    if matches!(env::var("GITHUB_ACTIONS").as_deref(), Ok("true")) {
        return Ok(());
    }

    Err(anyhow::anyhow!(
        "{command} is disabled on local machines. Run build/run/self-host verification through GitHub Actions."
    ))
}

#[derive(Debug, Serialize)]
struct SelfHostFileReport {
    file: String,
    success: bool,
    diagnostics: Vec<Diagnostic>,
}

#[derive(Debug, Serialize)]
struct SelfHostSummary {
    total_files: usize,
    passing_files: usize,
    failing_files: usize,
    total_diagnostics: usize,
}

#[derive(Debug, Serialize)]
struct SelfHostReadinessReport {
    schema_version: String,
    directory: String,
    success: bool,
    can_continue_in_bunker: bool,
    summary: SelfHostSummary,
    files: Vec<SelfHostFileReport>,
    blockers: Vec<String>,
    ai_prompt_context: diagnostic::AiPromptContext,
}

#[derive(Debug, Serialize)]
struct SelfHostCompileReport {
    schema_version: String,
    success: bool,
    compiler: String,
    input: String,
    output: String,
    main_result: String,
    generated_bytes: usize,
}

struct CurrentDirGuard {
    previous: PathBuf,
}

impl CurrentDirGuard {
    fn change_to(next: &PathBuf) -> Result<Self> {
        let previous = env::current_dir().context("Failed to read current directory")?;
        env::set_current_dir(next)
            .with_context(|| format!("Failed to switch to {}", next.display()))?;
        Ok(Self { previous })
    }
}

impl Drop for CurrentDirGuard {
    fn drop(&mut self) {
        let _ = env::set_current_dir(&self.previous);
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
                let diag = parse_error_to_diagnostic(&e, &file_path, &source);
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

    let fn_count: usize = ast
        .kernels
        .iter()
        .map(|k| {
            k.items
                .iter()
                .filter(|i| {
                    matches!(
                        i,
                        ast::KernelItem::Function(_) | ast::KernelItem::ComptimeFn(_)
                    )
                })
                .count()
        })
        .sum();

    let agent_count: usize = ast.shells.iter().map(|s| s.agents.len()).sum();

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
        diagnostics.push(type_error_to_diagnostic_with_source(
            err,
            &file_path,
            Some(&source),
        ));
    }

    // Contract verification (Kernel attributes) - verbose output
    let verify_errors = verify::verify_file_with_mode(&ast, use_smt, true)?;
    for err in &verify_errors {
        diagnostics.push(verify_error_to_diagnostic_with_source(
            err,
            &file_path,
            Some(&source),
        ));
    }

    // Output errors if any
    if !diagnostics.is_empty() {
        if format == OutputFormat::Json {
            let output = DiagnosticOutput::new(&file_path, diagnostics);
            println!("{}", output.to_json());
        } else {
            println!(
                "\n{} {} error(s):\n",
                "Error:".red().bold(),
                diagnostics.len()
            );
            for diag in &diagnostics {
                println!(
                    "  {} in {}",
                    diag.message.red(),
                    diag.location.context.as_deref().unwrap_or("unknown")
                );
            }
        }
        std::process::exit(1);
    }

    typeck::lower_unit_enums(&mut ast);

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
            println!(
                "  Windows: link /ENTRY:main {} /OUT:program.exe",
                output_path.display()
            );
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
                let diag = parse_error_to_diagnostic(&e, &file_path, &source);
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
        diagnostics.push(type_error_to_diagnostic_with_source(
            err,
            &file_path,
            Some(&source),
        ));
    }

    // Contract verification (Kernel attributes)
    let verify_errors = verify::verify_file_with_mode(&ast, use_smt, false)?;
    for err in &verify_errors {
        diagnostics.push(verify_error_to_diagnostic_with_source(
            err,
            &file_path,
            Some(&source),
        ));
    }

    // Output results
    if !diagnostics.is_empty() {
        if format == OutputFormat::Json {
            let output = DiagnosticOutput::new(&file_path, diagnostics);
            println!("{}", output.to_json());
        } else {
            println!(
                "{} {} error(s) found:\n",
                "Error:".red().bold(),
                diagnostics.len()
            );
            for diag in &diagnostics {
                println!(
                    "  {} in {}",
                    diag.message.red(),
                    diag.location.context.as_deref().unwrap_or("unknown")
                );
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

fn collect_diagnostics_for_source(
    file_path: &str,
    source: &str,
    use_smt: bool,
) -> Result<Vec<Diagnostic>> {
    let pairs = match BunkerParser::parse(Rule::file, source) {
        Ok(pairs) => pairs,
        Err(err) => return Ok(vec![parse_error_to_diagnostic(&err, file_path, source)]),
    };

    let file_pair = pairs.into_iter().next().unwrap();
    let mut ast = match build_ast(file_pair) {
        Ok(ast) => ast,
        Err(err) => {
            return Ok(vec![Diagnostic::error(
                codes::PARSE_ERROR,
                format!("AST build error: {}", err),
                SourceLocation::with_context(file_path, "AST building"),
            )
            .with_ai_prompt_hint(
                "The parser accepted the file, but AST lowering failed. Repair syntax around the reported construct or reduce the file to isolate the unsupported grammar shape.",
            )]);
        }
    };

    let _comptime_stats = comptime::fold_comptime_calls(&mut ast);
    let mut diagnostics = Vec::new();

    let type_errors = typeck::check_file(&ast)?;
    for err in &type_errors {
        diagnostics.push(type_error_to_diagnostic_with_source(
            err,
            file_path,
            Some(source),
        ));
    }

    let verify_errors = verify::verify_file_with_mode(&ast, use_smt, false)?;
    for err in &verify_errors {
        diagnostics.push(verify_error_to_diagnostic_with_source(
            err,
            file_path,
            Some(source),
        ));
    }

    Ok(diagnostics)
}

fn self_host_check(dir: &PathBuf, use_smt: bool, format: OutputFormat) -> Result<()> {
    if format == OutputFormat::Text {
        println!(
            "{} {}",
            "Checking self-host sources in".blue().bold(),
            dir.display()
        );
    }

    let mut files: Vec<PathBuf> = fs::read_dir(dir)
        .with_context(|| format!("Failed to read self-host directory: {}", dir.display()))?
        .filter_map(|entry| entry.ok().map(|entry| entry.path()))
        .filter(|path| path.extension().map(|ext| ext == "bkr").unwrap_or(false))
        .collect();
    files.sort();

    let mut reports = Vec::new();
    let mut all_diagnostics = Vec::new();

    for path in files {
        let file_path = path.display().to_string();
        let diagnostics = match load_self_host_compiler_source(&path) {
            Ok(source) => collect_diagnostics_for_source(&file_path, &source, use_smt)?,
            Err(err) => vec![Diagnostic::error(
                codes::PARSE_ERROR,
                format!("Failed to read file: {}", err),
                SourceLocation::with_context(&file_path, "file read"),
            )
            .with_ai_prompt_hint(
                "The self-host checker could not read this file. Ensure the path exists and is readable before asking the agent to repair code.",
            )],
        };
        let success = diagnostics.is_empty();

        if format == OutputFormat::Text {
            if success {
                println!("  {} {}", "PASS".green(), file_path);
            } else {
                println!(
                    "  {} {} ({} diagnostic(s))",
                    "FAIL".red(),
                    file_path,
                    diagnostics.len()
                );
                if let Some(first) = diagnostics.first() {
                    println!("    {}", first.message.red());
                }
            }
        }

        all_diagnostics.extend(diagnostics.clone());
        reports.push(SelfHostFileReport {
            file: file_path,
            success,
            diagnostics,
        });
    }

    let total_files = reports.len();
    let passing_files = reports.iter().filter(|report| report.success).count();
    let failing_files = total_files.saturating_sub(passing_files);
    let total_diagnostics = all_diagnostics.len();
    let success = failing_files == 0;
    let blockers: Vec<String> = reports
        .iter()
        .filter(|report| !report.success)
        .filter_map(|report| {
            report
                .diagnostics
                .first()
                .map(|diag| format!("{}: {}", report.file, diag.message))
        })
        .collect();
    let ai_prompt_context =
        DiagnosticOutput::new(dir.display().to_string(), all_diagnostics).ai_prompt_context;

    let report = SelfHostReadinessReport {
        schema_version: "bunker.self_host_readiness.v1".to_string(),
        directory: dir.display().to_string(),
        success,
        can_continue_in_bunker: success,
        summary: SelfHostSummary {
            total_files,
            passing_files,
            failing_files,
            total_diagnostics,
        },
        files: reports,
        blockers,
        ai_prompt_context,
    };

    if format == OutputFormat::Json {
        println!("{}", serde_json::to_string_pretty(&report)?);
    } else {
        println!(
            "\n{} {}/{} file(s) passing, {} diagnostic(s)",
            if success {
                "Self-host readiness:".green().bold()
            } else {
                "Self-host readiness:".yellow().bold()
            },
            report.summary.passing_files,
            report.summary.total_files,
            report.summary.total_diagnostics
        );
        if success {
            println!(
                "{} All Bunker self-host sources pass current checks.",
                "Ready:".green().bold()
            );
        } else {
            println!(
                "{} Bunker self-host sources still need repair before the compiler can move further into .bkr.",
                "Blocked:".yellow().bold()
            );
        }
    }

    if !success {
        std::process::exit(1);
    }

    Ok(())
}

fn absolute_from_current(path: &PathBuf) -> Result<PathBuf> {
    if path.is_absolute() {
        Ok(path.clone())
    } else {
        Ok(env::current_dir()
            .context("Failed to read current directory")?
            .join(path))
    }
}

fn unique_self_host_temp_dir() -> PathBuf {
    let nanos = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .map(|duration| duration.as_nanos())
        .unwrap_or(0);
    env::temp_dir().join(format!(
        "bunker-self-host-compile-{}-{}",
        std::process::id(),
        nanos
    ))
}

fn cleanup_self_host_temp_dir(temp_dir: &PathBuf) {
    let _ = fs::remove_file(temp_dir.join("self_host_input.bkr"));
    let _ = fs::remove_file(temp_dir.join("self_host_output.c"));
    let _ = fs::remove_file(temp_dir.join("self_host_trace.enabled"));
    let _ = fs::remove_file(temp_dir.join("self_host_trace.log"));
    let _ = fs::remove_file(temp_dir.join("test.c"));
    let _ = fs::remove_dir(temp_dir);
}

fn build_ast_from_source_for_run(file_path: &str, source: &str) -> Result<ast::File> {
    let pairs = BunkerParser::parse(Rule::file, source)
        .with_context(|| format!("Failed to parse compiler source: {}", file_path))?;
    let file_pair = pairs.into_iter().next().unwrap();
    let mut ast = build_ast(file_pair)
        .map_err(|err| anyhow::anyhow!("AST build error in {}: {}", file_path, err))?;
    let _comptime_stats = comptime::fold_comptime_calls(&mut ast);
    Ok(ast)
}

fn print_diagnostics_and_exit(file_path: &str, diagnostics: Vec<Diagnostic>, format: OutputFormat) {
    if format == OutputFormat::Json {
        let output = DiagnosticOutput::new(file_path, diagnostics);
        println!("{}", output.to_json());
    } else {
        println!(
            "{} {} diagnostic(s) found in {}:\n",
            "Error:".red().bold(),
            diagnostics.len(),
            file_path
        );
        for diag in &diagnostics {
            println!("  [{}] {}", diag.error_code, diag.message.red());
        }
    }
    std::process::exit(1);
}

fn parse_self_host_import(line: &str) -> Option<String> {
    let trimmed = line.trim();
    let rest = trimmed.strip_prefix("import ")?;
    let rest = rest.trim();
    let quoted = rest.strip_suffix(';')?.trim();
    let path = quoted.strip_prefix('"')?.strip_suffix('"')?;
    if path.is_empty() {
        return None;
    }
    Some(path.to_string())
}

fn read_self_host_compiler_source(path: &Path, seen: &mut HashSet<PathBuf>) -> Result<String> {
    let canonical = fs::canonicalize(path)
        .with_context(|| format!("Failed to resolve compiler module: {}", path.display()))?;
    if !seen.insert(canonical.clone()) {
        return Ok(String::new());
    }

    let source = fs::read_to_string(&canonical)
        .with_context(|| format!("Failed to read compiler file: {}", canonical.display()))?;
    let base_dir = canonical.parent().unwrap_or_else(|| Path::new("."));
    let mut expanded = String::new();

    for line in source.lines() {
        if let Some(import_path) = parse_self_host_import(line) {
            let module_path = base_dir.join(import_path);
            expanded.push_str(&read_self_host_compiler_source(&module_path, seen)?);
            if !expanded.ends_with('\n') {
                expanded.push('\n');
            }
        } else {
            expanded.push_str(line);
            expanded.push('\n');
        }
    }

    Ok(expanded)
}

fn load_self_host_compiler_source(root: &Path) -> Result<String> {
    let mut seen = HashSet::new();
    read_self_host_compiler_source(root, &mut seen)
}

fn self_host_compile(
    input: &PathBuf,
    output: &PathBuf,
    compiler: &PathBuf,
    format: OutputFormat,
) -> Result<()> {
    let input_abs = absolute_from_current(input)?;
    let output_abs = absolute_from_current(output)?;
    let compiler_abs = absolute_from_current(compiler)?;

    // The compiler kernel runs from an isolated temp directory. Expand input
    // imports before execution so modular inputs do not depend on cwd layout.
    let input_source = load_self_host_compiler_source(&input_abs)
        .with_context(|| format!("Failed to load input file: {}", input_abs.display()))?;
    let compiler_source = load_self_host_compiler_source(&compiler_abs)?;
    let compiler_path = compiler_abs.display().to_string();

    if format == OutputFormat::Text {
        println!("[self-host] checking compiler source");
    }
    let diagnostics = collect_diagnostics_for_source(&compiler_path, &compiler_source, false)?;
    if !diagnostics.is_empty() {
        print_diagnostics_and_exit(&compiler_path, diagnostics, format);
    }

    if format == OutputFormat::Text {
        println!("[self-host] building compiler AST");
    }
    let ast = build_ast_from_source_for_run(&compiler_path, &compiler_source)?;
    let temp_dir = unique_self_host_temp_dir();
    fs::create_dir_all(&temp_dir)
        .with_context(|| format!("Failed to create temp directory: {}", temp_dir.display()))?;

    let temp_input = temp_dir.join("self_host_input.bkr");
    let temp_output = temp_dir.join("self_host_output.c");
    fs::write(&temp_input, input_source)
        .with_context(|| format!("Failed to write temp input: {}", temp_input.display()))?;
    if env::var_os("BUNKER_SELF_HOST_TRACE").is_some() {
        let trace_marker = temp_dir.join("self_host_trace.enabled");
        fs::write(&trace_marker, b"1")
            .with_context(|| format!("Failed to write trace marker: {}", trace_marker.display()))?;
        let trace_log = temp_dir.join("self_host_trace.log");
        fs::write(&trace_log, b"[self-host trace] rust:temp_ready\n")
            .with_context(|| format!("Failed to write trace log: {}", trace_log.display()))?;
    }

    if format == OutputFormat::Text {
        println!(
            "{} {} {} {}",
            "Self-host compiling".cyan().bold(),
            input_abs.display(),
            "with".cyan().bold(),
            compiler_abs.display()
        );
    }

    let main_result = {
        let _guard = CurrentDirGuard::change_to(&temp_dir)?;
        // Intentionally defer arena reset here: some large self-host inputs
        // currently hit allocator behavior at reset due oversized arena blocks
        // in long-running JIT compilation paths. Process exit will reclaim memory.
        if format == OutputFormat::Text {
            println!("[self-host] running compiler kernel");
        }
        jit::run_kernel_main_flex(&ast)?
    };

    let result_ok = matches!(
        main_result,
        jit::MainResult::I32(42) | jit::MainResult::I64(42)
    );
    if !result_ok {
        cleanup_self_host_temp_dir(&temp_dir);
        return Err(anyhow::anyhow!(
            "Bunker-written compiler returned {}, expected 42",
            main_result
        ));
    }

    if format == OutputFormat::Text {
        println!("[self-host] reading generated output");
    }
    let generated = fs::read_to_string(&temp_output).with_context(|| {
        format!(
            "Bunker-written compiler did not produce {}",
            temp_output.display()
        )
    })?;

    if let Some(parent) = output_abs
        .parent()
        .filter(|parent| !parent.as_os_str().is_empty())
    {
        fs::create_dir_all(parent)
            .with_context(|| format!("Failed to create output directory: {}", parent.display()))?;
    }
    fs::write(&output_abs, &generated)
        .with_context(|| format!("Failed to write output file: {}", output_abs.display()))?;

    let report = SelfHostCompileReport {
        schema_version: "bunker.self_host_compile.v1".to_string(),
        success: true,
        compiler: compiler_abs.display().to_string(),
        input: input_abs.display().to_string(),
        output: output_abs.display().to_string(),
        main_result: main_result.to_string(),
        generated_bytes: generated.len(),
    };

    cleanup_self_host_temp_dir(&temp_dir);

    if format == OutputFormat::Json {
        println!("{}", serde_json::to_string_pretty(&report)?);
    } else {
        println!(
            "{} wrote {} byte(s) to {}",
            "Success:".green().bold(),
            report.generated_bytes,
            output_abs.display()
        );
    }

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
                let diag = parse_error_to_diagnostic(&e, &file_path, &source);
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
        diagnostics.push(type_error_to_diagnostic_with_source(
            err,
            &file_path,
            Some(&source),
        ));
    }

    // Contract verification (Kernel attributes)
    let verify_errors = verify::verify_file(&ast)?;
    for err in &verify_errors {
        diagnostics.push(verify_error_to_diagnostic_with_source(
            err,
            &file_path,
            Some(&source),
        ));
    }

    // Output errors if any
    if !diagnostics.is_empty() {
        if format == OutputFormat::Json {
            let output = DiagnosticOutput::new(&file_path, diagnostics);
            println!("{}", output.to_json());
        } else {
            println!(
                "{} {} error(s) found:\n",
                "Error:".red().bold(),
                diagnostics.len()
            );
            for diag in &diagnostics {
                println!(
                    "  {} in {}",
                    diag.message.red(),
                    diag.location.context.as_deref().unwrap_or("unknown")
                );
            }
        }
        std::process::exit(1);
    }

    typeck::lower_unit_enums(&mut ast);

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
