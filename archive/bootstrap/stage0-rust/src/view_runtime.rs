use std::collections::HashMap;
use std::io::{self, IsTerminal, Write};

use anyhow::{anyhow, Result};

use crate::ast;
use crate::shell_runtime::{RunOptions, ShellVm, Value};

#[derive(Debug, Clone)]
struct Button {
    id: usize,
    label: String,
    on_click: Option<ast::Expr>,
}

pub fn run(file: &ast::File, options: &RunOptions) -> Result<()> {
    let view = file
        .views
        .first()
        .ok_or_else(|| anyhow!("No View blocks found"))?;

    let mut vm = ShellVm::new(file, options.max_steps)?;

    // For View-driven runs, only enqueue the Shell entry message if it can be resolved.
    let entry_is_explicit = options.entry_agent.is_some()
        || !options.entry_args.is_empty()
        || options.entry_message != "start";
    let _ = vm.enqueue_entry(options, entry_is_explicit)?;
    let _ = vm.run_until_idle()?;

    let backend = std::env::var("BUNKER_VIEW_BACKEND").unwrap_or_else(|_| "auto".to_string());
    let interactive = io::stdin().is_terminal();

    let wants_graphics = match backend.as_str() {
        "graphics" => true,
        "text" => false,
        _ => view_has_graphics_target(view),
    };

    if wants_graphics {
        #[cfg(windows)]
        {
            // Move the VM into the GUI loop; it owns the event processing.
            return win32_graphics::run(view, vm, interactive);
        }
        #[cfg(not(windows))]
        {
            eprintln!("Warning: graphics View backend is only available on Windows; falling back to text.");
        }
    }

    if interactive {
        run_interactive(view, &mut vm)?;
    } else {
        run_demo(view, &mut vm)?;
    }

    Ok(())
}

fn view_has_graphics_target(view: &ast::View) -> bool {
    fn walk(component: &ast::Component) -> bool {
        if matches!(component.target, Some(ast::Target::Graphics)) {
            return true;
        }
        component.children.iter().any(walk)
    }

    view.components.iter().any(walk)
}

fn run_demo(view: &ast::View, vm: &mut ShellVm) -> Result<()> {
    println!("View: {}", view.name);
    let buttons = render_view(view, vm)?;

    if let Some(button) = buttons.first() {
        if let Some(expr) = &button.on_click {
            println!("\n[demo] click Button[{}]: {}", button.id, button.label);
            exec_view_action(expr, vm)?;
            let _ = vm.run_until_idle()?;
            println!("\n[demo] re-render");
            let _ = render_view(view, vm)?;
        }
    }

    Ok(())
}

fn run_interactive(view: &ast::View, vm: &mut ShellVm) -> Result<()> {
    loop {
        println!("\nView: {}", view.name);
        let buttons = render_view(view, vm)?;

        if buttons.is_empty() {
            println!("(no buttons) Type `quit` to exit.");
        } else {
            println!("Commands: `click <id|label>`, `quit`");
        }

        print!("view> ");
        io::stdout().flush().ok();

        let mut line = String::new();
        if io::stdin().read_line(&mut line)? == 0 {
            break;
        }
        let input = line.trim();
        if input.is_empty() {
            continue;
        }
        if matches!(input, "quit" | "exit") {
            break;
        }

        if let Some(rest) = input.strip_prefix("click ") {
            let rest = rest.trim();
            let button = if let Ok(id) = rest.parse::<usize>() {
                buttons.iter().find(|b| b.id == id).cloned()
            } else {
                buttons.iter().find(|b| b.label == rest).cloned()
            };

            let Some(button) = button else {
                println!("Unknown button: {rest}");
                continue;
            };

            let Some(expr) = &button.on_click else {
                println!("Button has no on_click handler.");
                continue;
            };

            exec_view_action(expr, vm)?;
            let _ = vm.run_until_idle()?;
            continue;
        }

        println!("Unknown command: {input}");
    }

    Ok(())
}

fn render_view(view: &ast::View, vm: &ShellVm) -> Result<Vec<Button>> {
    let mut buttons = Vec::new();
    for component in &view.components {
        render_component(component, vm, 0, &mut buttons)?;
    }
    Ok(buttons)
}

