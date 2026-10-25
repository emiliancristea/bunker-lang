//! Multi-file module loader and dependency graph resolver for Bunker.
//!
//! Handles recursive import resolution, cycle detection, path validation,
//! duplicate suppression, and compilation unit merging for multi-file programs.

use serde::{Deserialize, Serialize};
use std::collections::HashSet;
use std::fs;
use std::path::{Path, PathBuf};

use crate::ast;
use crate::ast_builder::build_ast;
use crate::diagnostic::{codes, Diagnostic, SourceLocation};
use crate::parser::{BunkerParser, Rule};
use pest::Parser;

/// A single directed edge in the module import graph.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct ImportEdge {
    pub from: String,
    pub to: String,
    pub raw_import: String,
    pub status: String, // "ok", "missing", "invalid", "cycle", "duplicate"
    #[serde(skip_serializing_if = "Option::is_none")]
    pub detail: Option<String>,
}

/// The complete machine-readable import graph for the compilation unit.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct ImportGraph {
    pub schema_version: String,
    pub root: String,
    pub path_policy: String,
    pub base_directory_resolution: bool,
    pub recursive_expansion: bool,
    pub duplicate_suppression: bool,
    pub cycle_safe_expansion: bool,
    pub unique_import_count: usize,
    pub edge_count: usize,
    pub ok_edge_count: usize,
    pub missing_edge_count: usize,
    pub invalid_edge_count: usize,
    pub cycle_edge_count: usize,
    pub duplicate_edge_count: usize,
    pub duplicate_or_cycle_edge_count: usize,
    pub imports: Vec<String>,
    pub edges: Vec<ImportEdge>,
    pub has_duplicate_or_cycle_import: bool,
    pub has_invalid_import: bool,
    pub invalid_import: String,
    pub has_missing_import: bool,
    pub missing_import: String,
}

impl ImportGraph {
    pub fn to_json_comment(&self) -> String {
        let json = serde_json::to_string(self).unwrap_or_default();
        format!("/* BUNKER_IMPORT_GRAPH_JSON: {} */\n", json)
    }
}

/// Validates an import path against the Bunker normalized relative path policy.
pub fn validate_import_path(import_path: &str) -> Result<(), String> {
    if import_path.is_empty() {
        return Err("Import path cannot be empty".to_string());
    }
    if import_path.contains('\\') {
        return Err("Import path cannot contain backslashes; use forward slashes '/'".to_string());
    }
    if import_path.starts_with('/') || (import_path.len() >= 2 && import_path.as_bytes()[1] == b':') {
        return Err("Import path must be relative, not absolute".to_string());
    }
    if import_path.starts_with("./") {
        return Err("Import path should not have leading './'".to_string());
    }
    if import_path.ends_with('/') {
        return Err("Import path cannot have trailing '/'".to_string());
    }
    if import_path.contains("//") {
        return Err("Import path cannot contain empty '//' segments".to_string());
    }
    if import_path == ".."
        || import_path.starts_with("../")
        || import_path.ends_with("/..")
        || import_path.contains("/../")
    {
        return Err("Parent directory traversal '..' is not allowed in import paths".to_string());
    }
    Ok(())
}

fn normalize_slash(p: &Path) -> String {
    let s = p.to_string_lossy().replace('\\', "/");
    if let Some(rest) = s.strip_prefix("//?/") {
        rest.to_string()
    } else {
        s
    }
}

struct LoaderState {
    root_path: PathBuf,
    importer_stack: Vec<PathBuf>,
    loaded_files: HashSet<PathBuf>,
    unique_imports: Vec<String>,
    edges: Vec<ImportEdge>,
    ok_edge_count: usize,
    missing_edge_count: usize,
    invalid_edge_count: usize,
    cycle_edge_count: usize,
    duplicate_edge_count: usize,
    invalid_import: String,
    missing_import: String,
}

impl LoaderState {
    fn new(root: PathBuf) -> Self {
        Self {
            root_path: root,
            importer_stack: Vec::new(),
            loaded_files: HashSet::new(),
            unique_imports: Vec::new(),
            edges: Vec::new(),
            ok_edge_count: 0,
            missing_edge_count: 0,
            invalid_edge_count: 0,
            cycle_edge_count: 0,
            duplicate_edge_count: 0,
            invalid_import: String::new(),
            missing_import: String::new(),
        }
    }

