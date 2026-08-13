#[derive(Debug, Clone, PartialEq)]
pub struct File {
    pub kernels: Vec<Kernel>,
    pub shells: Vec<Shell>,
    pub views: Vec<View>,
}

// ====================
// KERNEL AST
// ====================

#[derive(Debug, Clone, PartialEq)]
pub struct Kernel {
    pub name: String,
    pub items: Vec<KernelItem>,
}

#[derive(Debug, Clone, PartialEq)]
pub enum KernelItem {
    Function(Function),
    Struct(StructDef),
    Enum(EnumDef),
    Const(ConstDef),
    ComptimeFn(Function),
}

#[derive(Debug, Clone, PartialEq)]
pub struct Function {
    pub name: String,
    pub attributes: Vec<Attribute>,
    pub params: Vec<Param>,
    pub return_type: Option<Type>,
    pub body: Block,
}

#[derive(Debug, Clone, PartialEq)]
pub struct StructDef {
    pub name: String,
    pub fields: Vec<StructField>,
}

#[derive(Debug, Clone, PartialEq)]
pub struct StructField {
    pub name: String,
    pub ty: Type,
}

#[derive(Debug, Clone, PartialEq)]
pub struct EnumVariantDecl {
    pub name: String,
    pub payload: Option<Type>,
}

#[derive(Debug, Clone, PartialEq)]
pub struct EnumDef {
    pub name: String,
    pub variants: Vec<EnumVariantDecl>,
}

impl EnumDef {
    pub fn variant_names(&self) -> Vec<String> {
        self.variants
            .iter()
            .map(|variant| variant.name.clone())
            .collect()
    }
}

#[derive(Debug, Clone, PartialEq)]
pub struct ConstDef {
    pub name: String,
    pub ty: Type,
    pub value: Expr,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Param {
    pub name: String,
    pub ty: Type,
}

#[derive(Debug, Clone, PartialEq)]
pub enum Attribute {
    Verified,
    UnsafeTrust,
    Requires(Expr),
    Ensures(Expr),
}

// ====================
// SHELL AST
// ====================

#[derive(Debug, Clone, PartialEq)]
pub struct Shell {
    pub name: String,
    pub imports: Vec<String>,
    pub agents: Vec<Agent>,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Agent {
    pub name: String,
    pub state: Vec<StateDecl>,
    pub handlers: Vec<MessageHandler>,
}

#[derive(Debug, Clone, PartialEq)]
pub struct StateDecl {
    pub name: String,
    pub value: Expr,
}

#[derive(Debug, Clone, PartialEq)]
pub struct MessageHandler {
    pub message: String,
    pub params: Vec<Param>,
    pub body: Block,
}

// ====================
// VIEW AST
// ====================

#[derive(Debug, Clone, PartialEq)]
pub struct View {
    pub name: String,
    pub components: Vec<Component>,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Component {
    pub target: Option<Target>,
    pub name: String,
    pub properties: Vec<Property>,
    pub children: Vec<Component>,
}

#[derive(Debug, Clone, PartialEq)]
pub enum Target {
    Graphics,
    Embedded,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Property {
    pub name: String,
    pub value: Expr,
}

// ====================
// STATEMENTS
// ====================

#[derive(Debug, Clone, PartialEq)]
pub struct Block {
    pub statements: Vec<Stmt>,
}

#[derive(Debug, Clone, PartialEq)]
pub enum Stmt {
    Let {
        name: String,
        ty: Option<Type>,
        value: Expr,
    },
    Assign {
        target: Expr,
        value: Expr,
    },
    Return(Option<Expr>),
    If {
        condition: Expr,
        then_block: Block,
        else_block: Option<Block>,
    },
    For {
        var: String,
        iter: Expr,
        body: Block,
    },
    While {
        condition: Expr,
        body: Block,
    },
    Loop(Block),
    Break,
    Continue,
    Match {
        expr: Expr,
        arms: Vec<MatchArm>,
    },
    Defer(Block),
    Send {
        message: Expr,
        target: String,
        args: Vec<(String, Expr)>,
    },
    Expr(Expr),
}

#[derive(Debug, Clone, PartialEq)]
pub struct MatchArm {
    pub pattern: Pattern,
    pub body: MatchBody,
}

#[derive(Debug, Clone, PartialEq)]
pub enum MatchBody {
    Expr(Expr),
    Block(Block),
}

#[derive(Debug, Clone, PartialEq)]
#[allow(dead_code)]
pub enum Pattern {
    Some(String),
    None,
    Bool(bool),
    Literal(Literal),
    Ident(String),
    EnumVariant {
        enum_name: String,
        variant: String,
        binding: Option<String>,
    },
    EnumPayload {
        tag: i64,
        binding: String,
    },
}

// ====================
// EXPRESSIONS
// ====================

#[derive(Debug, Clone, PartialEq)]
pub enum Expr {
    Literal(Literal),
    Ident(String),
    Binary {
        op: BinaryOp,
        left: Box<Expr>,
        right: Box<Expr>,
    },
    Unary {
        op: UnaryOp,
        expr: Box<Expr>,
    },
    Call {
        func: Box<Expr>,
        args: Vec<Expr>,
    },
    Index {
        expr: Box<Expr>,
        index: Box<Expr>,
    },
    Field {
        expr: Box<Expr>,
        field: String,
    },
    Use {
        path: Vec<String>,
        args: Vec<(String, Expr)>,
    },
    Send {
        message: Box<Expr>,
        target: Vec<String>,
        args: Vec<(String, Expr)>,
    },
    Lambda {
        params: Vec<Param>,
        body: Box<Expr>,
    },
    If {
        condition: Box<Expr>,
        then_expr: Box<Expr>,
        else_expr: Box<Expr>,
    },
    Match {
        expr: Box<Expr>,
        arms: Vec<MatchArm>,
    },
    Block(Block),
    Some(Box<Expr>),
    None,
    Array(Vec<Expr>),
    Struct {
        name: String,
        fields: Vec<(String, Expr)>,
    },
    Copy(Box<Expr>),
    /// Range expression: `start..end` (exclusive) or `start..=end` (inclusive)
    Range {
        start: Box<Expr>,
        end: Box<Expr>,
        inclusive: bool,
    },
    /// Type cast expression: `expr as Type`
    Cast {
        expr: Box<Expr>,
        target_type: Type,
    },
}

#[derive(Debug, Clone, PartialEq)]
pub enum Literal {
    Int(i64),
    Float(f64),
    String(String),
    Char(char),
    Bool(bool),
    HexColor(String),
}

#[derive(Debug, Clone, Copy, PartialEq)]
pub enum BinaryOp {
    Add,
    Sub,
    Mul,
    Div,
    Mod,
    Eq,
    Ne,
    Lt,
    Le,
    Gt,
    Ge,
    And,
    Or,
    BitAnd,
    BitOr,
    BitXor,
    Shl,
    Shr,
    As,
}

#[derive(Debug, Clone, Copy, PartialEq)]
pub enum UnaryOp {
    Neg,
    Not,
}

// ====================
// TYPES
// ====================

#[derive(Debug, Clone, PartialEq)]
pub enum Type {
    I32,
    I64,
    F32,
    F64,
    Bool,
    Str,
    Vec2,
    Vec3,
    Option(Box<Type>),
    Result(Box<Type>, Box<Type>),  // Result<T, E>
    Vec(Box<Type>),                // Vec<T> - dynamic array
    HashMap(Box<Type>, Box<Type>), // HashMap<K, V>
    Array(Box<Type>, usize),
    Ref { mutable: bool, ty: Box<Type> },
    Named(String),
}