fn render_component(
    component: &ast::Component,
    vm: &ShellVm,
    depth: usize,
    buttons: &mut Vec<Button>,
) -> Result<()> {
    let indent = "  ".repeat(depth);
    match component.name.as_str() {
        "Window" => {
            let title =
                get_prop_string(component, "title", vm).unwrap_or_else(|| "Untitled".to_string());
            let width = get_prop_int(component, "width", vm).unwrap_or(0);
            let height = get_prop_int(component, "height", vm).unwrap_or(0);
            println!("{indent}Window \"{title}\" ({width}x{height})");
        }
        "Column" => {
            let spacing = get_prop_int(component, "spacing", vm);
            if let Some(s) = spacing {
                println!("{indent}Column (spacing: {s})");
            } else {
                println!("{indent}Column");
            }
        }
        "Row" => {
            let spacing = get_prop_int(component, "spacing", vm);
            if let Some(s) = spacing {
                println!("{indent}Row (spacing: {s})");
            } else {
                println!("{indent}Row");
            }
        }
        "Grid" => {
            let columns = get_prop_int(component, "columns", vm).unwrap_or(2);
            let spacing = get_prop_int(component, "spacing", vm);
            if let Some(s) = spacing {
                println!("{indent}Grid ({columns} cols, spacing: {s})");
            } else {
                println!("{indent}Grid ({columns} cols)");
            }
        }
        "Label" => {
            let text = get_prop_string(component, "text", vm).unwrap_or_default();
            println!("{indent}Label: {text}");
        }
        "Button" => {
            let label =
                get_prop_string(component, "text", vm).unwrap_or_else(|| "Button".to_string());
            let on_click = get_prop_expr(component, "on_click").cloned();
            let id = buttons.len();
            println!("{indent}Button[{id}]: {label}");
            buttons.push(Button {
                id,
                label,
                on_click,
            });
        }
        other => {
            println!("{indent}{other}");
        }
    }

    for child in &component.children {
        render_component(child, vm, depth + 1, buttons)?;
    }
    Ok(())
}

fn get_prop_expr<'a>(component: &'a ast::Component, name: &str) -> Option<&'a ast::Expr> {
    component
        .properties
        .iter()
        .find(|p| p.name == name)
        .map(|p| &p.value)
}

fn get_prop_string(component: &ast::Component, name: &str, vm: &ShellVm) -> Option<String> {
    let expr = get_prop_expr(component, name)?;
    let value = eval_view_expr(expr, vm).ok()?;
    Some(value.to_display_string())
}

fn get_prop_int(component: &ast::Component, name: &str, vm: &ShellVm) -> Option<i64> {
    let expr = get_prop_expr(component, name)?;
    let value = eval_view_expr(expr, vm).ok()?;
    match value {
        Value::Int(n) => Some(n),
        _ => None,
    }
}

fn exec_view_action(expr: &ast::Expr, vm: &mut ShellVm) -> Result<()> {
    match expr {
        ast::Expr::Send {
            message,
            target,
            args,
        } => {
            let msg_val = eval_view_expr(message, vm)?;
            let Value::Str(message) = msg_val else {
                return Err(anyhow!(
                    "View send message must be a string, got {msg_val:?}"
                ));
            };

            let agent = resolve_target_agent(target, vm.shell_name())?;

            let mut evaluated_args = HashMap::new();
            for (name, expr) in args {
                evaluated_args.insert(name.clone(), eval_view_expr(expr, vm)?);
            }

            vm.enqueue_message(&agent, &message, evaluated_args);
            Ok(())
        }
        other => Err(anyhow!("Unsupported view action: {other:?}")),
    }
}

fn resolve_target_agent(path: &[String], shell_name: &str) -> Result<String> {
    match path {
        [agent] => Ok(agent.clone()),
        [shell, agent] if shell == shell_name => Ok(agent.clone()),
        [shell, _agent] => Err(anyhow!(
            "View target shell '{}' does not match active shell '{}'",
            shell,
            shell_name
        )),
        other if !other.is_empty() => Ok(other[other.len() - 1].clone()),
        _ => Err(anyhow!("View send target cannot be empty")),
    }
}