    fn to_graph(&self) -> ImportGraph {
        let duplicate_or_cycle = self.duplicate_edge_count + self.cycle_edge_count;
        ImportGraph {
            schema_version: "bunker.import_graph.v1".to_string(),
            root: normalize_slash(&self.root_path),
            path_policy: "normalized_relative_forward_slash".to_string(),
            base_directory_resolution: true,
            recursive_expansion: true,
            duplicate_suppression: true,
            cycle_safe_expansion: true,
            unique_import_count: self.unique_imports.len(),
            edge_count: self.edges.len(),
            ok_edge_count: self.ok_edge_count,
            missing_edge_count: self.missing_edge_count,
            invalid_edge_count: self.invalid_edge_count,
            cycle_edge_count: self.cycle_edge_count,
            duplicate_edge_count: self.duplicate_edge_count,
            duplicate_or_cycle_edge_count: duplicate_or_cycle,
            imports: self.unique_imports.clone(),
            edges: self.edges.clone(),
            has_duplicate_or_cycle_import: duplicate_or_cycle > 0,
            has_invalid_import: !self.invalid_import.is_empty(),
            invalid_import: self.invalid_import.clone(),
            has_missing_import: !self.missing_import.is_empty(),
            missing_import: self.missing_import.clone(),
        }
    }
}

/// Recursively loads a Bunker file and all its imported dependencies, returning the
/// combined `ast::File` and the machine-readable `ImportGraph`.
pub fn load_file_and_imports(entry_path: &Path) -> Result<(ast::File, ImportGraph), Diagnostic> {
    let canonical_root = fs::canonicalize(entry_path).unwrap_or_else(|_| entry_path.to_path_buf());
    let mut state = LoaderState::new(canonical_root.clone());

    let combined_file = load_recursive(&canonical_root, &mut state)?;
    let graph = state.to_graph();

    Ok((combined_file, graph))
}

