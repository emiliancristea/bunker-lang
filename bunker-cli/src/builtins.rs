use crate::ast;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum BuiltinArgRule {
    Any,
    Str,
    Integer,
    StrOrArray,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct BuiltinParamSpec {
    pub rule: BuiltinArgRule,
    pub type_error: &'static str,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum RuntimeBuiltinType {
    I32,
    I64,
    Bool,
    Str,
}

impl RuntimeBuiltinType {
    pub fn to_ast_type(self) -> ast::Type {
        match self {
            Self::I32 => ast::Type::I32,
            Self::I64 => ast::Type::I64,
            Self::Bool => ast::Type::Bool,
            Self::Str => ast::Type::Str,
        }
    }
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum BuiltinReturnType {
    Runtime(RuntimeBuiltinType),
    ResultI64I64,
}

impl BuiltinReturnType {
    pub fn to_ast_type(self) -> ast::Type {
        match self {
            Self::Runtime(ty) => ty.to_ast_type(),
            Self::ResultI64I64 => {
                ast::Type::Result(Box::new(ast::Type::I64), Box::new(ast::Type::I64))
            }
        }
    }
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct TypecheckBuiltinSpec {
    pub name: &'static str,
    pub arity_error: &'static str,
    pub params: &'static [BuiltinParamSpec],
    pub return_type: BuiltinReturnType,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct RuntimeBuiltinSpec {
    pub name: &'static str,
    pub params: &'static [RuntimeBuiltinType],
    pub return_type: Option<RuntimeBuiltinType>,
}

static TYPECHECK_BUILTINS: &[TypecheckBuiltinSpec] = &[
    TypecheckBuiltinSpec {
        name: "strlen",
        arity_error: "strlen expects 1 argument",
        params: &[BuiltinParamSpec {
            rule: BuiltinArgRule::Str,
            type_error: "strlen expects str",
        }],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::I32),
    },
    TypecheckBuiltinSpec {
        name: "len",
        arity_error: "len expects 1 argument",
        params: &[BuiltinParamSpec {
            rule: BuiltinArgRule::StrOrArray,
            type_error: "len expects array or str",
        }],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::I32),
    },
    TypecheckBuiltinSpec {
        name: "read_file",
        arity_error: "read_file expects 1 argument",
        params: &[BuiltinParamSpec {
            rule: BuiltinArgRule::Str,
            type_error: "read_file expects str path",
        }],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::Str),
    },
    TypecheckBuiltinSpec {
        name: "write_file",
        arity_error: "write_file expects 2 arguments",
        params: &[
            BuiltinParamSpec {
                rule: BuiltinArgRule::Str,
                type_error: "write_file path must be str",
            },
            BuiltinParamSpec {
                rule: BuiltinArgRule::Str,
                type_error: "write_file content must be str",
            },
        ],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::Bool),
    },
    TypecheckBuiltinSpec {
        name: "file_exists",
        arity_error: "file_exists expects 1 argument",
        params: &[BuiltinParamSpec {
            rule: BuiltinArgRule::Str,
            type_error: "file_exists expects str path",
        }],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::Bool),
    },
    TypecheckBuiltinSpec {
        name: "char_at",
        arity_error: "char_at expects 2 arguments (string, index)",
        params: &[
            BuiltinParamSpec {
                rule: BuiltinArgRule::Str,
                type_error: "char_at expects str",
            },
            BuiltinParamSpec {
                rule: BuiltinArgRule::Integer,
                type_error: "char_at expects i64 index",
            },
        ],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::Str),
    },
    TypecheckBuiltinSpec {
        name: "substring",
        arity_error: "substring expects 3 arguments (string, start, end)",
        params: &[
            BuiltinParamSpec {
                rule: BuiltinArgRule::Str,
                type_error: "substring expects str",
            },
            BuiltinParamSpec {
                rule: BuiltinArgRule::Any,
                type_error: "",
            },
            BuiltinParamSpec {
                rule: BuiltinArgRule::Any,
                type_error: "",
            },
        ],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::Str),
    },
    TypecheckBuiltinSpec {
        name: "contains",
        arity_error: "contains expects 2 arguments (string, substring)",
        params: &[
            BuiltinParamSpec {
                rule: BuiltinArgRule::Str,
                type_error: "contains expects str",
            },
            BuiltinParamSpec {
                rule: BuiltinArgRule::Str,
                type_error: "contains expects str substring",
            },
        ],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::Bool),
    },
    TypecheckBuiltinSpec {
        name: "starts_with",
        arity_error: "starts_with expects 2 arguments (string, prefix)",
        params: &[
            BuiltinParamSpec {
                rule: BuiltinArgRule::Str,
                type_error: "starts_with expects str",
            },
            BuiltinParamSpec {
                rule: BuiltinArgRule::Str,
                type_error: "starts_with expects str prefix",
            },
        ],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::Bool),
    },
    TypecheckBuiltinSpec {
        name: "ends_with",
        arity_error: "ends_with expects 2 arguments (string, suffix)",
        params: &[
            BuiltinParamSpec {
                rule: BuiltinArgRule::Str,
                type_error: "ends_with expects str",
            },
            BuiltinParamSpec {
                rule: BuiltinArgRule::Str,
                type_error: "ends_with expects str suffix",
            },
        ],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::Bool),
    },
    TypecheckBuiltinSpec {
        name: "trim",
        arity_error: "trim expects 1 argument (string)",
        params: &[BuiltinParamSpec {
            rule: BuiltinArgRule::Str,
            type_error: "trim expects str",
        }],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::Str),
    },
    TypecheckBuiltinSpec {
        name: "parse_int",
        arity_error: "parse_int expects 1 argument (string)",
        params: &[BuiltinParamSpec {
            rule: BuiltinArgRule::Str,
            type_error: "parse_int expects str",
        }],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::I64),
    },
    TypecheckBuiltinSpec {
        name: "int_to_string",
        arity_error: "int_to_string expects 1 argument (integer)",
        params: &[BuiltinParamSpec {
            rule: BuiltinArgRule::Integer,
            type_error: "int_to_string expects i64 or i32",
        }],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::Str),
    },
    TypecheckBuiltinSpec {
        name: "char_code",
        arity_error: "char_code expects 1 argument (string)",
        params: &[BuiltinParamSpec {
            rule: BuiltinArgRule::Str,
            type_error: "char_code expects str",
        }],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::I64),
    },
    TypecheckBuiltinSpec {
        name: "char_code_at",
        arity_error: "char_code_at expects 2 arguments (string, index)",
        params: &[
            BuiltinParamSpec {
                rule: BuiltinArgRule::Str,
                type_error: "char_code_at expects str",
            },
            BuiltinParamSpec {
                rule: BuiltinArgRule::Integer,
                type_error: "char_code_at expects i64 index",
            },
        ],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::I64),
    },
    TypecheckBuiltinSpec {
        name: "from_char_code",
        arity_error: "from_char_code expects 1 argument (integer)",
        params: &[BuiltinParamSpec {
            rule: BuiltinArgRule::Integer,
            type_error: "from_char_code expects i64 or i32",
        }],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::Str),
    },
    TypecheckBuiltinSpec {
        name: "vec_new",
        arity_error: "vec_new expects 0 arguments",
        params: &[],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::I64),
    },
    TypecheckBuiltinSpec {
        name: "vec_push",
        arity_error: "vec_push expects 2 arguments (vec, value)",
        params: &[
            BuiltinParamSpec {
                rule: BuiltinArgRule::Any,
                type_error: "",
            },
            BuiltinParamSpec {
                rule: BuiltinArgRule::Any,
                type_error: "",
            },
        ],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::I64),
    },
    TypecheckBuiltinSpec {
        name: "vec_pop",
        arity_error: "vec_pop expects 1 argument (vec)",
        params: &[BuiltinParamSpec {
            rule: BuiltinArgRule::Any,
            type_error: "",
        }],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::I64),
    },
    TypecheckBuiltinSpec {
        name: "vec_len",
        arity_error: "vec_len expects 1 argument (vec)",
        params: &[BuiltinParamSpec {
            rule: BuiltinArgRule::Any,
            type_error: "",
        }],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::I64),
    },
    TypecheckBuiltinSpec {
        name: "vec_capacity",
        arity_error: "vec_capacity expects 1 argument (vec)",
        params: &[BuiltinParamSpec {
            rule: BuiltinArgRule::Any,
            type_error: "",
        }],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::I64),
    },
    TypecheckBuiltinSpec {
        name: "vec_get",
        arity_error: "vec_get expects 2 arguments (vec, index)",
        params: &[
            BuiltinParamSpec {
                rule: BuiltinArgRule::Any,
                type_error: "",
            },
            BuiltinParamSpec {
                rule: BuiltinArgRule::Any,
                type_error: "",
            },
        ],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::I64),
    },
    TypecheckBuiltinSpec {
        name: "vec_set",
        arity_error: "vec_set expects 3 arguments (vec, index, value)",
        params: &[
            BuiltinParamSpec {
                rule: BuiltinArgRule::Any,
                type_error: "",
            },
            BuiltinParamSpec {
                rule: BuiltinArgRule::Any,
                type_error: "",
            },
            BuiltinParamSpec {
                rule: BuiltinArgRule::Any,
                type_error: "",
            },
        ],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::Bool),
    },
    TypecheckBuiltinSpec {
        name: "vec_clear",
        arity_error: "vec_clear expects 1 argument (vec)",
        params: &[BuiltinParamSpec {
            rule: BuiltinArgRule::Any,
            type_error: "",
        }],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::I32),
    },
    TypecheckBuiltinSpec {
        name: "result_ok",
        arity_error: "result_ok expects 1 argument (value)",
        params: &[BuiltinParamSpec {
            rule: BuiltinArgRule::Any,
            type_error: "",
        }],
        return_type: BuiltinReturnType::ResultI64I64,
    },
    TypecheckBuiltinSpec {
        name: "result_err",
        arity_error: "result_err expects 1 argument (error)",
        params: &[BuiltinParamSpec {
            rule: BuiltinArgRule::Any,
            type_error: "",
        }],
        return_type: BuiltinReturnType::ResultI64I64,
    },
    TypecheckBuiltinSpec {
        name: "result_is_ok",
        arity_error: "result_is_ok expects 1 argument (result)",
        params: &[BuiltinParamSpec {
            rule: BuiltinArgRule::Any,
            type_error: "",
        }],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::Bool),
    },
    TypecheckBuiltinSpec {
        name: "result_is_err",
        arity_error: "result_is_err expects 1 argument (result)",
        params: &[BuiltinParamSpec {
            rule: BuiltinArgRule::Any,
            type_error: "",
        }],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::Bool),
    },
    TypecheckBuiltinSpec {
        name: "result_unwrap",
        arity_error: "result_unwrap expects 1 argument (result)",
        params: &[BuiltinParamSpec {
            rule: BuiltinArgRule::Any,
            type_error: "",
        }],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::I64),
    },
    TypecheckBuiltinSpec {
        name: "result_unwrap_err",
        arity_error: "result_unwrap_err expects 1 argument (result)",
        params: &[BuiltinParamSpec {
            rule: BuiltinArgRule::Any,
            type_error: "",
        }],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::I64),
    },
    TypecheckBuiltinSpec {
        name: "result_tag",
        arity_error: "result_tag expects 1 argument (result)",
        params: &[BuiltinParamSpec {
            rule: BuiltinArgRule::Any,
            type_error: "",
        }],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::I64),
    },
    TypecheckBuiltinSpec {
        name: "result_value",
        arity_error: "result_value expects 1 argument (result)",
        params: &[BuiltinParamSpec {
            rule: BuiltinArgRule::Any,
            type_error: "",
        }],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::I64),
    },
    TypecheckBuiltinSpec {
        name: "hashmap_new",
        arity_error: "hashmap_new expects 0 arguments",
        params: &[],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::I64),
    },
    TypecheckBuiltinSpec {
        name: "hashmap_insert",
        arity_error: "hashmap_insert expects 3 arguments (map, key, value)",
        params: &[
            BuiltinParamSpec {
                rule: BuiltinArgRule::Any,
                type_error: "",
            },
            BuiltinParamSpec {
                rule: BuiltinArgRule::Any,
                type_error: "",
            },
            BuiltinParamSpec {
                rule: BuiltinArgRule::Any,
                type_error: "",
            },
        ],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::Bool),
    },
    TypecheckBuiltinSpec {
        name: "hashmap_get",
        arity_error: "hashmap_get expects 2 arguments (map, key)",
        params: &[
            BuiltinParamSpec {
                rule: BuiltinArgRule::Any,
                type_error: "",
            },
            BuiltinParamSpec {
                rule: BuiltinArgRule::Any,
                type_error: "",
            },
        ],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::I64),
    },
    TypecheckBuiltinSpec {
        name: "hashmap_contains",
        arity_error: "hashmap_contains expects 2 arguments (map, key)",
        params: &[
            BuiltinParamSpec {
                rule: BuiltinArgRule::Any,
                type_error: "",
            },
            BuiltinParamSpec {
                rule: BuiltinArgRule::Any,
                type_error: "",
            },
        ],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::Bool),
    },
    TypecheckBuiltinSpec {
        name: "hashmap_remove",
        arity_error: "hashmap_remove expects 2 arguments (map, key)",
        params: &[
            BuiltinParamSpec {
                rule: BuiltinArgRule::Any,
                type_error: "",
            },
            BuiltinParamSpec {
                rule: BuiltinArgRule::Any,
                type_error: "",
            },
        ],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::Bool),
    },
    TypecheckBuiltinSpec {
        name: "hashmap_len",
        arity_error: "hashmap_len expects 1 argument (map)",
        params: &[BuiltinParamSpec {
            rule: BuiltinArgRule::Any,
            type_error: "",
        }],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::I64),
    },
    TypecheckBuiltinSpec {
        name: "hashmap_clear",
        arity_error: "hashmap_clear expects 1 argument (map)",
        params: &[BuiltinParamSpec {
            rule: BuiltinArgRule::Any,
            type_error: "",
        }],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::I32),
    },
    TypecheckBuiltinSpec {
        name: "hashmap_keys",
        arity_error: "hashmap_keys expects 1 argument (map)",
        params: &[BuiltinParamSpec {
            rule: BuiltinArgRule::Any,
            type_error: "",
        }],
        return_type: BuiltinReturnType::Runtime(RuntimeBuiltinType::I64),
    },
];