fn eval_view_expr(expr: &ast::Expr, vm: &ShellVm) -> Result<Value> {
    match expr {
        ast::Expr::Literal(lit) => Ok(match lit {
            ast::Literal::Int(n) => Value::Int(*n),
            ast::Literal::Float(f) => Value::Float(*f),
            ast::Literal::String(s) => Value::Str(s.clone()),
            ast::Literal::Bool(b) => Value::Bool(*b),
            ast::Literal::Char(c) => Value::Int(*c as i64),
            ast::Literal::HexColor(s) => Value::Str(s.clone()),
        }),
        ast::Expr::Binary { op, left, right } => {
            let left_val = eval_view_expr(left, vm)?;
            let right_val = eval_view_expr(right, vm)?;
            eval_binary(*op, left_val, right_val)
        }
        ast::Expr::Unary { op, expr } => {
            let val = eval_view_expr(expr, vm)?;
            eval_unary(*op, val)
        }
        ast::Expr::Ident(name) => Err(anyhow!("Unbound identifier in view: {}", name)),
        ast::Expr::Field { .. } => eval_view_binding(expr, vm),
        ast::Expr::If {
            condition,
            then_expr,
            else_expr,
        } => {
            let cond = eval_view_expr(condition, vm)?.as_bool()?;
            if cond {
                eval_view_expr(then_expr, vm)
            } else {
                eval_view_expr(else_expr, vm)
            }
        }
        ast::Expr::Block(block) => eval_view_block(block, vm),
        other => Err(anyhow!("Unsupported view expression: {other:?}")),
    }
}

fn eval_view_block(block: &ast::Block, vm: &ShellVm) -> Result<Value> {
    let mut last = None;
    for stmt in &block.statements {
        match stmt {
            ast::Stmt::Expr(expr) => {
                last = Some(eval_view_expr(expr, vm)?);
            }
            other => {
                return Err(anyhow!("Unsupported view statement in block: {other:?}"));
            }
        }
    }
    last.ok_or_else(|| anyhow!("Block expression must yield a value"))
}

fn eval_view_binding(expr: &ast::Expr, vm: &ShellVm) -> Result<Value> {
    let mut parts = Vec::new();
    if collect_field_chain(expr, &mut parts).is_none() {
        return Err(anyhow!("Unsupported view field expression: {expr:?}"));
    }

    match parts.as_slice() {
        [shell, agent, key] if shell == vm.shell_name() => vm
            .get_agent_state_value(agent, key)
            .ok_or_else(|| anyhow!("Unknown binding: {}.{}.{}", shell, agent, key)),
        [agent, key] => vm
            .get_agent_state_value(agent, key)
            .ok_or_else(|| anyhow!("Unknown binding: {}.{}", agent, key)),
        _ => Err(anyhow!("Unsupported binding path: {}", parts.join("."))),
    }
}

fn collect_field_chain(expr: &ast::Expr, parts: &mut Vec<String>) -> Option<()> {
    match expr {
        ast::Expr::Ident(name) => {
            parts.push(name.clone());
            Some(())
        }
        ast::Expr::Field { expr, field } => {
            collect_field_chain(expr, parts)?;
            parts.push(field.clone());
            Some(())
        }
        _ => None,
    }
}

fn eval_unary(op: ast::UnaryOp, val: Value) -> Result<Value> {
    match op {
        ast::UnaryOp::Neg => match val {
            Value::Int(n) => Ok(Value::Int(-n)),
            Value::Float(f) => Ok(Value::Float(-f)),
            other => Err(anyhow!("Cannot negate {other:?}")),
        },
        ast::UnaryOp::Not => Ok(Value::Bool(!val.as_bool()?)),
    }
}

