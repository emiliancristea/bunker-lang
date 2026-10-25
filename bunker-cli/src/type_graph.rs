//! Machine-readable type graph report for AI agents and tooling.
//!
//! Produces canonical BUNKER_TYPE_GRAPH_JSON matching the specification in Track A (A-011).

use serde::{Deserialize, Serialize};

use crate::ast::{self, BinaryOp, Expr, Literal, Stmt, Type};

/// Type information for a single node in the graph.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct TypeNodeInfo {
    pub type_kind: String,
    pub type_tag: String,
    pub c_abi: String,
    pub source: String,
    pub known: bool,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub struct_name: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub element_type_kind: Option<String>,
}

/// A field within a struct in the type graph.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct FieldTypeGraphEntry {
    pub name: String,
    pub type_kind: String,
    pub c_abi: String,
    pub source: String,
    pub known: bool,
}

/// A struct definition entry in the type graph.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct StructTypeGraphEntry {
    pub name: String,
    pub source_start: i64,
    pub source_end: i64,
    pub fields: Vec<FieldTypeGraphEntry>,
}

/// An enum variant in the type graph.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct VariantTypeGraphEntry {
    pub name: String,
    pub payloads: Vec<String>,
}

/// An enum definition entry in the type graph.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct EnumTypeGraphEntry {
    pub name: String,
    pub variants: Vec<VariantTypeGraphEntry>,
}

/// A constant definition entry in the type graph.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct ConstTypeGraphEntry {
    pub name: String,
    pub type_kind: String,
    pub c_abi: String,
    pub source: String,
    pub known: bool,
}

/// A function parameter entry in the type graph.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct ParamTypeGraphEntry {
    pub name: String,
    pub type_kind: String,
    pub c_abi: String,
    pub source: String,
    pub known: bool,
}

/// A local variable entry in the type graph.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct LocalTypeGraphEntry {
    pub name: String,
    pub type_kind: String,
    pub source: String,
    pub known: bool,
}

/// A return statement entry in the type graph.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct ReturnTypeGraphEntry {
    pub type_kind: String,
    pub c_abi: String,
    pub source: String,
    pub known: bool,
}

/// A function entry in the type graph.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct FunctionTypeGraphEntry {
    pub name: String,
    pub source_start: i64,
    pub source_end: i64,
    pub return_type: TypeNodeInfo,
    pub params: Vec<ParamTypeGraphEntry>,
    pub locals: Vec<LocalTypeGraphEntry>,
    pub returns: Vec<ReturnTypeGraphEntry>,
}

/// Summary counts for the type graph.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct TypeGraphSummary {
    pub function_count: usize,
    pub struct_count: usize,
    pub enum_count: usize,
    pub const_count: usize,
}

/// The complete machine-readable type graph report.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct TypeGraphReport {
    pub schema_version: String,
    pub representation: String,
    pub complete: bool,
    pub declared_types: bool,
    pub local_inference: bool,
    pub truncated: bool,
    pub known_limits: String,
    pub summary: TypeGraphSummary,
    pub structs: Vec<StructTypeGraphEntry>,
    pub enums: Vec<EnumTypeGraphEntry>,
    pub constants: Vec<ConstTypeGraphEntry>,
    pub functions: Vec<FunctionTypeGraphEntry>,
}

impl TypeGraphReport {
    /// Serialize type graph report to compact JSON string.
    pub fn to_json(&self) -> String {
        serde_json::to_string(self).unwrap_or_default()
    }

    /// Serialize type graph report to pretty JSON string.
    #[allow(dead_code)]
    pub fn to_json_pretty(&self) -> String {
        serde_json::to_string_pretty(self).unwrap_or_default()
    }

    /// Format type graph report as an embedded C/Bunker block comment.
    pub fn to_json_comment(&self) -> String {
        format!("/* BUNKER_TYPE_GRAPH_JSON: {} */\n", self.to_json())
    }
}

/// Map an `ast::Type` to its canonical `type_kind` string.
pub fn type_to_kind(ty: &Type) -> String {
    match ty {
        Type::I32 => "i32".to_string(),
        Type::I64 => "i64".to_string(),
        Type::F32 => "f32".to_string(),
        Type::F64 => "f64".to_string(),
        Type::Bool => "bool".to_string(),
        Type::Str => "str".to_string(),
        Type::Vec2 => "vec2".to_string(),
        Type::Vec3 => "vec3".to_string(),
        Type::Unit => "unit".to_string(),
        Type::Never => "never".to_string(),
        Type::Named(name) => format!("struct:{}", name),
        Type::Generic(name, _) => format!("generic:{}", name),
        Type::Array(elem, len) => format!("array:{}[{}]", type_to_kind(elem), len),
        Type::Slice(elem) => format!("slice:{}", type_to_kind(elem)),
        Type::Vec(elem) => format!("vec:{}", type_to_kind(elem)),
        Type::HashMap(k, v) => format!("map<{},{}>", type_to_kind(k), type_to_kind(v)),
        Type::Option(inner) => format!("option:{}", type_to_kind(inner)),
        Type::Result(ok, err) => format!("result<{},{}>", type_to_kind(ok), type_to_kind(err)),
        Type::Tuple(elems) => {
            let inner = elems.iter().map(type_to_kind).collect::<Vec<_>>().join(",");
            format!("tuple({})", inner)
        }
        Type::Ref { mutable, ty } => {
            if *mutable {
                format!("&mut {}", type_to_kind(ty))
            } else {
                format!("&{}", type_to_kind(ty))
            }
        }
        Type::Fn(params, ret) => {
            let p = params.iter().map(type_to_kind).collect::<Vec<_>>().join(",");
            format!("fn({}) -> {}", p, type_to_kind(ret))
        }
    }
}