fn load_recursive(
    file_path: &Path,
    state: &mut LoaderState,
) -> Result<ast::File, Diagnostic> {
    state.importer_stack.push(file_path.to_path_buf());
    state.loaded_files.insert(file_path.to_path_buf());

    let source = fs::read_to_string(file_path).map_err(|err| {
        Diagnostic::error(
            codes::IMPORT_ERROR,
            format!("Failed to read file '{}': {}", file_path.display(), err),
            SourceLocation::with_context(normalize_slash(file_path), "file loading"),
        )
    })?;

    let pairs = BunkerParser::parse(Rule::file, &source).map_err(|err| {
        Diagnostic::error(
            codes::PARSE_ERROR,
            format!("Parse error in '{}': {}", file_path.display(), err),
            SourceLocation::with_context(normalize_slash(file_path), "parsing"),
        )
    })?;

    let file_pair = pairs.into_iter().next().unwrap();
    let mut ast = build_ast(file_pair).map_err(|err| {
        Diagnostic::error(
            codes::PARSE_ERROR,
            format!("AST build error in '{}': {}", file_path.display(), err),
            SourceLocation::with_context(normalize_slash(file_path), "AST building"),
        )
    })?;

    let base_dir = file_path.parent().unwrap_or_else(|| Path::new("."));

    // Extract imports from file level and kernel level
    let mut imports_to_process = Vec::new();
    for imp in &ast.imports {
        imports_to_process.push(imp.clone());
    }
    for kernel in &ast.kernels {
        for item in &kernel.items {
            if let ast::KernelItem::Import(imp) = item {
                imports_to_process.push(imp.clone());
            }
        }
    }

    let mut imported_files: Vec<ast::File> = Vec::new();

    for imp in imports_to_process {
        let from_str = normalize_slash(file_path);
        let raw_target = imp.target.clone();

        if !state.unique_imports.contains(&raw_target) {
            state.unique_imports.push(raw_target.clone());
        }

        if imp.is_path {
            if let Err(err_msg) = validate_import_path(&raw_target) {
                state.invalid_edge_count += 1;
                state.invalid_import = raw_target.clone();
                state.edges.push(ImportEdge {
                    from: from_str.clone(),
                    to: raw_target.clone(),
                    raw_import: raw_target.clone(),
                    status: "invalid".to_string(),
                    detail: Some(err_msg.clone()),
                });
                return Err(Diagnostic::error(
                    codes::IMPORT_INVALID_PATH,
                    format!("Invalid import path '{}': {}", raw_target, err_msg),
                    SourceLocation::with_context(from_str, "import path validation"),
                ));
            }

            let target_path = base_dir.join(&raw_target);
            if !target_path.exists() {
                state.missing_edge_count += 1;
                state.missing_import = raw_target.clone();
                state.edges.push(ImportEdge {
                    from: from_str.clone(),
                    to: normalize_slash(&target_path),
                    raw_import: raw_target.clone(),
                    status: "missing".to_string(),
                    detail: Some("File does not exist".to_string()),
                });
                return Err(Diagnostic::error(
                    codes::IMPORT_ERROR,
                    format!(
                        "Cannot find module '{}' imported from '{}'",
                        raw_target,
                        from_str
                    ),
                    SourceLocation::with_context(from_str, "import resolution"),
                ));
            }

            let canonical_target = fs::canonicalize(&target_path).unwrap_or(target_path);
            let to_str = normalize_slash(&canonical_target);

            // Cycle detection
            if state.importer_stack.contains(&canonical_target) {
                state.cycle_edge_count += 1;
                state.edges.push(ImportEdge {
                    from: from_str.clone(),
                    to: to_str.clone(),
                    raw_import: raw_target.clone(),
                    status: "cycle".to_string(),
                    detail: Some("Cyclic dependency detected".to_string()),
                });

                let mut cycle_chain: Vec<String> = state
                    .importer_stack
                    .iter()
                    .map(|p| p.file_name().unwrap_or_default().to_string_lossy().to_string())
                    .collect();
                cycle_chain.push(
                    canonical_target
                        .file_name()
                        .unwrap_or_default()
                        .to_string_lossy()
                        .to_string(),
                );

                return Err(Diagnostic::error(
                    codes::IMPORT_CYCLE,
                    format!(
                        "Cyclic dependency detected: {}",
                        cycle_chain.join(" -> ")
                    ),
                    SourceLocation::with_context(from_str, "cycle detection"),
                ));
            }

            // Duplicate suppression
            if state.loaded_files.contains(&canonical_target) {
                state.duplicate_edge_count += 1;
                state.edges.push(ImportEdge {
                    from: from_str,
                    to: to_str,
                    raw_import: raw_target,
                    status: "duplicate".to_string(),
                    detail: Some("Module already loaded; duplicate suppressed".to_string()),
                });
                continue;
            }

            // Normal valid load
            state.ok_edge_count += 1;
            state.edges.push(ImportEdge {
                from: from_str,
                to: to_str,
                raw_import: raw_target,
                status: "ok".to_string(),
                detail: None,
            });

            let sub_file = load_recursive(&canonical_target, state)?;
            imported_files.push(sub_file);
        } else {
            // Identifier import, e.g. import Helper;
            let candidate_path = base_dir.join(format!("{}.bkr", raw_target));
            if candidate_path.exists() {
                let canonical_target = fs::canonicalize(&candidate_path).unwrap_or(candidate_path);
                let to_str = normalize_slash(&canonical_target);

                if state.importer_stack.contains(&canonical_target) {
                    state.cycle_edge_count += 1;
                    return Err(Diagnostic::error(
                        codes::IMPORT_CYCLE,
                        format!("Cyclic dependency detected on module '{}'", raw_target),
                        SourceLocation::with_context(from_str, "cycle detection"),
                    ));
                }

                if state.loaded_files.contains(&canonical_target) {
                    state.duplicate_edge_count += 1;
                    continue;
                }

                state.ok_edge_count += 1;
                state.edges.push(ImportEdge {
                    from: from_str,
                    to: to_str,
                    raw_import: raw_target,
                    status: "ok".to_string(),
                    detail: None,
                });

                let sub_file = load_recursive(&canonical_target, state)?;
                imported_files.push(sub_file);
            }
        }
    }

    state.importer_stack.pop();

    // Merge imported files into the current AST
    for sub in imported_files {
        for kernel in sub.kernels {
            if !ast.kernels.iter().any(|k| k.name == kernel.name) {
                ast.kernels.push(kernel);
            }
        }
        for shell in sub.shells {
            if !ast.shells.iter().any(|s| s.name == shell.name) {
                ast.shells.push(shell);
            }
        }
        for view in sub.views {
            if !ast.views.iter().any(|v| v.name == view.name) {
                ast.views.push(view);
            }
        }
    }

    Ok(ast)
}