fn eval_binary(op: ast::BinaryOp, left: Value, right: Value) -> Result<Value> {
    use ast::BinaryOp as Op;

    match op {
        Op::Add => match (left, right) {
            (Value::Int(a), Value::Int(b)) => Ok(Value::Int(a + b)),
            (Value::Float(a), Value::Float(b)) => Ok(Value::Float(a + b)),
            (Value::Str(a), Value::Str(b)) => Ok(Value::Str(a + &b)),
            (Value::Str(a), b) => Ok(Value::Str(a + &b.to_display_string())),
            (a, Value::Str(b)) => Ok(Value::Str(a.to_display_string() + &b)),
            (a, b) => Err(anyhow!("Cannot add {a:?} and {b:?}")),
        },
        Op::Sub => match (left, right) {
            (Value::Int(a), Value::Int(b)) => Ok(Value::Int(a - b)),
            (Value::Float(a), Value::Float(b)) => Ok(Value::Float(a - b)),
            (a, b) => Err(anyhow!("Cannot subtract {a:?} and {b:?}")),
        },
        Op::Mul => match (left, right) {
            (Value::Int(a), Value::Int(b)) => Ok(Value::Int(a * b)),
            (Value::Float(a), Value::Float(b)) => Ok(Value::Float(a * b)),
            (a, b) => Err(anyhow!("Cannot multiply {a:?} and {b:?}")),
        },
        Op::Div => match (left, right) {
            (Value::Int(a), Value::Int(b)) => Ok(Value::Int(a / b)),
            (Value::Float(a), Value::Float(b)) => Ok(Value::Float(a / b)),
            (a, b) => Err(anyhow!("Cannot divide {a:?} and {b:?}")),
        },
        Op::Eq => Ok(Value::Bool(left == right)),
        Op::Ne => Ok(Value::Bool(left != right)),
        Op::Lt | Op::Le | Op::Gt | Op::Ge => {
            let (a, b) = match (left, right) {
                (Value::Int(a), Value::Int(b)) => (a as f64, b as f64),
                (Value::Float(a), Value::Float(b)) => (a, b),
                (a, b) => return Err(anyhow!("Cannot compare {a:?} and {b:?}")),
            };
            Ok(Value::Bool(match op {
                Op::Lt => a < b,
                Op::Le => a <= b,
                Op::Gt => a > b,
                Op::Ge => a >= b,
                _ => false,
            }))
        }
        Op::And => Ok(Value::Bool(left.as_bool()? && right.as_bool()?)),
        Op::Or => Ok(Value::Bool(left.as_bool()? || right.as_bool()?)),
        Op::Mod => match (left, right) {
            (Value::Int(a), Value::Int(b)) => Ok(Value::Int(a % b)),
            (a, b) => Err(anyhow!("Cannot mod {a:?} and {b:?}")),
        },
        Op::BitAnd => match (left, right) {
            (Value::Int(a), Value::Int(b)) => Ok(Value::Int(a & b)),
            (a, b) => Err(anyhow!("Cannot bitwise AND {a:?} and {b:?}")),
        },
        Op::BitOr => match (left, right) {
            (Value::Int(a), Value::Int(b)) => Ok(Value::Int(a | b)),
            (a, b) => Err(anyhow!("Cannot bitwise OR {a:?} and {b:?}")),
        },
        Op::BitXor => match (left, right) {
            (Value::Int(a), Value::Int(b)) => Ok(Value::Int(a ^ b)),
            (a, b) => Err(anyhow!("Cannot bitwise XOR {a:?} and {b:?}")),
        },
        Op::Shl => match (left, right) {
            (Value::Int(a), Value::Int(b)) => Ok(Value::Int(a << b)),
            (a, b) => Err(anyhow!("Cannot shift left {a:?} by {b:?}")),
        },
        Op::Shr => match (left, right) {
            (Value::Int(a), Value::Int(b)) => Ok(Value::Int(a >> b)),
            (a, b) => Err(anyhow!("Cannot shift right {a:?} by {b:?}")),
        },
        Op::As => Ok(left),
    }
}

#[cfg(windows)]
#[allow(
    dead_code,
    non_camel_case_types,
    non_snake_case,
    clippy::needless_lifetimes,
    clippy::upper_case_acronyms
)]
mod win32_graphics {
    use std::ffi::c_void;

    use anyhow::{anyhow, Result};

    use super::ShellVm;
    use super::{
        ast, eval_view_expr, exec_view_action, get_prop_expr, get_prop_int, get_prop_string,
    };

    // ==========================================================================
    // Layout System
    // ==========================================================================

    /// Rectangle representing a component's position and size.
    #[derive(Debug, Clone, Copy)]
    struct LayoutRect {
        x: i32,
        y: i32,
        width: i32,
        height: i32,
    }

    /// Default heights for leaf components.
    const LABEL_HEIGHT: i32 = 28;
    const BUTTON_HEIGHT: i32 = 32;
    const DEFAULT_SPACING: i32 = 8;
    const DEFAULT_PADDING: i32 = 10;

    /// Estimate the height of a component for vertical layout.
    fn estimate_height(component: &ast::Component) -> i32 {
        match component.name.as_str() {
            "Label" => LABEL_HEIGHT,
            "Button" => BUTTON_HEIGHT,
            "Row" => {
                // Row height is the max height of its children
                component
                    .children
                    .iter()
                    .map(estimate_height)
                    .max()
                    .unwrap_or(BUTTON_HEIGHT)
            }
            "Column" => {
                // Column height is sum of children + spacing
                let child_heights: i32 = component.children.iter().map(estimate_height).sum();
                let spacing = DEFAULT_SPACING * (component.children.len() as i32 - 1).max(0);
                child_heights + spacing
            }
            "Grid" => {
                // Estimate grid height based on rows
                let columns = 2; // Default columns
                let rows = (component.children.len() as i32 + columns - 1) / columns;
                rows * BUTTON_HEIGHT + DEFAULT_SPACING * (rows - 1).max(0)
            }
            _ => BUTTON_HEIGHT,
        }
    }