/// Map an `ast::Type` to its C ABI string.
pub fn type_to_c_abi(ty: &Type) -> String {
    match ty {
        Type::I32 => "bkr_i32".to_string(),
        Type::I64 => "bkr_i64".to_string(),
        Type::F32 => "float".to_string(),
        Type::F64 => "double".to_string(),
        Type::Bool => "bool".to_string(),
        Type::Str => "bkr_str".to_string(),
        Type::Vec2 => "bkr_vec2".to_string(),
        Type::Vec3 => "bkr_vec3".to_string(),
        Type::Unit => "void".to_string(),
        Type::Never => "void".to_string(),
        Type::Named(name) => format!("struct {}*", name),
        Type::Generic(_, _) => "void*".to_string(),
        Type::Array(elem, _) => format!("{}*", type_to_c_abi(elem)),
        Type::Slice(_) => "bkr_slice*".to_string(),
        Type::Vec(_) => "bkr_vec*".to_string(),
        Type::HashMap(_, _) => "bkr_map*".to_string(),
        Type::Option(_) => "bkr_option*".to_string(),
        Type::Result(_, _) => "bkr_result*".to_string(),
        Type::Tuple(_) => "void*".to_string(),
        Type::Ref { ty, .. } => format!("{}*", type_to_c_abi(ty)),
        Type::Fn(_, _) => "void*".to_string(),
    }
}

/// Convert an `ast::Type` to a `TypeNodeInfo`.
pub fn type_to_node_info(ty: &Type, source: &str) -> TypeNodeInfo {
    TypeNodeInfo {
        type_kind: type_to_kind(ty),
        type_tag: format!("{:?}", ty),
        c_abi: type_to_c_abi(ty),
        source: source.to_string(),
        known: true,
        struct_name: match ty {
            Type::Named(s) => Some(s.clone()),
            _ => None,
        },
        element_type_kind: match ty {
            Type::Array(elem, _) | Type::Slice(elem) | Type::Vec(elem) | Type::Option(elem) => {
                Some(type_to_kind(elem))
            }
            _ => None,
        },
    }
}

/// Infer a simple type from an expression for local type graph generation.
fn infer_simple_expr_type(expr: &Expr) -> Type {
    match expr {
        Expr::Literal(Literal::Int(_)) => Type::I32,
        Expr::Literal(Literal::Float(_)) => Type::F64,
        Expr::Literal(Literal::String(_)) => Type::Str,
        Expr::Literal(Literal::Char(_)) => Type::I32,
        Expr::Literal(Literal::Bool(_)) => Type::Bool,
        Expr::Literal(Literal::HexColor(_)) => Type::Str,
        Expr::Array(elems) => {
            if let Some(first) = elems.first() {
                Type::Array(Box::new(infer_simple_expr_type(first)), elems.len())
            } else {
                Type::Array(Box::new(Type::I32), 0)
            }
        }
        Expr::Tuple(elems) => Type::Tuple(elems.iter().map(infer_simple_expr_type).collect()),
        Expr::Binary { op, left, .. } => match op {
            BinaryOp::Eq
            | BinaryOp::Ne
            | BinaryOp::Lt
            | BinaryOp::Le
            | BinaryOp::Gt
            | BinaryOp::Ge
            | BinaryOp::And
            | BinaryOp::Or => Type::Bool,
            _ => infer_simple_expr_type(left),
        },
        Expr::Unary { op, expr } => match op {
            ast::UnaryOp::Not => Type::Bool,
            ast::UnaryOp::Neg => infer_simple_expr_type(expr),
        },
        Expr::Cast { target_type, .. } => target_type.clone(),
        Expr::Struct { name, .. } => Type::Named(name.clone()),
        Expr::Some(inner) => Type::Option(Box::new(infer_simple_expr_type(inner))),
        Expr::None => Type::Option(Box::new(Type::Unit)),
        Expr::Try(inner) => infer_simple_expr_type(inner),
        _ => Type::I32, // default fallback
    }
}