static RUNTIME_BUILTINS: &[RuntimeBuiltinSpec] = &[
    RuntimeBuiltinSpec {
        name: "read_file",
        params: &[RuntimeBuiltinType::Str],
        return_type: Some(RuntimeBuiltinType::Str),
    },
    RuntimeBuiltinSpec {
        name: "write_file",
        params: &[RuntimeBuiltinType::Str, RuntimeBuiltinType::Str],
        return_type: Some(RuntimeBuiltinType::Bool),
    },
    RuntimeBuiltinSpec {
        name: "file_exists",
        params: &[RuntimeBuiltinType::Str],
        return_type: Some(RuntimeBuiltinType::Bool),
    },
    RuntimeBuiltinSpec {
        name: "char_at",
        params: &[RuntimeBuiltinType::Str, RuntimeBuiltinType::I64],
        return_type: Some(RuntimeBuiltinType::Str),
    },
    RuntimeBuiltinSpec {
        name: "substring",
        params: &[
            RuntimeBuiltinType::Str,
            RuntimeBuiltinType::I64,
            RuntimeBuiltinType::I64,
        ],
        return_type: Some(RuntimeBuiltinType::Str),
    },
    RuntimeBuiltinSpec {
        name: "contains",
        params: &[RuntimeBuiltinType::Str, RuntimeBuiltinType::Str],
        return_type: Some(RuntimeBuiltinType::Bool),
    },
    RuntimeBuiltinSpec {
        name: "starts_with",
        params: &[RuntimeBuiltinType::Str, RuntimeBuiltinType::Str],
        return_type: Some(RuntimeBuiltinType::Bool),
    },
    RuntimeBuiltinSpec {
        name: "ends_with",
        params: &[RuntimeBuiltinType::Str, RuntimeBuiltinType::Str],
        return_type: Some(RuntimeBuiltinType::Bool),
    },
    RuntimeBuiltinSpec {
        name: "trim",
        params: &[RuntimeBuiltinType::Str],
        return_type: Some(RuntimeBuiltinType::Str),
    },
    RuntimeBuiltinSpec {
        name: "parse_int",
        params: &[RuntimeBuiltinType::Str],
        return_type: Some(RuntimeBuiltinType::I64),
    },
    RuntimeBuiltinSpec {
        name: "int_to_string",
        params: &[RuntimeBuiltinType::I64],
        return_type: Some(RuntimeBuiltinType::Str),
    },
    RuntimeBuiltinSpec {
        name: "char_code",
        params: &[RuntimeBuiltinType::Str],
        return_type: Some(RuntimeBuiltinType::I64),
    },
    RuntimeBuiltinSpec {
        name: "char_code_at",
        params: &[RuntimeBuiltinType::Str, RuntimeBuiltinType::I64],
        return_type: Some(RuntimeBuiltinType::I64),
    },
    RuntimeBuiltinSpec {
        name: "from_char_code",
        params: &[RuntimeBuiltinType::I64],
        return_type: Some(RuntimeBuiltinType::Str),
    },
    RuntimeBuiltinSpec {
        name: "str_eq",
        params: &[RuntimeBuiltinType::Str, RuntimeBuiltinType::Str],
        return_type: Some(RuntimeBuiltinType::Bool),
    },
    RuntimeBuiltinSpec {
        name: "vec_new",
        params: &[],
        return_type: Some(RuntimeBuiltinType::I64),
    },
    RuntimeBuiltinSpec {
        name: "vec_push",
        params: &[RuntimeBuiltinType::I64, RuntimeBuiltinType::I64],
        return_type: Some(RuntimeBuiltinType::I64),
    },
    RuntimeBuiltinSpec {
        name: "vec_pop",
        params: &[RuntimeBuiltinType::I64],
        return_type: Some(RuntimeBuiltinType::I64),
    },
    RuntimeBuiltinSpec {
        name: "vec_len",
        params: &[RuntimeBuiltinType::I64],
        return_type: Some(RuntimeBuiltinType::I64),
    },
    RuntimeBuiltinSpec {
        name: "vec_capacity",
        params: &[RuntimeBuiltinType::I64],
        return_type: Some(RuntimeBuiltinType::I64),
    },
    RuntimeBuiltinSpec {
        name: "vec_get",
        params: &[RuntimeBuiltinType::I64, RuntimeBuiltinType::I64],
        return_type: Some(RuntimeBuiltinType::I64),
    },
    RuntimeBuiltinSpec {
        name: "vec_set",
        params: &[
            RuntimeBuiltinType::I64,
            RuntimeBuiltinType::I64,
            RuntimeBuiltinType::I64,
        ],
        return_type: Some(RuntimeBuiltinType::Bool),
    },
    RuntimeBuiltinSpec {
        name: "vec_clear",
        params: &[RuntimeBuiltinType::I64],
        return_type: None,
    },
    RuntimeBuiltinSpec {
        name: "result_ok",
        params: &[RuntimeBuiltinType::I64],
        return_type: Some(RuntimeBuiltinType::I64),
    },
    RuntimeBuiltinSpec {
        name: "result_err",
        params: &[RuntimeBuiltinType::I64],
        return_type: Some(RuntimeBuiltinType::I64),
    },
    RuntimeBuiltinSpec {
        name: "result_is_ok",
        params: &[RuntimeBuiltinType::I64],
        return_type: Some(RuntimeBuiltinType::Bool),
    },
    RuntimeBuiltinSpec {
        name: "result_is_err",
        params: &[RuntimeBuiltinType::I64],
        return_type: Some(RuntimeBuiltinType::Bool),
    },
    RuntimeBuiltinSpec {
        name: "result_unwrap",
        params: &[RuntimeBuiltinType::I64],
        return_type: Some(RuntimeBuiltinType::I64),
    },
    RuntimeBuiltinSpec {
        name: "result_unwrap_err",
        params: &[RuntimeBuiltinType::I64],
        return_type: Some(RuntimeBuiltinType::I64),
    },
    RuntimeBuiltinSpec {
        name: "result_tag",
        params: &[RuntimeBuiltinType::I64],
        return_type: Some(RuntimeBuiltinType::I64),
    },
    RuntimeBuiltinSpec {
        name: "result_value",
        params: &[RuntimeBuiltinType::I64],
        return_type: Some(RuntimeBuiltinType::I64),
    },
    RuntimeBuiltinSpec {
        name: "hashmap_new",
        params: &[],
        return_type: Some(RuntimeBuiltinType::I64),
    },
    RuntimeBuiltinSpec {
        name: "hashmap_insert",
        params: &[
            RuntimeBuiltinType::I64,
            RuntimeBuiltinType::I64,
            RuntimeBuiltinType::I64,
        ],
        return_type: Some(RuntimeBuiltinType::Bool),
    },
    RuntimeBuiltinSpec {
        name: "hashmap_get",
        params: &[RuntimeBuiltinType::I64, RuntimeBuiltinType::I64],
        return_type: Some(RuntimeBuiltinType::I64),
    },
    RuntimeBuiltinSpec {
        name: "hashmap_contains",
        params: &[RuntimeBuiltinType::I64, RuntimeBuiltinType::I64],
        return_type: Some(RuntimeBuiltinType::Bool),
    },
    RuntimeBuiltinSpec {
        name: "hashmap_remove",
        params: &[RuntimeBuiltinType::I64, RuntimeBuiltinType::I64],
        return_type: Some(RuntimeBuiltinType::Bool),
    },
    RuntimeBuiltinSpec {
        name: "hashmap_len",
        params: &[RuntimeBuiltinType::I64],
        return_type: Some(RuntimeBuiltinType::I64),
    },
    RuntimeBuiltinSpec {
        name: "hashmap_clear",
        params: &[RuntimeBuiltinType::I64],
        return_type: None,
    },
    RuntimeBuiltinSpec {
        name: "hashmap_keys",
        params: &[RuntimeBuiltinType::I64],
        return_type: Some(RuntimeBuiltinType::I64),
    },
];