    /// Layout children vertically (Column layout).
    fn layout_column(
        component: &ast::Component,
        available: LayoutRect,
        vm: &ShellVm,
    ) -> Vec<LayoutRect> {
        let spacing =
            get_prop_int(component, "spacing", vm).unwrap_or(DEFAULT_SPACING as i64) as i32;
        let padding =
            get_prop_int(component, "padding", vm).unwrap_or(DEFAULT_PADDING as i64) as i32;

        let mut y = available.y + padding;
        let child_width = available.width - 2 * padding;

        component
            .children
            .iter()
            .map(|child| {
                let height = estimate_height(child);
                let rect = LayoutRect {
                    x: available.x + padding,
                    y,
                    width: child_width,
                    height,
                };
                y += height + spacing;
                rect
            })
            .collect()
    }

    /// Layout children horizontally (Row layout).
    fn layout_row(
        component: &ast::Component,
        available: LayoutRect,
        vm: &ShellVm,
    ) -> Vec<LayoutRect> {
        let spacing =
            get_prop_int(component, "spacing", vm).unwrap_or(DEFAULT_SPACING as i64) as i32;
        let padding = get_prop_int(component, "padding", vm).unwrap_or(0) as i32;

        let child_count = component.children.len() as i32;
        if child_count == 0 {
            return Vec::new();
        }

        let total_spacing = spacing * (child_count - 1);
        let child_width = (available.width - 2 * padding - total_spacing) / child_count;
        let child_height = available.height - 2 * padding;

        let mut x = available.x + padding;
        component
            .children
            .iter()
            .map(|_| {
                let rect = LayoutRect {
                    x,
                    y: available.y + padding,
                    width: child_width,
                    height: child_height,
                };
                x += child_width + spacing;
                rect
            })
            .collect()
    }

    /// Layout children in a grid.
    fn layout_grid(
        component: &ast::Component,
        available: LayoutRect,
        vm: &ShellVm,
    ) -> Vec<LayoutRect> {
        let columns = get_prop_int(component, "columns", vm).unwrap_or(2) as i32;
        let spacing =
            get_prop_int(component, "spacing", vm).unwrap_or(DEFAULT_SPACING as i64) as i32;
        let padding =
            get_prop_int(component, "padding", vm).unwrap_or(DEFAULT_PADDING as i64) as i32;

        let child_count = component.children.len() as i32;
        if child_count == 0 || columns <= 0 {
            return Vec::new();
        }

        let rows = (child_count + columns - 1) / columns;
        let cell_width = (available.width - 2 * padding - spacing * (columns - 1)) / columns;
        let cell_height = (available.height - 2 * padding - spacing * (rows - 1)) / rows;

        component
            .children
            .iter()
            .enumerate()
            .map(|(i, _)| {
                let col = i as i32 % columns;
                let row = i as i32 / columns;
                LayoutRect {
                    x: available.x + padding + col * (cell_width + spacing),
                    y: available.y + padding + row * (cell_height + spacing),
                    width: cell_width,
                    height: cell_height,
                }
            })
            .collect()
    }

    type BOOL = i32;
    type DWORD = u32;
    type HBRUSH = isize;
    type HCURSOR = isize;
    type HICON = isize;
    type HINSTANCE = isize;
    type HMENU = isize;
    type HWND = isize;
    type LPARAM = isize;
    type LRESULT = isize;
    type UINT = u32;
    type WPARAM = usize;
    type LONG_PTR = isize;

    const CW_USEDEFAULT: i32 = 0x80000000u32 as i32;

    const SW_SHOW: i32 = 5;

    const GWLP_USERDATA: i32 = -21;

    const WS_OVERLAPPEDWINDOW: DWORD = 0x00CF0000;
    const WS_VISIBLE: DWORD = 0x10000000;
    const WS_CHILD: DWORD = 0x40000000;

    const WM_COMMAND: UINT = 0x0111;
    const WM_CLOSE: UINT = 0x0010;
    const WM_DESTROY: UINT = 0x0002;

    const BN_CLICKED: u16 = 0;

    const MB_OK: UINT = 0x0000;
    const MB_ICONERROR: UINT = 0x0010;

