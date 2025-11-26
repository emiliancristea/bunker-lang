mod ast;
mod ast_builder;
mod codegen;
mod parser;
mod shell_codegen;
mod typeck;

use std::fs;
use std::path::PathBuf;

use anyhow::{Context, Result};
use clap::{Parser as ClapParser, Subcommand};
use colored::*;
use pest::Parser;

use parser::{BunkerParser, Rule};
use ast_builder::build_ast;
use codegen::Compiler;

#[derive(ClapParser)]
#[command(name = "bunker")]
#[command(author = "Bunker Corporation")]
#[command(version = "0.1.0")]
#[command(about = "The Bunker Language Compiler", long_about = None)]
struct Cli {
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
    },

    /// Check a .bkr file without compiling
    Check {
        /// The input file to check
        #[arg(value_name = "FILE")]
        input: PathBuf,
    },

    /// Parse and print the AST
    Parse {
        /// The input file to parse
        #[arg(value_name = "FILE")]
        input: PathBuf,
    },
}

fn main() -> Result<()> {
    let cli = Cli::parse();

    match cli.command {
        Commands::Build { input, output, emit, profile } => {
            build_file(&input, output.as_deref(), emit.as_deref(), &profile)
        }
        Commands::Check { input } => check_file(&input),
        Commands::Parse { input } => parse_file(&input),
    }
}

fn build_file(
    input: &PathBuf,
    output: Option<&std::path::Path>,
    emit: Option<&str>,
    _profile: &str,
) -> Result<()> {
    println!("{} {}", "Compiling".green().bold(), input.display());

    let source = fs::read_to_string(input)
        .with_context(|| format!("Failed to read file: {}", input.display()))?;

    let pairs = BunkerParser::parse(Rule::file, &source)
        .with_context(|| format!("Failed to parse file: {}", input.display()))?;

    // Build the AST
    let file_pair = pairs.into_iter().next().unwrap();
    let ast = build_ast(file_pair)
        .map_err(|e| anyhow::anyhow!("AST build error: {}", e))?;

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

    // Type checking
    let type_errors = typeck::check_file(&ast)?;
    if !type_errors.is_empty() {
        println!("\n{} {} type error(s):\n", "Error:".red().bold(), type_errors.len());
        for err in &type_errors {
            println!("  {} in {}", err.message.red(), err.location);
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

fn check_file(input: &PathBuf) -> Result<()> {
    println!("{} {}", "Checking".blue().bold(), input.display());

    let source = fs::read_to_string(input)
        .with_context(|| format!("Failed to read file: {}", input.display()))?;

    let pairs = BunkerParser::parse(Rule::file, &source)
        .with_context(|| format!("Failed to parse file: {}", input.display()))?;

    // Build AST
    let file_pair = pairs.into_iter().next().unwrap();
    let ast = build_ast(file_pair)
        .map_err(|e| anyhow::anyhow!("AST build error: {}", e))?;

    // Type check
    let errors = typeck::check_file(&ast)?;
    
    if errors.is_empty() {
        println!("{} No errors found.", "Success:".green().bold());
    } else {
        println!("{} {} error(s) found:\n", "Error:".red().bold(), errors.len());
        for err in &errors {
            println!("  {} in {}", err.message.red(), err.location);
        }
        std::process::exit(1);
    }
    
    Ok(())
}

fn parse_file(input: &PathBuf) -> Result<()> {
    println!("{} {}\n", "Parsing".blue().bold(), input.display());

    let source = fs::read_to_string(input)
        .with_context(|| format!("Failed to read file: {}", input.display()))?;

    print_ast(&source)?;
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