pub fn lookup_typecheck_builtin(name: &str) -> Option<&'static TypecheckBuiltinSpec> {
    TYPECHECK_BUILTINS.iter().find(|spec| spec.name == name)
}

pub fn lookup_runtime_builtin(name: &str) -> Option<&'static RuntimeBuiltinSpec> {
    RUNTIME_BUILTINS.iter().find(|spec| spec.name == name)
}

pub fn runtime_signature(name: &str) -> Option<(Vec<ast::Type>, Option<ast::Type>)> {
    lookup_runtime_builtin(name).map(|spec| {
        (
            spec.params.iter().map(|ty| ty.to_ast_type()).collect(),
            spec.return_type.map(RuntimeBuiltinType::to_ast_type),
        )
    })
}

pub fn infer_special_builtin_call_type(
    name: &str,
    arg_types: &[ast::Type],
    expected: Option<&ast::Type>,
) -> Option<ast::Type> {
    match name {
        "vec_new" => Some(match expected {
            Some(ast::Type::Vec(_)) => expected.cloned().unwrap_or(ast::Type::I64),
            _ => ast::Type::I64,
        }),
        "vec_get" | "vec_pop" => Some(match arg_types.first() {
            Some(ast::Type::Vec(elem)) => elem.as_ref().clone(),
            _ => ast::Type::I64,
        }),
        "hashmap_new" => Some(match expected {
            Some(ast::Type::HashMap(_, _)) => expected.cloned().unwrap_or(ast::Type::I64),
            _ => ast::Type::I64,
        }),
        "hashmap_get" => Some(match arg_types.first() {
            Some(ast::Type::HashMap(_, value)) => value.as_ref().clone(),
            _ => ast::Type::I64,
        }),
        "hashmap_keys" => Some(match arg_types.first() {
            Some(ast::Type::HashMap(key, _)) => ast::Type::Vec(Box::new(key.as_ref().clone())),
            _ => ast::Type::I64,
        }),
        "result_ok" => {
            let ok_ty = arg_types.first().cloned().unwrap_or(ast::Type::I64);
            let err_ty = match expected {
                Some(ast::Type::Result(_, err)) => err.as_ref().clone(),
                _ => ast::Type::I32,
            };
            Some(ast::Type::Result(Box::new(ok_ty), Box::new(err_ty)))
        }
        "result_err" => {
            let ok_ty = match expected {
                Some(ast::Type::Result(ok, _)) => ok.as_ref().clone(),
                _ => ast::Type::I32,
            };
            let err_ty = arg_types.first().cloned().unwrap_or(ast::Type::I64);
            Some(ast::Type::Result(Box::new(ok_ty), Box::new(err_ty)))
        }
        "result_unwrap" => Some(match arg_types.first() {
            Some(ast::Type::Result(ok, _)) => ok.as_ref().clone(),
            _ => ast::Type::I64,
        }),
        "result_unwrap_err" => Some(match arg_types.first() {
            Some(ast::Type::Result(_, err)) => err.as_ref().clone(),
            _ => ast::Type::I64,
        }),
        "result_value" => Some(match arg_types.first() {
            Some(ast::Type::Result(ok, err)) if ok == err => ok.as_ref().clone(),
            _ => ast::Type::I64,
        }),
        _ => None,
    }
}