    const COLOR_WINDOW: i32 = 5;

    #[repr(C)]
    struct POINT {
        x: i32,
        y: i32,
    }

    #[repr(C)]
    struct MSG {
        hwnd: HWND,
        message: UINT,
        wParam: WPARAM,
        lParam: LPARAM,
        time: DWORD,
        pt: POINT,
        lPrivate: DWORD,
    }

    type WNDPROC = unsafe extern "system" fn(HWND, UINT, WPARAM, LPARAM) -> LRESULT;

    #[repr(C)]
    struct WNDCLASSW {
        style: UINT,
        lpfnWndProc: Option<WNDPROC>,
        cbClsExtra: i32,
        cbWndExtra: i32,
        hInstance: HINSTANCE,
        hIcon: HICON,
        hCursor: HCURSOR,
        hbrBackground: HBRUSH,
        lpszMenuName: *const u16,
        lpszClassName: *const u16,
    }

    #[link(name = "user32")]
    extern "system" {
        fn RegisterClassW(lpWndClass: *const WNDCLASSW) -> u16;
        fn CreateWindowExW(
            dwExStyle: DWORD,
            lpClassName: *const u16,
            lpWindowName: *const u16,
            dwStyle: DWORD,
            X: i32,
            Y: i32,
            nWidth: i32,
            nHeight: i32,
            hWndParent: HWND,
            hMenu: HMENU,
            hInstance: HINSTANCE,
            lpParam: *mut c_void,
        ) -> HWND;
        fn DefWindowProcW(hwnd: HWND, msg: UINT, wparam: WPARAM, lparam: LPARAM) -> LRESULT;
        fn ShowWindow(hwnd: HWND, nCmdShow: i32) -> BOOL;
        fn UpdateWindow(hwnd: HWND) -> BOOL;
        fn GetMessageW(
            lpMsg: *mut MSG,
            hWnd: HWND,
            wMsgFilterMin: UINT,
            wMsgFilterMax: UINT,
        ) -> BOOL;
        fn TranslateMessage(lpMsg: *const MSG) -> BOOL;
        fn DispatchMessageW(lpMsg: *const MSG) -> LRESULT;
        fn PostQuitMessage(nExitCode: i32);
        fn SetWindowTextW(hwnd: HWND, lpString: *const u16) -> BOOL;
        fn SetWindowLongPtrW(hwnd: HWND, nIndex: i32, dwNewLong: LONG_PTR) -> LONG_PTR;
        fn GetWindowLongPtrW(hwnd: HWND, nIndex: i32) -> LONG_PTR;
        fn PostMessageW(hwnd: HWND, msg: UINT, wParam: WPARAM, lParam: LPARAM) -> BOOL;
        fn MessageBoxW(hwnd: HWND, text: *const u16, caption: *const u16, typ: UINT) -> i32;
    }

    #[link(name = "kernel32")]
    extern "system" {
        fn GetModuleHandleW(lpModuleName: *const u16) -> HINSTANCE;
    }

    #[derive(Debug)]
    struct LabelWidget {
        hwnd: HWND,
        text_expr: ast::Expr,
    }

    #[derive(Debug)]
    struct ButtonWidget {
        id: u16,
        hwnd: HWND,
        on_click: Option<ast::Expr>,
    }