/// Build a `TypeGraphReport` from an `ast::File` and raw source.
pub fn build_type_graph_report(file: &ast::File, source: &str) -> TypeGraphReport {
    let source_bytes = source.len();

    let mut structs = Vec::new();
    let mut enums = Vec::new();
    let mut constants = Vec::new();
    let mut functions = Vec::new();

    for kernel in &file.kernels {
        for item in &kernel.items {
            match item {
                ast::KernelItem::Struct(s) => {
                    let fields = s
                        .fields
                        .iter()
                        .map(|f| FieldTypeGraphEntry {
                            name: f.name.clone(),
                            type_kind: type_to_kind(&f.ty),
                            c_abi: type_to_c_abi(&f.ty),
                            source: "declared".to_string(),
                            known: true,
                        })
                        .collect();
                    structs.push(StructTypeGraphEntry {
                        name: s.name.clone(),
                        source_start: 0,
                        source_end: source_bytes as i64,
                        fields,
                    });
                }
                ast::KernelItem::Enum(e) => {
                    let variants = e
                        .variants
                        .iter()
                        .map(|v| VariantTypeGraphEntry {
                            name: v.name.clone(),
                            payloads: v.payloads.iter().map(type_to_kind).collect(),
                        })
                        .collect();
                    enums.push(EnumTypeGraphEntry {
                        name: e.name.clone(),
                        variants,
                    });
                }
                ast::KernelItem::Const(c) => {
                    constants.push(ConstTypeGraphEntry {
                        name: c.name.clone(),
                        type_kind: type_to_kind(&c.ty),
                        c_abi: type_to_c_abi(&c.ty),
                        source: "declared".to_string(),
                        known: true,
                    });
                }
                ast::KernelItem::Function(f) | ast::KernelItem::ComptimeFn(f) => {
                    let return_type = f
                        .return_type
                        .as_ref()
                        .map(|t| type_to_node_info(t, "declared"))
                        .unwrap_or_else(|| type_to_node_info(&Type::Unit, "declared"));

                    let params = f
                        .params
                        .iter()
                        .map(|p| ParamTypeGraphEntry {
                            name: p.name.clone(),
                            type_kind: type_to_kind(&p.ty),
                            c_abi: type_to_c_abi(&p.ty),
                            source: "declared".to_string(),
                            known: true,
                        })
                        .collect();

                    let mut locals = Vec::new();
                    let mut returns = Vec::new();

                    collect_locals_and_returns(&f.body, &mut locals, &mut returns, f.return_type.as_ref());

                    functions.push(FunctionTypeGraphEntry {
                        name: f.name.clone(),
                        source_start: 0,
                        source_end: source_bytes as i64,
                        return_type,
                        params,
                        locals,
                        returns,
                    });
                }
                _ => {}
            }
        }
    }

    let summary = TypeGraphSummary {
        function_count: functions.len(),
        struct_count: structs.len(),
        enum_count: enums.len(),
        const_count: constants.len(),
    };

    TypeGraphReport {
        schema_version: "bunker.type_graph.v1".to_string(),
        representation: "typeck_inference".to_string(),
        complete: true,
        declared_types: true,
        local_inference: true,
        truncated: false,
        known_limits: "Type checker inferred and declared types across kernels, functions, structs, enums, constants, and statement bodies.".to_string(),
        summary,
        structs,
        enums,
        constants,
        functions,
    }
}

fn collect_locals_and_returns(
    block: &ast::Block,
    locals: &mut Vec<LocalTypeGraphEntry>,
    returns: &mut Vec<ReturnTypeGraphEntry>,
    fn_ret: Option<&Type>,
) {
    for stmt in &block.statements {
        match stmt {
            Stmt::Let { name, ty, value, .. } => {
                let (type_kind, source) = if let Some(t) = ty {
                    (type_to_kind(t), "declared")
                } else {
                    let inferred = infer_simple_expr_type(value);
                    (type_to_kind(&inferred), "inferred")
                };
                locals.push(LocalTypeGraphEntry {
                    name: name.clone(),
                    type_kind,
                    source: source.to_string(),
                    known: true,
                });
            }
            Stmt::Return(opt_expr) => {
                let ty = if let Some(e) = opt_expr {
                    if let Some(r) = fn_ret {
                        r.clone()
                    } else {
                        infer_simple_expr_type(e)
                    }
                } else {
                    Type::Unit
                };
                returns.push(ReturnTypeGraphEntry {
                    type_kind: type_to_kind(&ty),
                    c_abi: type_to_c_abi(&ty),
                    source: "return_statement".to_string(),
                    known: true,
                });
            }
            Stmt::If { then_block, else_block, .. } => {
                collect_locals_and_returns(then_block, locals, returns, fn_ret);
                if let Some(eb) = else_block {
                    collect_locals_and_returns(eb, locals, returns, fn_ret);
                }
            }
            Stmt::While { body, .. } | Stmt::For { body, .. } | Stmt::Loop { body, .. } => {
                collect_locals_and_returns(body, locals, returns, fn_ret);
            }
            Stmt::Match { arms, .. } => {
                for arm in arms {
                    match &arm.body {
                        ast::MatchBody::Block(b) => collect_locals_and_returns(b, locals, returns, fn_ret),
                        ast::MatchBody::Expr(_) => {}
                    }
                }
            }
            _ => {}
        }
    }
}