    struct App<'a> {
        hwnd: HWND,
        vm: ShellVm<'a>,
        labels: Vec<LabelWidget>,
        buttons: Vec<ButtonWidget>,
    }

    pub(super) fn run(view: &ast::View, vm: ShellVm<'_>, interactive: bool) -> Result<()> {
        let window = find_first_window_component(view)
            .ok_or_else(|| anyhow!("No Window component found in View {}", view.name))?;

        let title = get_prop_string(window, "title", &vm).unwrap_or_else(|| view.name.clone());
        let mut width = get_prop_int(window, "width", &vm).unwrap_or(400);
        let mut height = get_prop_int(window, "height", &vm).unwrap_or(300);
        if width <= 0 {
            width = 400;
        }
        if height <= 0 {
            height = 300;
        }

        unsafe {
            let hinstance = GetModuleHandleW(std::ptr::null());

            let class_name = to_wide("BunkerLangViewWindow");

            let wc = WNDCLASSW {
                style: 0,
                lpfnWndProc: Some(wndproc),
                cbClsExtra: 0,
                cbWndExtra: 0,
                hInstance: hinstance,
                hIcon: 0,
                hCursor: 0,
                hbrBackground: (COLOR_WINDOW + 1) as HBRUSH,
                lpszMenuName: std::ptr::null(),
                lpszClassName: class_name.as_ptr(),
            };

            if RegisterClassW(&wc) == 0 {
                return Err(anyhow!("RegisterClassW failed"));
            }

            let title_w = to_wide(&title);
            let hwnd = CreateWindowExW(
                0,
                class_name.as_ptr(),
                title_w.as_ptr(),
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                width as i32,
                height as i32,
                0,
                0,
                hinstance,
                std::ptr::null_mut(),
            );

            if hwnd == 0 {
                return Err(anyhow!("CreateWindowExW failed"));
            }

            let mut app_box = Box::new(App {
                hwnd,
                vm,
                labels: Vec::new(),
                buttons: Vec::new(),
            });

            build_controls(&mut app_box, window, hinstance, width as i32, height as i32)?;
            app_box.refresh_labels()?;

            // Store pointer for callbacks.
            let app_ptr: *mut App<'_> = &mut *app_box;
            SetWindowLongPtrW(hwnd, GWLP_USERDATA, app_ptr as LONG_PTR);

            ShowWindow(hwnd, SW_SHOW);
            UpdateWindow(hwnd);

            if !interactive {
                app_box.demo_click_first_button()?;
                app_box.refresh_labels()?;
                let _ = PostMessageW(hwnd, WM_CLOSE, 0, 0);
            }

            // Run the message loop (blocks until the window is closed).
            let mut msg = MSG {
                hwnd: 0,
                message: 0,
                wParam: 0,
                lParam: 0,
                time: 0,
                pt: POINT { x: 0, y: 0 },
                lPrivate: 0,
            };
            while GetMessageW(&mut msg, 0, 0, 0) > 0 {
                let _ = TranslateMessage(&msg);
                let _ = DispatchMessageW(&msg);
            }

            Ok(())
        }
    }

    fn find_first_window_component<'a>(view: &'a ast::View) -> Option<&'a ast::Component> {
        fn walk<'a>(component: &'a ast::Component) -> Option<&'a ast::Component> {
            if component.name == "Window" {
                return Some(component);
            }
            for child in &component.children {
                if let Some(found) = walk(child) {
                    return Some(found);
                }
            }
            None
        }

        for component in &view.components {
            if let Some(found) = walk(component) {
                return Some(found);
            }
        }
        None
    }

    fn to_wide(s: &str) -> Vec<u16> {
        s.encode_utf16().chain(std::iter::once(0)).collect()
    }

    fn build_controls(
        app: &mut App<'_>,
        window: &ast::Component,
        hinstance: HINSTANCE,
        width: i32,
        height: i32,
    ) -> Result<()> {
        let mut next_id: u16 = 1000;
        let available = LayoutRect {
            x: 0,
            y: 0,
            width,
            height,
        };

        // Start recursive layout from window's children
        build_controls_recursive(app, window, available, hinstance, &mut next_id)
    }

    fn build_controls_recursive(
        app: &mut App<'_>,
        component: &ast::Component,
        available: LayoutRect,
        hinstance: HINSTANCE,
        next_id: &mut u16,
    ) -> Result<()> {
        match component.name.as_str() {
            "Window" | "Column" => {
                // Layout children vertically
                let child_rects = layout_column(component, available, &app.vm);
                for (child, rect) in component.children.iter().zip(child_rects) {
                    build_controls_recursive(app, child, rect, hinstance, next_id)?;
                }
            }
            "Row" => {
                // Layout children horizontally
                let child_rects = layout_row(component, available, &app.vm);
                for (child, rect) in component.children.iter().zip(child_rects) {
                    build_controls_recursive(app, child, rect, hinstance, next_id)?;
                }
            }
            "Grid" => {
                // Layout children in a grid
                let child_rects = layout_grid(component, available, &app.vm);
                for (child, rect) in component.children.iter().zip(child_rects) {
                    build_controls_recursive(app, child, rect, hinstance, next_id)?;
                }
            }
            "Label" => {
                create_label_control(app, component, available, hinstance)?;
            }
            "Button" => {
                create_button_control(app, component, available, hinstance, next_id)?;
            }
            _ => {
                // Unknown component - recurse into children with same available space
                for child in &component.children {
                    build_controls_recursive(app, child, available, hinstance, next_id)?;
                }
            }
        }
        Ok(())
    }

    fn create_label_control(
        app: &mut App<'_>,
        component: &ast::Component,
        rect: LayoutRect,
        hinstance: HINSTANCE,
    ) -> Result<()> {
        let expr = get_prop_expr(component, "text")
            .cloned()
            .unwrap_or_else(|| ast::Expr::Literal(ast::Literal::String(String::new())));

        unsafe {
            let class = to_wide("STATIC");
            let text = to_wide("");
            let hwnd = CreateWindowExW(
                0,
                class.as_ptr(),
                text.as_ptr(),
                WS_CHILD | WS_VISIBLE,
                rect.x,
                rect.y,
                rect.width,
                rect.height.min(LABEL_HEIGHT),
                app.hwnd,
                0,
                hinstance,
                std::ptr::null_mut(),
            );
            if hwnd == 0 {
                return Err(anyhow!("Failed to create STATIC control"));
            }
            app.labels.push(LabelWidget {
                hwnd,
                text_expr: expr,
            });
        }
        Ok(())
    }

    fn create_button_control(
        app: &mut App<'_>,
        component: &ast::Component,
        rect: LayoutRect,
        hinstance: HINSTANCE,
        next_id: &mut u16,
    ) -> Result<()> {
        let label =
            get_prop_string(component, "text", &app.vm).unwrap_or_else(|| "Button".to_string());
        let on_click = get_prop_expr(component, "on_click").cloned();

        unsafe {
            let label_w = to_wide(&label);
            let class = to_wide("BUTTON");
            let hwnd = CreateWindowExW(
                0,
                class.as_ptr(),
                label_w.as_ptr(),
                WS_CHILD | WS_VISIBLE,
                rect.x,
                rect.y,
                rect.width,
                rect.height.min(BUTTON_HEIGHT),
                app.hwnd,
                *next_id as HMENU,
                hinstance,
                std::ptr::null_mut(),
            );
            if hwnd == 0 {
                return Err(anyhow!("Failed to create BUTTON control"));
            }

            app.buttons.push(ButtonWidget {
                id: *next_id,
                hwnd,
                on_click,
            });
            *next_id = next_id.wrapping_add(1);
        }
        Ok(())
    }

    impl App<'_> {
        fn refresh_labels(&mut self) -> Result<()> {
            unsafe {
                for label in &self.labels {
                    let value = eval_view_expr(&label.text_expr, &self.vm)?;
                    let text = value.to_display_string();
                    let text_w = to_wide(&text);
                    let _ = SetWindowTextW(label.hwnd, text_w.as_ptr());
                }
            }
            Ok(())
        }

        fn demo_click_first_button(&mut self) -> Result<()> {
            let Some(button) = self.buttons.first() else {
                return Ok(());
            };
            let Some(expr) = &button.on_click else {
                return Ok(());
            };
            exec_view_action(expr, &mut self.vm)?;
            let _ = self.vm.run_until_idle()?;
            Ok(())
        }

        fn handle_button_click(&mut self, id: u16) -> Result<()> {
            let Some(button) = self.buttons.iter().find(|b| b.id == id) else {
                return Ok(());
            };

            let Some(expr) = &button.on_click else {
                return Ok(());
            };

            exec_view_action(expr, &mut self.vm)?;
            let _ = self.vm.run_until_idle()?;
            self.refresh_labels()?;
            Ok(())
        }
    }

    unsafe extern "system" fn wndproc(
        hwnd: HWND,
        msg: UINT,
        wparam: WPARAM,
        lparam: LPARAM,
    ) -> LRESULT {
        match msg {
            WM_COMMAND => {
                let code = ((wparam >> 16) & 0xFFFF) as u16;
                if code == BN_CLICKED {
                    let id = (wparam & 0xFFFF) as u16;
                    let ptr = GetWindowLongPtrW(hwnd, GWLP_USERDATA) as *mut App<'static>;
                    if !ptr.is_null() {
                        let app = &mut *ptr;
                        if let Err(e) = app.handle_button_click(id) {
                            let text = to_wide(&format!("{e}"));
                            let caption = to_wide("Bunker View Error");
                            let _ = MessageBoxW(
                                hwnd,
                                text.as_ptr(),
                                caption.as_ptr(),
                                MB_OK | MB_ICONERROR,
                            );
                        }
                    }
                }
                0
            }
            WM_DESTROY => {
                let _ = SetWindowLongPtrW(hwnd, GWLP_USERDATA, 0);
                PostQuitMessage(0);
                0
            }
            _ => DefWindowProcW(hwnd, msg, wparam, lparam),
        }
    }
}
