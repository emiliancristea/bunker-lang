use std::alloc::{alloc_zeroed, dealloc, Layout};
use std::cell::RefCell;
use std::collections::HashMap;

use anyhow::{anyhow, Result};
use cranelift::prelude::*;
use cranelift_jit::{JITBuilder, JITModule};
use cranelift_module::{FuncId, Linkage, Module};

use crate::{ast, builtins};

// ============================================================================
// Thread-local Arena Allocator for JIT Runtime
// ============================================================================

#[allow(dead_code)]
const ARENA_BLOCK_SIZE: usize = 64 * 1024; // 64 KB blocks
const ARENA_WATERMARK_MAX_DEPTH: usize = 1_000_000;

struct ArenaBlock {
    data: *mut u8,
    layout: Layout,
}

impl Drop for ArenaBlock {
    fn drop(&mut self) {
        unsafe {
            dealloc(self.data, self.layout);
        }
    }
}

struct Arena {
    blocks: Vec<ArenaBlock>,
    current: *mut u8,
    remaining: usize,
    total_allocated: usize,
}

impl Arena {
    fn new() -> Self {
        Self {
            blocks: Vec::new(),
            current: std::ptr::null_mut(),
            remaining: 0,
            total_allocated: 0,
        }
    }

    #[allow(dead_code)]
    fn alloc(&mut self, size: usize, align: usize) -> *mut u8 {
        if size == 0 {
            return std::ptr::null_mut();
        }

        let align = align.max(1).next_power_of_two();

        // Align the current pointer
        let current_addr = self.current as usize;
        let aligned_addr = (current_addr + align - 1) & !(align - 1);
        let padding = aligned_addr - current_addr;

        if padding + size <= self.remaining {
            // Bump allocate from current block
            self.current = (aligned_addr + size) as *mut u8;
            self.remaining -= padding + size;
            self.total_allocated += size;
            return aligned_addr as *mut u8;
        }

        // Need a new block
        let block_size = ARENA_BLOCK_SIZE.max(size + align);
        let Ok(layout) = Layout::from_size_align(block_size, 8) else {
            return std::ptr::null_mut();
        };

        let ptr = unsafe { alloc_zeroed(layout) };
        if ptr.is_null() {
            return std::ptr::null_mut();
        }

        self.blocks.push(ArenaBlock { data: ptr, layout });

        // Align within new block
        let block_addr = ptr as usize;
        let aligned_addr = (block_addr + align - 1) & !(align - 1);

        self.current = (aligned_addr + size) as *mut u8;
        self.remaining = block_size - (aligned_addr - block_addr) - size;
        self.total_allocated += size;

        aligned_addr as *mut u8
    }

    fn reset(&mut self) {
        // Free all blocks except the first one (keep for reuse)
        if self.blocks.len() > 1 {
            self.blocks.truncate(1);
        }

        if let Some(block) = self.blocks.first() {
            self.current = block.data;
            self.remaining = block.layout.size();
        } else {
            self.current = std::ptr::null_mut();
            self.remaining = 0;
        }

        self.total_allocated = 0;
    }

    fn stats(&self) -> (usize, usize) {
        let block_memory: usize = self.blocks.iter().map(|b| b.layout.size()).sum();
        (self.total_allocated, block_memory)
    }

    /// Save current arena position as a watermark for later restoration.
    fn save_watermark(&self) -> ArenaWatermark {
        ArenaWatermark {
            block_count: self.blocks.len(),
            position: self.current,
            remaining: self.remaining,
        }
    }

    /// Restore arena to a previously saved watermark, freeing all allocations made after it.
    fn restore_watermark(&mut self, mark: ArenaWatermark) {
        // Free blocks allocated after watermark
        while self.blocks.len() > mark.block_count {
            self.blocks.pop(); // Drops and deallocates the block
        }
        // Restore position within surviving block
        self.current = mark.position;
        self.remaining = mark.remaining;
        // Note: We don't adjust total_allocated since it's for stats only
    }
}

/// Watermark representing a saved arena position.
#[derive(Clone, Copy)]
struct ArenaWatermark {
    block_count: usize,
    position: *mut u8,
    remaining: usize,
}

thread_local! {
    static JIT_ARENA: RefCell<Arena> = RefCell::new(Arena::new());
    static WATERMARK_STACK: RefCell<Vec<ArenaWatermark>> = const { RefCell::new(Vec::new()) };
}

/// Reset the JIT arena, freeing all allocated memory.
pub fn reset_jit_arena() {
    JIT_ARENA.with(|arena| arena.borrow_mut().reset());
    WATERMARK_STACK.with(|stack| stack.borrow_mut().clear());
}

// ============================================================================
// Arena Scope Runtime Functions (called from JIT-compiled code)
// ============================================================================

/// Push a new arena watermark onto the stack (called at block entry).
extern "C" fn bunker_arena_push() {
    WATERMARK_STACK.with(|stack| {
        let mut stack = stack.borrow_mut();
        if stack.len() >= ARENA_WATERMARK_MAX_DEPTH {
            panic!(
                "JIT arena watermark stack overflow: exceeded {ARENA_WATERMARK_MAX_DEPTH} nested scopes"
            );
        }

        JIT_ARENA.with(|arena| {
            let mark = arena.borrow().save_watermark();
            stack.push(mark);
        });
    });
}

/// Pop and restore the last arena watermark (called at block exit).
extern "C" fn bunker_arena_pop() {
    WATERMARK_STACK.with(|stack| {
        if let Some(mark) = stack.borrow_mut().pop() {
            JIT_ARENA.with(|arena| arena.borrow_mut().restore_watermark(mark));
        }
    });
}

/// Get arena statistics: (bytes_allocated, bytes_reserved)
#[allow(dead_code)]
pub fn jit_arena_stats() -> (usize, usize) {
    JIT_ARENA.with(|arena| arena.borrow().stats())
}

/// Read a file and return its contents as a Bunker string (allocated in arena).
/// String format: [len: i64][data: u8...]
/// Returns 0 (null) on error.
extern "C" fn bunker_read_file(path_ptr: i64) -> i64 {
    if path_ptr == 0 {
        return 0;
    }

    // Read path string from Bunker format
    let path_str = unsafe {
        let ptr = path_ptr as *const u8;
        let len = *(ptr as *const i64) as usize;
        let data = std::slice::from_raw_parts(ptr.add(8), len);
        match std::str::from_utf8(data) {
            Ok(s) => s.to_string(),
            Err(_) => return 0,
        }
    };

    // Read the file
    let contents = match std::fs::read_to_string(&path_str) {
        Ok(s) => s,
        Err(_) => return 0,
    };

    alloc_bunker_string(&contents)
}

/// Unrecoverable panic with formatted message to stderr. Exits process with code 101.
extern "C" fn bunker_panic(msg_ptr: i64) {
    let msg_str = if msg_ptr == 0 {
        "<no message>".to_string()
    } else {
        unsafe {
            let ptr = msg_ptr as *const u8;
            let len = *(ptr as *const i64) as usize;
            let data = std::slice::from_raw_parts(ptr.add(8), len);
            std::str::from_utf8(data).unwrap_or("<invalid utf8>").to_string()
        }
    };
    eprintln!("bunker runtime panic: {}", msg_str);
    std::process::exit(101);
}

/// Runtime assertion failure check. If cond == 0, exits process with code 101.
extern "C" fn bunker_assert(cond: i8, msg_ptr: i64) {
    if cond == 0 {
        let msg_str = if msg_ptr == 0 {
            "assertion failed".to_string()
        } else {
            unsafe {
                let ptr = msg_ptr as *const u8;
                let len = *(ptr as *const i64) as usize;
                let data = std::slice::from_raw_parts(ptr.add(8), len);
                std::str::from_utf8(data).unwrap_or("<invalid utf8>").to_string()
            }
        };
        eprintln!("bunker runtime assertion failed: {}", msg_str);
        std::process::exit(101);
    }
}

/// Write content to a file. Returns 1 on success, 0 on failure.
extern "C" fn bunker_write_file(path_ptr: i64, content_ptr: i64) -> i64 {
    if path_ptr == 0 || content_ptr == 0 {
        return 0;
    }

    // Read path string
    let path_str = unsafe {
        let ptr = path_ptr as *const u8;
        let len = *(ptr as *const i64) as usize;
        let data = std::slice::from_raw_parts(ptr.add(8), len);
        match std::str::from_utf8(data) {
            Ok(s) => s.to_string(),
            Err(_) => return 0,
        }
    };

    // Read content string
    let content_str = unsafe {
        let ptr = content_ptr as *const u8;
        let len = *(ptr as *const i64) as usize;
        let data = std::slice::from_raw_parts(ptr.add(8), len);
        match std::str::from_utf8(data) {
            Ok(s) => s.to_string(),
            Err(_) => return 0,
        }
    };

    // Write to file
    match std::fs::write(&path_str, &content_str) {
        Ok(_) => 1,
        Err(_) => 0,
    }
}

/// Check if a file exists. Returns 1 if exists, 0 otherwise.
extern "C" fn bunker_file_exists(path_ptr: i64) -> i64 {
    if path_ptr == 0 {
        return 0;
    }

    let path_str = unsafe {
        let ptr = path_ptr as *const u8;
        let len = *(ptr as *const i64) as usize;
        let data = std::slice::from_raw_parts(ptr.add(8), len);
        match std::str::from_utf8(data) {
            Ok(s) => s.to_string(),
            Err(_) => return 0,
        }
    };

    if std::path::Path::new(&path_str).exists() {
        1
    } else {
        0
    }
}

extern "C" fn bunker_args_count() -> i64 {
    let args: Vec<String> = std::env::args().collect();
    args.len() as i64
}

extern "C" fn bunker_arg_at(index: i64) -> i64 {
    let args: Vec<String> = std::env::args().collect();
    if index >= 0 && (index as usize) < args.len() {
        alloc_bunker_string(&args[index as usize])
    } else {
        alloc_bunker_string("")
    }
}

/// Helper to read a Bunker string from a pointer
unsafe fn read_bunker_string(ptr: i64) -> Option<String> {
    if ptr == 0 {
        return None;
    }
    let ptr = ptr as *const u8;
    let len = *(ptr as *const i64) as usize;
    let data = std::slice::from_raw_parts(ptr.add(8), len);
    std::str::from_utf8(data).ok().map(|s| s.to_string())
}

/// Helper to allocate and write a Bunker string
fn alloc_bunker_string(s: &str) -> i64 {
    let bytes = s.as_bytes();
    let total_size = 8 + bytes.len();

    let layout = match std::alloc::Layout::from_size_align(total_size.max(8), 8) {
        Ok(layout) => layout,
        Err(_) => return 0,
    };
    let result_ptr = unsafe { std::alloc::alloc_zeroed(layout) };
    if result_ptr.is_null() {
        return 0;
    }

    unsafe {
        *(result_ptr as *mut i64) = bytes.len() as i64;
        std::ptr::copy_nonoverlapping(bytes.as_ptr(), result_ptr.add(8), bytes.len());
    }

    result_ptr as i64
}

/// Get character at index. Returns single-char string or empty string if out of bounds.
extern "C" fn bunker_char_at(str_ptr: i64, index: i64) -> i64 {
    let s = unsafe { read_bunker_string(str_ptr) };
    let Some(s) = s else {
        return alloc_bunker_string("");
    };

    if index < 0 || index as usize >= s.len() {
        return alloc_bunker_string("");
    }

    // Get character at byte index (works for ASCII, for UTF-8 would need char_indices)
    let ch = s.chars().nth(index as usize);
    match ch {
        Some(c) => {
            let mut buf = [0u8; 4];
            let char_str = c.encode_utf8(&mut buf);
            alloc_bunker_string(char_str)
        }
        None => alloc_bunker_string(""),
    }
}

/// Extract substring from start to end (exclusive).
extern "C" fn bunker_substring(str_ptr: i64, start: i64, end: i64) -> i64 {
    let s = unsafe { read_bunker_string(str_ptr) };
    let Some(s) = s else {
        return alloc_bunker_string("");
    };

    let start = start.max(0) as usize;
    let end = end.max(0) as usize;
    let len = s.len();

    if start >= len || start >= end {
        return alloc_bunker_string("");
    }

    let end = end.min(len);
    alloc_bunker_string(&s[start..end])
}

/// Check if string contains substring. Returns 1 if yes, 0 if no.
extern "C" fn bunker_contains(str_ptr: i64, substr_ptr: i64) -> i64 {
    let s = unsafe { read_bunker_string(str_ptr) };
    let substr = unsafe { read_bunker_string(substr_ptr) };

    match (s, substr) {
        (Some(s), Some(sub)) if s.contains(&sub) => 1,
        _ => 0,
    }
}

/// Check if string starts with prefix. Returns 1 if yes, 0 if no.
extern "C" fn bunker_starts_with(str_ptr: i64, prefix_ptr: i64) -> i64 {
    let s = unsafe { read_bunker_string(str_ptr) };
    let prefix = unsafe { read_bunker_string(prefix_ptr) };

    match (s, prefix) {
        (Some(s), Some(p)) if s.starts_with(&p) => 1,
        _ => 0,
    }
}

/// Check if string ends with suffix. Returns 1 if yes, 0 if no.
extern "C" fn bunker_ends_with(str_ptr: i64, suffix_ptr: i64) -> i64 {
    let s = unsafe { read_bunker_string(str_ptr) };
    let suffix = unsafe { read_bunker_string(suffix_ptr) };

    match (s, suffix) {
        (Some(s), Some(suf)) if s.ends_with(&suf) => 1,
        _ => 0,
    }
}

/// Trim whitespace from both ends of string.
extern "C" fn bunker_trim(str_ptr: i64) -> i64 {
    let s = unsafe { read_bunker_string(str_ptr) };
    let Some(s) = s else {
        return alloc_bunker_string("");
    };
    alloc_bunker_string(s.trim())
}

/// Parse string as integer. Returns the integer value, or 0 if parsing fails.
extern "C" fn bunker_parse_int(str_ptr: i64) -> i64 {
    let s = unsafe { read_bunker_string(str_ptr) };
    let Some(s) = s else { return 0 };
    s.trim().parse::<i64>().unwrap_or(0)
}

/// Convert integer to string.
extern "C" fn bunker_int_to_string(value: i64) -> i64 {
    alloc_bunker_string(&value.to_string())
}

/// Get the character code (ASCII/UTF-8 first byte) of the first character in a string.
extern "C" fn bunker_char_code(str_ptr: i64) -> i64 {
    let s = unsafe { read_bunker_string(str_ptr) };
    match s {
        Some(s) if !s.is_empty() => s.bytes().next().unwrap_or(0) as i64,
        _ => 0,
    }
}

/// Get the byte character code at an index without allocating a one-character string.
extern "C" fn bunker_char_code_at(str_ptr: i64, index: i64) -> i64 {
    if str_ptr == 0 || index < 0 {
        return 0;
    }

    unsafe {
        let ptr = str_ptr as *const u8;
        let len = *(ptr as *const i64) as usize;
        let index = index as usize;
        if index >= len {
            return 0;
        }
        *ptr.add(8 + index) as i64
    }
}

/// Create a single-character string from a character code.
extern "C" fn bunker_from_char_code(code: i64) -> i64 {
    if !(0..=255).contains(&code) {
        return alloc_bunker_string("");
    }
    let ch = code as u8 as char;
    alloc_bunker_string(&ch.to_string())
}

/// Compare two strings for equality. Returns 1 if equal, 0 otherwise.
extern "C" fn bunker_str_eq(a_ptr: i64, b_ptr: i64) -> i64 {
    let a = unsafe { read_bunker_string(a_ptr) };
    let b = unsafe { read_bunker_string(b_ptr) };
    match (a, b) {
        (Some(a), Some(b)) if a == b => 1,
        (Some(_), Some(_)) => 0,
        (None, None) => 1, // Both null
        _ => 0,            // One null, one not
    }
}

/// Join a Vec<str> handle into one newline-terminated string in a single pass.
extern "C" fn bunker_join_lines(vec_ptr: i64) -> i64 {
    if vec_ptr == 0 {
        return alloc_bunker_string("");
    }

    unsafe {
        let header = vec_ptr as *const i64;
        let length = *header.offset(1);
        let data_ptr = *header.offset(2) as *const i64;
        if length <= 0 || data_ptr.is_null() {
            return alloc_bunker_string("");
        }

        let mut total_len: usize = 0;
        let mut i: i64 = 0;
        while i < length {
            let str_ptr = *data_ptr.offset(i as isize);
            if str_ptr != 0 {
                total_len = total_len.saturating_add(*(str_ptr as *const i64) as usize);
            }
            total_len = total_len.saturating_add(1);
            i += 1;
        }

        let mut output = String::with_capacity(total_len);
        i = 0;
        while i < length {
            let str_ptr = *data_ptr.offset(i as isize);
            if let Some(line) = read_bunker_string(str_ptr) {
                output.push_str(&line);
            }
            output.push('\n');
            i += 1;
        }

        alloc_bunker_string(&output)
    }
}

// ============================================================================
// Vec<T> Dynamic Array Runtime Functions
// ============================================================================
// Vec layout: [capacity: i64][length: i64][data_ptr: *mut i64]
// Each element is stored as i64 (all Bunker types are i64 at runtime)

const VEC_INITIAL_CAPACITY: i64 = 8;
const VEC_HEADER_SIZE: i64 = 24; // 8 bytes capacity + 8 bytes length + 8 bytes data ptr

/// Create a new empty Vec. Returns pointer to Vec header.
/// Vec handles must survive block scopes because parsers/builders store them in other Vecs.
/// Allocate both header and data with the system allocator instead of the arena.
extern "C" fn bunker_vec_new() -> i64 {
    let header_layout = std::alloc::Layout::from_size_align(VEC_HEADER_SIZE as usize, 8).unwrap();
    let header_ptr = unsafe { std::alloc::alloc_zeroed(header_layout) };
    if header_ptr.is_null() {
        return 0;
    }

    let data_layout =
        std::alloc::Layout::from_size_align((VEC_INITIAL_CAPACITY * 8) as usize, 8).unwrap();
    let data_ptr = unsafe { std::alloc::alloc_zeroed(data_layout) };
    if data_ptr.is_null() {
        unsafe {
            std::alloc::dealloc(header_ptr, header_layout);
        }
        return 0;
    }

    unsafe {
        // Write capacity
        *(header_ptr as *mut i64) = VEC_INITIAL_CAPACITY;
        // Write length (0)
        *((header_ptr as *mut i64).offset(1)) = 0;
        // Write data pointer
        *((header_ptr as *mut i64).offset(2)) = data_ptr as i64;
    }

    header_ptr as i64
}

/// Push an element to the Vec. Returns the new length.
/// Note: Vec data uses system allocator to survive arena scope changes.
extern "C" fn bunker_vec_push(vec_ptr: i64, value: i64) -> i64 {
    if vec_ptr == 0 {
        return 0;
    }

    unsafe {
        let header = vec_ptr as *mut i64;
        let capacity = *header;
        let length = *header.offset(1);
        let data_ptr = *header.offset(2) as *mut i64;

        // Check if we need to grow
        if length >= capacity {
            // Need to reallocate - double the capacity
            let new_capacity = capacity * 2;

            // Use system allocator for vec data (not arena)
            let new_layout =
                std::alloc::Layout::from_size_align((new_capacity * 8) as usize, 8).unwrap();
            let new_data = std::alloc::alloc_zeroed(new_layout);
            if new_data.is_null() {
                return length;
            }

            // Copy old data
            if !data_ptr.is_null() && length > 0 {
                std::ptr::copy_nonoverlapping(data_ptr, new_data as *mut i64, length as usize);
                // Free old data
                let old_layout =
                    std::alloc::Layout::from_size_align((capacity * 8) as usize, 8).unwrap();
                std::alloc::dealloc(data_ptr as *mut u8, old_layout);
            }

            // Update header
            *header = new_capacity;
            *header.offset(2) = new_data as i64;

            // Write new element
            let new_data_ptr = new_data as *mut i64;
            *new_data_ptr.offset(length as isize) = value;
            *header.offset(1) = length + 1;

            length + 1
        } else {
            // Just push
            *data_ptr.offset(length as isize) = value;
            *header.offset(1) = length + 1;
            length + 1
        }
    }
}

/// Pop the last element from the Vec. Returns the element or 0 if empty.
extern "C" fn bunker_vec_pop(vec_ptr: i64) -> i64 {
    if vec_ptr == 0 {
        return 0;
    }

    unsafe {
        let header = vec_ptr as *mut i64;
        let length = *header.offset(1);

        if length == 0 {
            return 0;
        }

        let data_ptr = *header.offset(2) as *mut i64;
        let value = *data_ptr.offset((length - 1) as isize);
        *header.offset(1) = length - 1;
        value
    }
}

/// Get the length of the Vec.
extern "C" fn bunker_vec_len(vec_ptr: i64) -> i64 {
    if vec_ptr == 0 {
        return 0;
    }

    unsafe {
        let header = vec_ptr as *mut i64;
        *header.offset(1)
    }
}

/// Get the capacity of the Vec.
extern "C" fn bunker_vec_capacity(vec_ptr: i64) -> i64 {
    if vec_ptr == 0 {
        return 0;
    }

    unsafe {
        let header = vec_ptr as *mut i64;
        *header
    }
}

/// Get element at index. Returns 0 if out of bounds.
extern "C" fn bunker_vec_get(vec_ptr: i64, index: i64) -> i64 {
    if vec_ptr == 0 {
        return 0;
    }

    unsafe {
        let header = vec_ptr as *mut i64;
        let length = *header.offset(1);

        if index < 0 || index >= length {
            return 0;
        }

        let data_ptr = *header.offset(2) as *mut i64;
        *data_ptr.offset(index as isize)
    }
}

/// Set element at index. Returns 1 if successful, 0 if out of bounds.
extern "C" fn bunker_vec_set(vec_ptr: i64, index: i64, value: i64) -> i64 {
    if vec_ptr == 0 {
        return 0;
    }

    unsafe {
        let header = vec_ptr as *mut i64;
        let length = *header.offset(1);

        if index < 0 || index >= length {
            return 0;
        }

        let data_ptr = *header.offset(2) as *mut i64;
        *data_ptr.offset(index as isize) = value;
        1
    }
}

/// Clear all elements from the Vec.
extern "C" fn bunker_vec_clear(vec_ptr: i64) {
    if vec_ptr == 0 {
        return;
    }

    unsafe {
        let header = vec_ptr as *mut i64;
        *header.offset(1) = 0; // Set length to 0
    }
}

/// Check if the Vec contains an item (for integer/primitive/handle types). Returns 1 if found, 0 otherwise.
extern "C" fn bunker_vec_contains(vec_ptr: i64, item: i64) -> i64 {
    if vec_ptr == 0 {
        return 0;
    }
    unsafe {
        let header = vec_ptr as *const i64;
        let length = *header.offset(1);
        let data_ptr = *header.offset(2) as *const i64;
        if length <= 0 || data_ptr.is_null() {
            return 0;
        }
        for i in 0..length {
            let val = *data_ptr.offset(i as isize);
            if val == item {
                return 1;
            }
        }
    }
    0
}

/// Check if the Vec contains a string item using bunker_str_eq. Returns 1 if found, 0 otherwise.
extern "C" fn bunker_vec_contains_str(vec_ptr: i64, item: i64) -> i64 {
    if vec_ptr == 0 {
        return 0;
    }
    unsafe {
        let header = vec_ptr as *const i64;
        let length = *header.offset(1);
        let data_ptr = *header.offset(2) as *const i64;
        if length <= 0 || data_ptr.is_null() {
            return 0;
        }
        for i in 0..length {
            let val = *data_ptr.offset(i as isize);
            if bunker_str_eq(val, item) == 1 {
                return 1;
            }
        }
    }
    0
}

/// Check if the Vec is empty. Returns 1 if empty, 0 otherwise.
extern "C" fn bunker_vec_is_empty(vec_ptr: i64) -> i64 {
    if vec_ptr == 0 {
        return 1;
    }
    unsafe {
        let length = *((vec_ptr as *const i64).offset(1));
        if length == 0 { 1 } else { 0 }
    }
}

/// Clone a Vec into a new independent Vec.
extern "C" fn bunker_vec_clone(vec_ptr: i64) -> i64 {
    let new_vec = bunker_vec_new();
    if vec_ptr == 0 || new_vec == 0 {
        return new_vec;
    }
    unsafe {
        let header = vec_ptr as *const i64;
        let length = *header.offset(1);
        let data_ptr = *header.offset(2) as *const i64;
        if !data_ptr.is_null() {
            for i in 0..length {
                let val = *data_ptr.offset(i as isize);
                bunker_vec_push(new_vec, val);
            }
        }
    }
    new_vec
}

/// In-place reverse the elements of a Vec. Returns 1 on success, 0 on error.
extern "C" fn bunker_vec_reverse(vec_ptr: i64) -> i64 {
    if vec_ptr == 0 {
        return 0;
    }
    unsafe {
        let header = vec_ptr as *mut i64;
        let length = *header.offset(1);
        let data_ptr = *header.offset(2) as *mut i64;
        if length > 1 && !data_ptr.is_null() {
            let mut i: isize = 0;
            let mut j: isize = (length - 1) as isize;
            while i < j {
                let tmp = *data_ptr.offset(i);
                *data_ptr.offset(i) = *data_ptr.offset(j);
                *data_ptr.offset(j) = tmp;
                i += 1;
                j -= 1;
            }
        }
    }
    1
}

/// Map each element of a Vec using a function pointer fn(T) -> U.
extern "C" fn bunker_vec_map(vec_ptr: i64, fn_ptr: i64) -> i64 {
    let new_vec = bunker_vec_new();
    if vec_ptr == 0 || fn_ptr == 0 || new_vec == 0 {
        return new_vec;
    }
    unsafe {
        let header = vec_ptr as *const i64;
        let length = *header.offset(1);
        let data_ptr = *header.offset(2) as *const i64;
        let f: extern "C" fn(i64) -> i64 = std::mem::transmute(fn_ptr);
        if !data_ptr.is_null() {
            for i in 0..length {
                let val = *data_ptr.offset(i as isize);
                let mapped = f(val);
                bunker_vec_push(new_vec, mapped);
            }
        }
    }
    new_vec
}

/// Filter elements of a Vec using a predicate function pointer fn(T) -> bool.
extern "C" fn bunker_vec_filter(vec_ptr: i64, fn_ptr: i64) -> i64 {
    let new_vec = bunker_vec_new();
    if vec_ptr == 0 || fn_ptr == 0 || new_vec == 0 {
        return new_vec;
    }
    unsafe {
        let header = vec_ptr as *const i64;
        let length = *header.offset(1);
        let data_ptr = *header.offset(2) as *const i64;
        let f: extern "C" fn(i64) -> i64 = std::mem::transmute(fn_ptr);
        if !data_ptr.is_null() {
            for i in 0..length {
                let val = *data_ptr.offset(i as isize);
                if f(val) != 0 {
                    bunker_vec_push(new_vec, val);
                }
            }
        }
    }
    new_vec
}

/// Left-fold elements of a Vec using an accumulator function pointer fn(U, T) -> U.
extern "C" fn bunker_vec_fold(vec_ptr: i64, init: i64, fn_ptr: i64) -> i64 {
    if vec_ptr == 0 || fn_ptr == 0 {
        return init;
    }
    unsafe {
        let header = vec_ptr as *const i64;
        let length = *header.offset(1);
        let data_ptr = *header.offset(2) as *const i64;
        let f: extern "C" fn(i64, i64) -> i64 = std::mem::transmute(fn_ptr);
        let mut acc = init;
        if !data_ptr.is_null() {
            for i in 0..length {
                let val = *data_ptr.offset(i as isize);
                acc = f(acc, val);
            }
        }
        acc
    }
}

/// Find first element of a Vec satisfying predicate fn(T) -> bool, returning Option<T>.
extern "C" fn bunker_vec_find(vec_ptr: i64, fn_ptr: i64) -> i64 {
    if vec_ptr == 0 || fn_ptr == 0 {
        return 0;
    }
    unsafe {
        let header = vec_ptr as *const i64;
        let length = *header.offset(1);
        let data_ptr = *header.offset(2) as *const i64;
        let f: extern "C" fn(i64) -> i64 = std::mem::transmute(fn_ptr);
        if !data_ptr.is_null() {
            for i in 0..length {
                let val = *data_ptr.offset(i as isize);
                if f(val) != 0 {
                    return bunker_option_some(val);
                }
            }
        }
    }
    0
}

// ============================================================================
// Result<T, E> Runtime Functions
// ============================================================================
// Result layout: [tag: i64][value: i64]
// tag = 0 means Ok, value is the success value
// tag = 1 means Err, value is the error value

const RESULT_SIZE: i64 = 16; // 8 bytes tag + 8 bytes value

/// Create an Ok result with the given value.
extern "C" fn bunker_result_ok(value: i64) -> i64 {
    let layout = std::alloc::Layout::from_size_align(RESULT_SIZE as usize, 8).unwrap();
    let ptr = unsafe { std::alloc::alloc_zeroed(layout) };
    if ptr.is_null() {
        return 0;
    }

    unsafe {
        *(ptr as *mut i64) = 0; // Ok tag
        *((ptr as *mut i64).offset(1)) = value;
    }

    ptr as i64
}

/// Create an Err result with the given error value.
extern "C" fn bunker_result_err(error: i64) -> i64 {
    let layout = std::alloc::Layout::from_size_align(RESULT_SIZE as usize, 8).unwrap();
    let ptr = unsafe { std::alloc::alloc_zeroed(layout) };
    if ptr.is_null() {
        return 0;
    }

    unsafe {
        *(ptr as *mut i64) = 1; // Err tag
        *((ptr as *mut i64).offset(1)) = error;
    }

    ptr as i64
}

/// Check if a result is Ok. Returns 1 if Ok, 0 if Err.
extern "C" fn bunker_result_is_ok(result_ptr: i64) -> i64 {
    if result_ptr == 0 {
        return 0;
    }

    unsafe {
        let tag = *(result_ptr as *const i64);
        if tag == 0 {
            1
        } else {
            0
        }
    }
}

/// Check if a result is Err. Returns 1 if Err, 0 if Ok.
extern "C" fn bunker_result_is_err(result_ptr: i64) -> i64 {
    if result_ptr == 0 {
        return 1; // Null is treated as error
    }

    unsafe {
        let tag = *(result_ptr as *const i64);
        if tag == 1 {
            1
        } else {
            0
        }
    }
}

/// Unwrap the Ok value. Returns 0 if it's an Err (panics in production).
extern "C" fn bunker_result_unwrap(result_ptr: i64) -> i64 {
    if result_ptr == 0 {
        return 0;
    }

    unsafe {
        let tag = *(result_ptr as *const i64);
        if tag != 0 {
            // Would panic in production, but for now return 0
            return 0;
        }
        *((result_ptr as *const i64).offset(1))
    }
}

/// Unwrap the Err value. Returns 0 if it's Ok.
extern "C" fn bunker_result_unwrap_err(result_ptr: i64) -> i64 {
    if result_ptr == 0 {
        return 0;
    }

    unsafe {
        let tag = *(result_ptr as *const i64);
        if tag != 1 {
            return 0;
        }
        *((result_ptr as *const i64).offset(1))
    }
}

/// Get the tag of a result (0 = Ok, 1 = Err).
extern "C" fn bunker_result_tag(result_ptr: i64) -> i64 {
    if result_ptr == 0 {
        return 1; // Null is treated as Err
    }

    unsafe { *(result_ptr as *const i64) }
}

/// Get the value from a result (Ok or Err value).
extern "C" fn bunker_result_value(result_ptr: i64) -> i64 {
    if result_ptr == 0 {
        return 0;
    }

    unsafe { *((result_ptr as *const i64).offset(1)) }
}

// ============================================================================
// HashMap<K, V> Runtime Functions
// ============================================================================
// HashMap layout: [capacity: i64][length: i64][entries_ptr: *mut Entry]
// Entry layout: [key: i64][value: i64][hash: i64][occupied: i64]
// Using open addressing with linear probing

const HASHMAP_HEADER_SIZE: i64 = 32; // capacity + length + entries_ptr + key_type
const HASHMAP_ENTRY_SIZE: i64 = 32; // key + value + hash + occupied
const HASHMAP_INITIAL_CAPACITY: i64 = 16;

/// Simple hash function for i64 keys (using FNV-1a-like hash)
fn hash_i64(key: i64) -> i64 {
    let mut h = 0xcbf29ce484222325u64;
    let bytes = key.to_le_bytes();
    for b in bytes {
        h ^= b as u64;
        h = h.wrapping_mul(0x100000001b3);
    }
    h as i64
}

fn hash_str(s: &str) -> i64 {
    let mut h = 0xcbf29ce484222325u64;
    for b in s.as_bytes() {
        h ^= *b as u64;
        h = h.wrapping_mul(0x100000001b3);
    }
    h as i64
}

unsafe fn hashmap_get_key_hash(key_type: i64, key: i64) -> i64 {
    if key_type == 1 {
        if let Some(s) = read_bunker_string(key) {
            hash_str(&s)
        } else {
            0
        }
    } else {
        hash_i64(key)
    }
}

unsafe fn hashmap_key_eq(key_type: i64, k1: i64, k2: i64) -> bool {
    if key_type == 1 {
        if k1 == k2 {
            return true;
        }
        let s1 = read_bunker_string(k1);
        let s2 = read_bunker_string(k2);
        match (s1, s2) {
            (Some(a), Some(b)) => a == b,
            _ => false,
        }
    } else {
        k1 == k2
    }
}

/// Create a new empty HashMap.
extern "C" fn bunker_hashmap_new() -> i64 {
    let header_layout =
        std::alloc::Layout::from_size_align(HASHMAP_HEADER_SIZE as usize, 8).unwrap();
    let header_ptr = unsafe { std::alloc::alloc_zeroed(header_layout) };
    if header_ptr.is_null() {
        return 0;
    }

    let entries_size = HASHMAP_INITIAL_CAPACITY * HASHMAP_ENTRY_SIZE;
    let entries_layout = std::alloc::Layout::from_size_align(entries_size as usize, 8).unwrap();
    let entries_ptr = unsafe { std::alloc::alloc_zeroed(entries_layout) };
    if entries_ptr.is_null() {
        unsafe {
            std::alloc::dealloc(header_ptr, header_layout);
        }
        return 0;
    }

    unsafe {
        *(header_ptr as *mut i64) = HASHMAP_INITIAL_CAPACITY; // capacity
        *((header_ptr as *mut i64).offset(1)) = 0; // length
        *((header_ptr as *mut i64).offset(2)) = entries_ptr as i64; // entries_ptr
        *((header_ptr as *mut i64).offset(3)) = 0; // key_type (default 0 = int)
    }

    header_ptr as i64
}

extern "C" fn bunker_hashmap_new_str() -> i64 {
    let ptr = bunker_hashmap_new();
    if ptr != 0 {
        unsafe {
            *((ptr as *mut i64).offset(3)) = 1;
        }
    }
    ptr
}

/// Insert a key-value pair into the HashMap. Returns 1 on success.
extern "C" fn bunker_hashmap_insert(map_ptr: i64, key: i64, value: i64) -> i64 {
    if map_ptr == 0 {
        return 0;
    }

    unsafe {
        let capacity = *(map_ptr as *const i64);
        let length = *((map_ptr as *const i64).offset(1));
        let entries_ptr = *((map_ptr as *const i64).offset(2)) as *mut i64;
        let key_type = *((map_ptr as *const i64).offset(3));

        // Check if we need to grow (load factor > 0.75)
        if length * 4 >= capacity * 3 {
            // Grow the hashmap
            if bunker_hashmap_grow(map_ptr) == 0 {
                return 0;
            }
            // Re-read after grow
            return bunker_hashmap_insert(map_ptr, key, value);
        }

        let hash = hashmap_get_key_hash(key_type, key);
        let mut idx = (hash & (capacity - 1)) as isize;

        // Linear probing
        loop {
            let entry_ptr =
                (entries_ptr as *mut u8).offset(idx * HASHMAP_ENTRY_SIZE as isize) as *mut i64;
            let occupied = *entry_ptr.offset(3);

            if occupied == 0 {
                // Empty slot - insert here
                *entry_ptr = key; // key
                *entry_ptr.offset(1) = value; // value
                *entry_ptr.offset(2) = hash; // hash
                *entry_ptr.offset(3) = 1; // occupied

                // Update length
                *((map_ptr as *mut i64).offset(1)) = length + 1;
                return 1;
            } else if hashmap_key_eq(key_type, *entry_ptr, key) {
                // Key already exists - update value
                *entry_ptr.offset(1) = value;
                return 1;
            }

            // Move to next slot
            idx = (idx + 1) & (capacity as isize - 1);
        }
    }
}

extern "C" fn bunker_hashmap_insert_str(map_ptr: i64, key: i64, value: i64) -> i64 {
    if map_ptr != 0 {
        unsafe {
            *((map_ptr as *mut i64).offset(3)) = 1;
        }
    }
    bunker_hashmap_insert(map_ptr, key, value)
}

/// Grow the HashMap when load factor exceeds threshold.
extern "C" fn bunker_hashmap_grow(map_ptr: i64) -> i64 {
    if map_ptr == 0 {
        return 0;
    }

    unsafe {
        let old_capacity = *(map_ptr as *const i64);
        let old_entries_ptr = *((map_ptr as *const i64).offset(2)) as *mut i8;
        let old_entries_size = old_capacity * HASHMAP_ENTRY_SIZE;
        let old_entries_layout =
            std::alloc::Layout::from_size_align(old_entries_size as usize, 8).unwrap();
        let key_type = *((map_ptr as *const i64).offset(3));

        let new_capacity = old_capacity * 2;
        let new_entries_size = new_capacity * HASHMAP_ENTRY_SIZE;
        let new_entries_layout =
            std::alloc::Layout::from_size_align(new_entries_size as usize, 8).unwrap();
        let new_entries_ptr = std::alloc::alloc_zeroed(new_entries_layout);
        if new_entries_ptr.is_null() {
            return 0;
        }

        // Re-insert all entries from old table
        *(map_ptr as *mut i64) = new_capacity;
        *((map_ptr as *mut i64).offset(1)) = 0;
        *((map_ptr as *mut i64).offset(2)) = new_entries_ptr as i64;

        for i in 0..old_capacity {
            let entry_ptr = (old_entries_ptr as *const u8)
                .offset(i as isize * HASHMAP_ENTRY_SIZE as isize)
                as *const i64;
            let occupied = *entry_ptr.offset(3);

            if occupied != 0 {
                let key = *entry_ptr;
                let value = *entry_ptr.offset(1);

                // Insert into new table (call without recursion risk since we doubled capacity)
                let hash = hashmap_get_key_hash(key_type, key);
                let mut idx = (hash & (new_capacity - 1)) as isize;

                loop {
                    let new_entry_ptr =
                        new_entries_ptr.offset(idx * HASHMAP_ENTRY_SIZE as isize) as *mut i64;
                    let new_occupied = *new_entry_ptr.offset(3);

                    if new_occupied == 0 {
                        *new_entry_ptr = key;
                        *new_entry_ptr.offset(1) = value;
                        *new_entry_ptr.offset(2) = hash;
                        *new_entry_ptr.offset(3) = 1;

                        let len = *((map_ptr as *const i64).offset(1));
                        *((map_ptr as *mut i64).offset(1)) = len + 1;
                        break;
                    }

                    idx = (idx + 1) & (new_capacity as isize - 1);
                }
            }
        }

        std::alloc::dealloc(old_entries_ptr as *mut u8, old_entries_layout);
        1
    }
}

/// Get a value from the HashMap. Returns 0 if not found (use contains to check).
extern "C" fn bunker_hashmap_get(map_ptr: i64, key: i64) -> i64 {
    if map_ptr == 0 {
        return 0;
    }

    unsafe {
        let capacity = *(map_ptr as *const i64);
        let entries_ptr = *((map_ptr as *const i64).offset(2)) as *const i64;
        let key_type = *((map_ptr as *const i64).offset(3));

        let hash = hashmap_get_key_hash(key_type, key);
        let mut idx = (hash & (capacity - 1)) as isize;
        let start_idx = idx;

        loop {
            let entry_ptr =
                (entries_ptr as *const u8).offset(idx * HASHMAP_ENTRY_SIZE as isize) as *const i64;
            let occupied = *entry_ptr.offset(3);

            if occupied == 0 {
                // Empty slot - key not found
                return 0;
            } else if hashmap_key_eq(key_type, *entry_ptr, key) {
                // Found the key
                return *entry_ptr.offset(1);
            }

            idx = (idx + 1) & (capacity as isize - 1);
            if idx == start_idx {
                // Wrapped around - not found
                return 0;
            }
        }
    }
}

/// Check if the HashMap contains a key. Returns 1 if found, 0 otherwise.
extern "C" fn bunker_hashmap_contains(map_ptr: i64, key: i64) -> i64 {
    if map_ptr == 0 {
        return 0;
    }

    unsafe {
        let capacity = *(map_ptr as *const i64);
        let entries_ptr = *((map_ptr as *const i64).offset(2)) as *const i64;
        let key_type = *((map_ptr as *const i64).offset(3));

        let hash = hashmap_get_key_hash(key_type, key);
        let mut idx = (hash & (capacity - 1)) as isize;
        let start_idx = idx;

        loop {
            let entry_ptr =
                (entries_ptr as *const u8).offset(idx * HASHMAP_ENTRY_SIZE as isize) as *const i64;
            let occupied = *entry_ptr.offset(3);

            if occupied == 0 {
                return 0;
            } else if hashmap_key_eq(key_type, *entry_ptr, key) {
                return 1;
            }

            idx = (idx + 1) & (capacity as isize - 1);
            if idx == start_idx {
                return 0;
            }
        }
    }
}

/// Remove a key from the HashMap. Returns 1 if removed, 0 if not found.
extern "C" fn bunker_hashmap_remove(map_ptr: i64, key: i64) -> i64 {
    if map_ptr == 0 {
        return 0;
    }

    unsafe {
        let capacity = *(map_ptr as *const i64);
        let entries_ptr = *((map_ptr as *const i64).offset(2)) as *mut i64;
        let key_type = *((map_ptr as *const i64).offset(3));

        let hash = hashmap_get_key_hash(key_type, key);
        let mut idx = (hash & (capacity - 1)) as isize;
        let start_idx = idx;

        loop {
            let entry_ptr =
                (entries_ptr as *mut u8).offset(idx * HASHMAP_ENTRY_SIZE as isize) as *mut i64;
            let occupied = *entry_ptr.offset(3);

            if occupied == 0 {
                return 0;
            } else if hashmap_key_eq(key_type, *entry_ptr, key) {
                // Mark as deleted (set occupied to 0)
                *entry_ptr.offset(3) = 0;

                // Update length
                let length = *((map_ptr as *const i64).offset(1));
                *((map_ptr as *mut i64).offset(1)) = length - 1;

                return 1;
            }

            idx = (idx + 1) & (capacity as isize - 1);
            if idx == start_idx {
                return 0;
            }
        }
    }
}

extern "C" fn bunker_hashmap_len(map_ptr: i64) -> i64 {
    if map_ptr == 0 {
        return 0;
    }

    unsafe { *((map_ptr as *const i64).offset(1)) }
}

/// Clear all entries in the HashMap.
extern "C" fn bunker_hashmap_clear(map_ptr: i64) {
    if map_ptr == 0 {
        return;
    }

    unsafe {
        let capacity = *(map_ptr as *const i64);
        let entries_ptr = *((map_ptr as *const i64).offset(2)) as *mut u8;

        // Zero out all entries
        std::ptr::write_bytes(entries_ptr, 0, (capacity * HASHMAP_ENTRY_SIZE) as usize);

        // Reset length
        *((map_ptr as *mut i64).offset(1)) = 0;
    }
}

/// Get all keys from the HashMap as a Vec.
extern "C" fn bunker_hashmap_keys(map_ptr: i64) -> i64 {
    if map_ptr == 0 {
        return bunker_vec_new();
    }

    let vec_ptr = bunker_vec_new();
    if vec_ptr == 0 {
        return 0;
    }

    unsafe {
        let capacity = *(map_ptr as *const i64);
        let entries_ptr = *((map_ptr as *const i64).offset(2)) as *const i64;

        for i in 0..capacity {
            let entry_ptr = (entries_ptr as *const u8)
                .offset(i as isize * HASHMAP_ENTRY_SIZE as isize)
                as *const i64;
            let occupied = *entry_ptr.offset(3);

            if occupied != 0 {
                let key = *entry_ptr;
                bunker_vec_push(vec_ptr, key);
            }
        }
    }

    vec_ptr
}

/// Check if the HashMap is empty. Returns 1 if empty, 0 otherwise.
extern "C" fn bunker_hashmap_is_empty(map_ptr: i64) -> i64 {
    if map_ptr == 0 {
        return 1;
    }
    unsafe {
        let length = *((map_ptr as *const i64).offset(1));
        if length == 0 { 1 } else { 0 }
    }
}

/// Get all values from the HashMap as a Vec.
extern "C" fn bunker_hashmap_values(map_ptr: i64) -> i64 {
    if map_ptr == 0 {
        return bunker_vec_new();
    }

    let vec_ptr = bunker_vec_new();
    if vec_ptr == 0 {
        return 0;
    }

    unsafe {
        let capacity = *(map_ptr as *const i64);
        let entries_ptr = *((map_ptr as *const i64).offset(2)) as *const i64;

        for i in 0..capacity {
            let entry_ptr = (entries_ptr as *const u8)
                .offset(i as isize * HASHMAP_ENTRY_SIZE as isize)
                as *const i64;
            let occupied = *entry_ptr.offset(3);

            if occupied != 0 {
                let val = *entry_ptr.offset(1);
                bunker_vec_push(vec_ptr, val);
            }
        }
    }

    vec_ptr
}

/// Allocate an 8-byte Option::Some box containing `val`.
extern "C" fn bunker_option_some(val: i64) -> i64 {
    let layout = std::alloc::Layout::from_size_align(8, 8).unwrap();
    let ptr = unsafe { std::alloc::alloc_zeroed(layout) };
    if ptr.is_null() {
        return 0;
    }
    unsafe {
        *(ptr as *mut i64) = val;
    }
    ptr as i64
}

/// Recoverable hashmap get returning Option<V> (Some(val) if found, 0 / None if not found).
extern "C" fn bunker_hashmap_get_opt(map_ptr: i64, key: i64) -> i64 {
    if map_ptr == 0 {
        return 0;
    }
    unsafe {
        let capacity = *(map_ptr as *const i64);
        let entries_ptr = *((map_ptr as *const i64).offset(2)) as *const i64;
        let key_type = *((map_ptr as *const i64).offset(3));
        let hash = hashmap_get_key_hash(key_type, key);
        let mut idx = (hash & (capacity - 1)) as isize;
        let start_idx = idx;

        loop {
            let entry_ptr =
                (entries_ptr as *const u8).offset(idx * HASHMAP_ENTRY_SIZE as isize) as *const i64;
            let occupied = *entry_ptr.offset(3);
            if occupied == 0 {
                return 0;
            } else if hashmap_key_eq(key_type, *entry_ptr, key) {
                let val = *entry_ptr.offset(1);
                return bunker_option_some(val);
            }
            idx = (idx + 1) & (capacity as isize - 1);
            if idx == start_idx {
                return 0;
            }
        }
    }
}

/// Recoverable vec get returning Option<T> (Some(val) if in bounds, 0 / None if out of bounds).
extern "C" fn bunker_vec_get_opt(vec_ptr: i64, index: i64) -> i64 {
    if vec_ptr == 0 {
        return 0;
    }
    unsafe {
        let header = vec_ptr as *mut i64;
        let length = *header.offset(1);
        if index < 0 || index >= length {
            return 0;
        }
        let data_ptr = *header.offset(2) as *mut i64;
        let val = *data_ptr.offset(index as isize);
        bunker_option_some(val)
    }
}

/// Recoverable vec pop returning Option<T> (Some(val) if non-empty, 0 / None if empty).
extern "C" fn bunker_vec_pop_opt(vec_ptr: i64) -> i64 {
    if vec_ptr == 0 {
        return 0;
    }
    unsafe {
        let header = vec_ptr as *mut i64;
        let length = *header.offset(1);
        if length <= 0 {
            return 0;
        }
        let data_ptr = *header.offset(2) as *mut i64;
        let val = *data_ptr.offset((length - 1) as isize);
        *header.offset(1) = length - 1;
        bunker_option_some(val)
    }
}

/// Recoverable read_file returning Result<str, str> (Ok(content) or Err(msg)).
extern "C" fn bunker_read_file_result(path_ptr: i64) -> i64 {
    let path_str = unsafe { read_bunker_string(path_ptr) };
    let Some(path_str) = path_str else {
        let err_ptr = alloc_bunker_string("null path");
        return bunker_result_err(err_ptr);
    };
    match std::fs::read_to_string(&path_str) {
        Ok(contents) => {
            let ok_ptr = alloc_bunker_string(&contents);
            bunker_result_ok(ok_ptr)
        }
        Err(e) => {
            let err_ptr = alloc_bunker_string(&e.to_string());
            bunker_result_err(err_ptr)
        }
    }
}

/// Recoverable write_file returning Result<bool, str> (Ok(true) or Err(msg)).
extern "C" fn bunker_write_file_result(path_ptr: i64, content_ptr: i64) -> i64 {
    let path_str = unsafe { read_bunker_string(path_ptr) };
    let Some(path_str) = path_str else {
        let err_ptr = alloc_bunker_string("null path");
        return bunker_result_err(err_ptr);
    };
    let content_str = unsafe { read_bunker_string(content_ptr) };
    let Some(content_str) = content_str else {
        let err_ptr = alloc_bunker_string("null content");
        return bunker_result_err(err_ptr);
    };
    match std::fs::write(&path_str, &content_str) {
        Ok(()) => bunker_result_ok(1),
        Err(e) => {
            let err_ptr = alloc_bunker_string(&e.to_string());
            bunker_result_err(err_ptr)
        }
    }
}

/// Recoverable parse_int returning Result<i64, str> (Ok(val) or Err(msg)).
extern "C" fn bunker_parse_int_result(str_ptr: i64) -> i64 {
    let s = unsafe { read_bunker_string(str_ptr) };
    let Some(s) = s else {
        let err_ptr = alloc_bunker_string("null string");
        return bunker_result_err(err_ptr);
    };
    match s.trim().parse::<i64>() {
        Ok(val) => bunker_result_ok(val),
        Err(_) => {
            let err_ptr = alloc_bunker_string("invalid integer format");
            bunker_result_err(err_ptr)
        }
    }
}

extern "C" fn bunker_str_index_of(str_ptr: i64, needle_ptr: i64) -> i64 {
    let s = unsafe { read_bunker_string(str_ptr) };
    let needle = unsafe { read_bunker_string(needle_ptr) };
    match (s, needle) {
        (Some(s), Some(needle)) => match s.find(&needle) {
            Some(idx) => idx as i64,
            None => -1,
        },
        _ => -1,
    }
}

extern "C" fn bunker_str_replace(str_ptr: i64, from_ptr: i64, to_ptr: i64) -> i64 {
    let s = unsafe { read_bunker_string(str_ptr) }.unwrap_or_default();
    let from = unsafe { read_bunker_string(from_ptr) }.unwrap_or_default();
    let to = unsafe { read_bunker_string(to_ptr) }.unwrap_or_default();
    let replaced = s.replace(&from, &to);
    alloc_bunker_string(&replaced)
}

extern "C" fn bunker_str_split(str_ptr: i64, delim_ptr: i64) -> i64 {
    let s = unsafe { read_bunker_string(str_ptr) }.unwrap_or_default();
    let delim = unsafe { read_bunker_string(delim_ptr) }.unwrap_or_default();
    let vec_ptr = bunker_vec_new();
    if delim.is_empty() {
        for ch in s.chars() {
            let part_ptr = alloc_bunker_string(&ch.to_string());
            bunker_vec_push(vec_ptr, part_ptr);
        }
    } else {
        for part in s.split(&delim) {
            let part_ptr = alloc_bunker_string(part);
            bunker_vec_push(vec_ptr, part_ptr);
        }
    }
    vec_ptr
}

extern "C" fn bunker_str_to_upper(str_ptr: i64) -> i64 {
    let s = unsafe { read_bunker_string(str_ptr) }.unwrap_or_default();
    alloc_bunker_string(&s.to_ascii_uppercase())
}

extern "C" fn bunker_str_to_lower(str_ptr: i64) -> i64 {
    let s = unsafe { read_bunker_string(str_ptr) }.unwrap_or_default();
    alloc_bunker_string(&s.to_ascii_lowercase())
}

extern "C" fn bunker_str_repeat(str_ptr: i64, count: i64) -> i64 {
    if count <= 0 {
        return alloc_bunker_string("");
    }
    let s = unsafe { read_bunker_string(str_ptr) }.unwrap_or_default();
    alloc_bunker_string(&s.repeat(count as usize))
}

extern "C" fn bunker_path_join(a_ptr: i64, b_ptr: i64) -> i64 {
    let a = unsafe { read_bunker_string(a_ptr) }.unwrap_or_default();
    let b = unsafe { read_bunker_string(b_ptr) }.unwrap_or_default();
    let a_clean = a.trim_end_matches(|c| c == '/' || c == '\\');
    let b_clean = b.trim_start_matches(|c| c == '/' || c == '\\');
    let joined = if a_clean.is_empty() {
        b_clean.to_string()
    } else if b_clean.is_empty() {
        a_clean.to_string()
    } else {
        format!("{}/{}", a_clean, b_clean)
    };
    alloc_bunker_string(&joined)
}

extern "C" fn bunker_path_dir(path_ptr: i64) -> i64 {
    let p = unsafe { read_bunker_string(path_ptr) }.unwrap_or_default();
    let last_slash = p.rfind(|c| c == '/' || c == '\\');
    let dir = match last_slash {
        Some(idx) => &p[..idx],
        None => "",
    };
    alloc_bunker_string(dir)
}

extern "C" fn bunker_path_base(path_ptr: i64) -> i64 {
    let p = unsafe { read_bunker_string(path_ptr) }.unwrap_or_default();
    let last_slash = p.rfind(|c| c == '/' || c == '\\');
    let base = match last_slash {
        Some(idx) => &p[idx + 1..],
        None => &p[..],
    };
    alloc_bunker_string(base)
}

extern "C" fn bunker_path_ext(path_ptr: i64) -> i64 {
    let p = unsafe { read_bunker_string(path_ptr) }.unwrap_or_default();
    let base = match p.rfind(|c| c == '/' || c == '\\') {
        Some(idx) => &p[idx + 1..],
        None => &p[..],
    };
    let ext = match base.rfind('.') {
        Some(idx) if idx > 0 && idx + 1 < base.len() => &base[idx + 1..],
        _ => "",
    };
    alloc_bunker_string(ext)
}

extern "C" fn bunker_path_is_abs(path_ptr: i64) -> i64 {
    let p = unsafe { read_bunker_string(path_ptr) }.unwrap_or_default();
    if p.is_empty() {
        return 0;
    }
    let bytes = p.as_bytes();
    let is_abs = bytes[0] == b'/' || bytes[0] == b'\\' || (bytes.len() >= 2 && bytes[1] == b':');
    if is_abs { 1 } else { 0 }
}

extern "C" fn bunker_env_var(key_ptr: i64) -> i64 {
    let key = unsafe { read_bunker_string(key_ptr) };
    let Some(key) = key else {
        let err_ptr = alloc_bunker_string("null key");
        return bunker_result_err(err_ptr);
    };
    match std::env::var(&key) {
        Ok(val) => {
            let ok_ptr = alloc_bunker_string(&val);
            bunker_result_ok(ok_ptr)
        }
        Err(e) => {
            let err_ptr = alloc_bunker_string(&e.to_string());
            bunker_result_err(err_ptr)
        }
    }
}

extern "C" fn bunker_env_get(key_ptr: i64) -> i64 {
    let key = unsafe { read_bunker_string(key_ptr) };
    let Some(key) = key else {
        return 0; // None
    };
    match std::env::var(&key) {
        Ok(val) => {
            let ok_ptr = alloc_bunker_string(&val);
            bunker_option_some(ok_ptr)
        }
        Err(_) => 0, // None
    }
}

extern "C" fn bunker_env_set(key_ptr: i64, val_ptr: i64) -> i64 {
    let key = unsafe { read_bunker_string(key_ptr) };
    let val = unsafe { read_bunker_string(val_ptr) };
    if let (Some(key), Some(val)) = (key, val) {
        std::env::set_var(&key, &val);
        1
    } else {
        0
    }
}

extern "C" fn bunker_env_has(key_ptr: i64) -> i64 {
    let key = unsafe { read_bunker_string(key_ptr) };
    if let Some(key) = key {
        if std::env::var(&key).is_ok() { 1 } else { 0 }
    } else {
        0
    }
}

extern "C" fn bunker_time_now_ms() -> i64 {
    match std::time::SystemTime::now().duration_since(std::time::UNIX_EPOCH) {
        Ok(d) => d.as_millis() as i64,
        Err(_) => 0,
    }
}

extern "C" fn bunker_time_now_unix() -> i64 {
    match std::time::SystemTime::now().duration_since(std::time::UNIX_EPOCH) {
        Ok(d) => d.as_secs() as i64,
        Err(_) => 0,
    }
}

// ============================================================================
// Byte Buffer Implementation
// ============================================================================
// Layout: [capacity: i64][length: i64][data_ptr: *mut u8]

const BYTES_HEADER_SIZE: i64 = 24;

extern "C" fn bunker_bytes_new(capacity: i64) -> i64 {
    let cap = if capacity < 8 { 8 } else { capacity };
    let header_layout = std::alloc::Layout::from_size_align(BYTES_HEADER_SIZE as usize, 8).unwrap();
    let header_ptr = unsafe { std::alloc::alloc_zeroed(header_layout) };
    if header_ptr.is_null() {
        return 0;
    }
    let data_layout = std::alloc::Layout::from_size_align(cap as usize, 1).unwrap();
    let data_ptr = unsafe { std::alloc::alloc_zeroed(data_layout) };
    if data_ptr.is_null() {
        unsafe { std::alloc::dealloc(header_ptr, header_layout); }
        return 0;
    }
    unsafe {
        *(header_ptr as *mut i64) = cap;
        *((header_ptr as *mut i64).offset(1)) = 0;
        *((header_ptr as *mut i64).offset(2)) = data_ptr as i64;
    }
    header_ptr as i64
}

extern "C" fn bunker_bytes_len(handle: i64) -> i64 {
    if handle == 0 { return 0; }
    unsafe {
        let header = handle as *const i64;
        *header.offset(1)
    }
}

extern "C" fn bunker_bytes_capacity(handle: i64) -> i64 {
    if handle == 0 { return 0; }
    unsafe {
        let header = handle as *const i64;
        *header
    }
}

extern "C" fn bunker_bytes_get(handle: i64, index: i64) -> i32 {
    if handle == 0 || index < 0 { return 0; }
    unsafe {
        let header = handle as *const i64;
        let len = *header.offset(1);
        if index >= len { return 0; }
        let data = *header.offset(2) as *const u8;
        *data.add(index as usize) as i32
    }
}

extern "C" fn bunker_bytes_set(handle: i64, index: i64, val: i32) -> i32 {
    if handle == 0 || index < 0 { return 0; }
    unsafe {
        let header = handle as *mut i64;
        let len = *header.offset(1);
        if index >= len { return 0; }
        let data = *header.offset(2) as *mut u8;
        *data.add(index as usize) = (val & 0xFF) as u8;
        1
    }
}

extern "C" fn bunker_bytes_push(handle: i64, val: i32) -> i32 {
    if handle == 0 { return 0; }
    unsafe {
        let header = handle as *mut i64;
        let capacity = *header;
        let length = *header.offset(1);
        let data_ptr = *header.offset(2) as *mut u8;

        if length >= capacity {
            let new_capacity = capacity * 2;
            let old_layout = std::alloc::Layout::from_size_align(capacity as usize, 1).unwrap();
            let new_data_ptr = std::alloc::realloc(data_ptr, old_layout, new_capacity as usize);
            if new_data_ptr.is_null() {
                return 0;
            }
            *header = new_capacity;
            *header.offset(2) = new_data_ptr as i64;
        }

        let cur_data = *header.offset(2) as *mut u8;
        *cur_data.add(length as usize) = (val & 0xFF) as u8;
        *header.offset(1) = length + 1;
        1
    }
}

extern "C" fn bunker_bytes_from_str(str_ptr: i64) -> i64 {
    if str_ptr == 0 { return bunker_bytes_new(8); }
    unsafe {
        let len = *(str_ptr as *const i64) as usize;
        let slice = std::slice::from_raw_parts((str_ptr + 8) as *const u8, len);
        let handle = bunker_bytes_new(len as i64);
        if handle == 0 { return 0; }
        let header = handle as *mut i64;
        let data_ptr = *header.offset(2) as *mut u8;
        std::ptr::copy_nonoverlapping(slice.as_ptr(), data_ptr, len);
        *header.offset(1) = len as i64;
        handle
    }
}

extern "C" fn bunker_bytes_to_str(handle: i64) -> i64 {
    if handle == 0 { return alloc_bunker_string(""); }
    unsafe {
        let header = handle as *const i64;
        let len = *header.offset(1) as usize;
        let data = *header.offset(2) as *const u8;
        let slice = std::slice::from_raw_parts(data, len);
        let s = std::str::from_utf8(slice).unwrap_or("");
        alloc_bunker_string(s)
    }
}

// ============================================================================
// Slices (D-008)
// Layout: [data_ptr: *const u8, len: i64, elem_size: i64] (24 bytes)
// ============================================================================

extern "C" fn bunker_slice_new(data_ptr: i64, len: i64, elem_size: i64) -> i64 {
    let layout = std::alloc::Layout::from_size_align(24, 8).unwrap();
    let ptr = unsafe { std::alloc::alloc(layout) as *mut i64 };
    if ptr.is_null() {
        return 0;
    }
    let safe_len = if len < 0 || data_ptr == 0 { 0 } else { len };
    let esize = if elem_size <= 0 { 8 } else { elem_size };
    unsafe {
        *ptr = data_ptr;
        *ptr.offset(1) = safe_len;
        *ptr.offset(2) = esize;
    }
    ptr as i64
}

extern "C" fn bunker_slice_len(slice_ptr: i64) -> i64 {
    if slice_ptr == 0 { return 0; }
    unsafe {
        let ptr = slice_ptr as *const i64;
        *ptr.offset(1)
    }
}

extern "C" fn bunker_slice_get(slice_ptr: i64, index: i64) -> i64 {
    if slice_ptr == 0 || index < 0 { return 0; }
    unsafe {
        let ptr = slice_ptr as *const i64;
        let data = *ptr as *const u8;
        let len = *ptr.offset(1);
        let esize = *ptr.offset(2);
        if data.is_null() || index >= len { return 0; }
        match esize {
            1 => *data.add(index as usize) as i64,
            2 => *(data.add((index * 2) as usize) as *const i16) as i64,
            4 => *(data.add((index * 4) as usize) as *const i32) as i64,
            _ => *(data.add((index * 8) as usize) as *const i64),
        }
    }
}

extern "C" fn bunker_slice_sub(slice_ptr: i64, start: i64, sub_len: i64) -> i64 {
    if slice_ptr == 0 || start < 0 || sub_len <= 0 {
        return bunker_slice_new(0, 0, 8);
    }
    unsafe {
        let ptr = slice_ptr as *const i64;
        let data = *ptr as *const u8;
        let len = *ptr.offset(1);
        let esize = *ptr.offset(2);
        if data.is_null() || start >= len {
            return bunker_slice_new(0, 0, esize);
        }
        let available = len - start;
        let actual_len = if sub_len > available { available } else { sub_len };
        let new_data = data.add((start * esize) as usize) as i64;
        bunker_slice_new(new_data, actual_len, esize)
    }
}

extern "C" fn bunker_slice_contains(slice_ptr: i64, item: i64) -> i8 {
    if slice_ptr == 0 { return 0; }
    unsafe {
        let ptr = slice_ptr as *const i64;
        let len = *ptr.offset(1);
        if len <= 0 { return 0; }
        for i in 0..len {
            if bunker_slice_get(slice_ptr, i) == item {
                return 1;
            }
        }
        0
    }
}

extern "C" fn bunker_slice_to_vec(slice_ptr: i64) -> i64 {
    let vec_handle = bunker_vec_new();
    if slice_ptr == 0 { return vec_handle; }
    unsafe {
        let ptr = slice_ptr as *const i64;
        let len = *ptr.offset(1);
        for i in 0..len {
            let val = bunker_slice_get(slice_ptr, i);
            bunker_vec_push(vec_handle, val);
        }
    }
    vec_handle
}

extern "C" fn bunker_vec_as_slice(vec_handle: i64) -> i64 {
    if vec_handle == 0 { return bunker_slice_new(0, 0, 8); }
    unsafe {
        let header = vec_handle as *const i64;
        let len = *header.offset(1);
        let data = *header.offset(2);
        bunker_slice_new(data, len, 8)
    }
}

extern "C" fn bunker_vec_slice(vec_handle: i64, start: i64, sub_len: i64) -> i64 {
    let full_slice = bunker_vec_as_slice(vec_handle);
    bunker_slice_sub(full_slice, start, sub_len)
}

extern "C" fn bunker_bytes_as_slice(handle: i64) -> i64 {
    if handle == 0 { return bunker_slice_new(0, 0, 1); }
    unsafe {
        let header = handle as *const i64;
        let len = *header.offset(1);
        let data = *header.offset(2);
        bunker_slice_new(data, len, 1)
    }
}

extern "C" fn bunker_bytes_slice(handle: i64, start: i64, sub_len: i64) -> i64 {
    let full_slice = bunker_bytes_as_slice(handle);
    bunker_slice_sub(full_slice, start, sub_len)
}

// ============================================================================
// File and Path (D-013)
// ============================================================================

fn read_bunker_path(ptr: i64) -> Option<String> {
    if ptr == 0 { return None; }
    unsafe {
        let first_word = *(ptr as *const i64);
        if first_word > 0x10000 {
            if let Some(s) = read_bunker_string(first_word) {
                return Some(s);
            }
        }
        read_bunker_string(ptr)
    }
}

extern "C" fn bunker_path_exists(path_ptr: i64) -> i8 {
    let Some(p) = read_bunker_path(path_ptr) else { return 0; };
    if std::path::Path::new(&p).exists() { 1 } else { 0 }
}

extern "C" fn bunker_path_is_file(path_ptr: i64) -> i8 {
    let Some(p) = read_bunker_path(path_ptr) else { return 0; };
    if std::path::Path::new(&p).is_file() { 1 } else { 0 }
}

extern "C" fn bunker_path_is_dir(path_ptr: i64) -> i8 {
    let Some(p) = read_bunker_path(path_ptr) else { return 0; };
    if std::path::Path::new(&p).is_dir() { 1 } else { 0 }
}

extern "C" fn bunker_file_read(path_ptr: i64) -> i64 {
    let Some(path_str) = read_bunker_path(path_ptr) else {
        let err_ptr = alloc_bunker_string("null path");
        return bunker_result_err(err_ptr);
    };
    match std::fs::read_to_string(&path_str) {
        Ok(contents) => {
            let ok_ptr = alloc_bunker_string(&contents);
            bunker_result_ok(ok_ptr)
        }
        Err(e) => {
            let err_ptr = alloc_bunker_string(&e.to_string());
            bunker_result_err(err_ptr)
        }
    }
}

extern "C" fn bunker_file_write(path_ptr: i64, content_ptr: i64) -> i64 {
    let Some(path_str) = read_bunker_path(path_ptr) else {
        let err_ptr = alloc_bunker_string("null path");
        return bunker_result_err(err_ptr);
    };
    let content_str = unsafe { read_bunker_string(content_ptr) };
    let Some(content_str) = content_str else {
        let err_ptr = alloc_bunker_string("null content");
        return bunker_result_err(err_ptr);
    };
    match std::fs::write(&path_str, &content_str) {
        Ok(()) => bunker_result_ok(content_str.len() as i64),
        Err(e) => {
            let err_ptr = alloc_bunker_string(&e.to_string());
            bunker_result_err(err_ptr)
        }
    }
}

extern "C" fn bunker_file_size(path_ptr: i64) -> i64 {
    let Some(path_str) = read_bunker_path(path_ptr) else {
        let err_ptr = alloc_bunker_string("null path");
        return bunker_result_err(err_ptr);
    };
    match std::fs::metadata(&path_str) {
        Ok(meta) => bunker_result_ok(meta.len() as i64),
        Err(e) => {
            let err_ptr = alloc_bunker_string(&e.to_string());
            bunker_result_err(err_ptr)
        }
    }
}

extern "C" fn bunker_file_remove(path_ptr: i64) -> i64 {
    let Some(path_str) = read_bunker_path(path_ptr) else {
        let err_ptr = alloc_bunker_string("null path");
        return bunker_result_err(err_ptr);
    };
    match std::fs::remove_file(&path_str) {
        Ok(()) => bunker_result_ok(1),
        Err(e) => {
            let err_ptr = alloc_bunker_string(&e.to_string());
            bunker_result_err(err_ptr)
        }
    }
}

extern "C" fn bunker_file_read_bytes(path_ptr: i64) -> i64 {
    let Some(path_str) = read_bunker_path(path_ptr) else {
        let err_ptr = alloc_bunker_string("null path");
        return bunker_result_err(err_ptr);
    };
    match std::fs::read(&path_str) {
        Ok(data) => {
            let handle = bunker_bytes_new(data.len() as i64);
            if handle == 0 {
                let err_ptr = alloc_bunker_string("out of memory");
                return bunker_result_err(err_ptr);
            }
            unsafe {
                let header = handle as *mut i64;
                let dst = *header.offset(2) as *mut u8;
                std::ptr::copy_nonoverlapping(data.as_ptr(), dst, data.len());
                *header.offset(1) = data.len() as i64;
            }
            bunker_result_ok(handle)
        }
        Err(e) => {
            let err_ptr = alloc_bunker_string(&e.to_string());
            bunker_result_err(err_ptr)
        }
    }
}

extern "C" fn bunker_file_write_bytes(path_ptr: i64, bytes_handle: i64) -> i64 {
    let Some(path_str) = read_bunker_path(path_ptr) else {
        let err_ptr = alloc_bunker_string("null path");
        return bunker_result_err(err_ptr);
    };
    if bytes_handle == 0 {
        let err_ptr = alloc_bunker_string("null bytes");
        return bunker_result_err(err_ptr);
    }
    unsafe {
        let header = bytes_handle as *const i64;
        let len = *header.offset(1) as usize;
        let data = *header.offset(2) as *const u8;
        let slice = std::slice::from_raw_parts(data, len);
        match std::fs::write(&path_str, slice) {
            Ok(()) => bunker_result_ok(len as i64),
            Err(e) => {
                let err_ptr = alloc_bunker_string(&e.to_string());
                bunker_result_err(err_ptr)
            }
        }
    }
}

extern "C" fn bunker_dir_create(path_ptr: i64) -> i64 {
    let Some(path_str) = read_bunker_path(path_ptr) else {
        let err_ptr = alloc_bunker_string("null path");
        return bunker_result_err(err_ptr);
    };
    match std::fs::create_dir_all(&path_str) {
        Ok(()) => bunker_result_ok(1),
        Err(e) => {
            let err_ptr = alloc_bunker_string(&e.to_string());
            bunker_result_err(err_ptr)
        }
    }
}

extern "C" fn bunker_dir_remove(path_ptr: i64) -> i64 {
    let Some(path_str) = read_bunker_path(path_ptr) else {
        let err_ptr = alloc_bunker_string("null path");
        return bunker_result_err(err_ptr);
    };
    match std::fs::remove_dir_all(&path_str) {
        Ok(()) => bunker_result_ok(1),
        Err(e) => {
            let err_ptr = alloc_bunker_string(&e.to_string());
            bunker_result_err(err_ptr)
        }
    }
}

extern "C" fn bunker_process_is_sandboxed() -> i8 {
    if std::env::var("BUNKER_DISABLE_PROCESS").is_ok() || std::env::var("BUNKER_SANDBOX").is_ok() {
        1
    } else {
        0
    }
}

extern "C" fn bunker_process_pid() -> i32 {
    std::process::id() as i32
}

extern "C" fn bunker_process_exit(code: i32) {
    std::process::exit(code);
}

extern "C" fn bunker_process_run(cmd_ptr: i64) -> i64 {
    if bunker_process_is_sandboxed() != 0 {
        let err_ptr = alloc_bunker_string("process execution is disabled by sandbox policy");
        return bunker_result_err(err_ptr);
    }
    let Some(cmd_str) = (unsafe { read_bunker_string(cmd_ptr) }) else {
        let err_ptr = alloc_bunker_string("null command");
        return bunker_result_err(err_ptr);
    };

    #[cfg(target_os = "windows")]
    let output = std::process::Command::new("cmd")
        .args(["/C", &cmd_str])
        .output();

    #[cfg(not(target_os = "windows"))]
    let output = std::process::Command::new("sh")
        .args(["-c", &cmd_str])
        .output();

    match output {
        Ok(out) => {
            if out.status.success() {
                let stdout_str = String::from_utf8_lossy(&out.stdout);
                let ok_ptr = alloc_bunker_string(&stdout_str);
                bunker_result_ok(ok_ptr)
            } else {
                let stderr_str = String::from_utf8_lossy(&out.stderr);
                let err_msg = if !stderr_str.trim().is_empty() {
                    stderr_str.trim().to_string()
                } else {
                    format!("process exited with code {:?}", out.status.code())
                };
                let err_ptr = alloc_bunker_string(&err_msg);
                bunker_result_err(err_ptr)
            }
        }
        Err(e) => {
            let err_ptr = alloc_bunker_string(&e.to_string());
            bunker_result_err(err_ptr)
        }
    }
}

extern "C" fn bunker_process_run_status(cmd_ptr: i64) -> i64 {
    if bunker_process_is_sandboxed() != 0 {
        let err_ptr = alloc_bunker_string("process execution is disabled by sandbox policy");
        return bunker_result_err(err_ptr);
    }
    let Some(cmd_str) = (unsafe { read_bunker_string(cmd_ptr) }) else {
        let err_ptr = alloc_bunker_string("null command");
        return bunker_result_err(err_ptr);
    };

    #[cfg(target_os = "windows")]
    let status = std::process::Command::new("cmd")
        .args(["/C", &cmd_str])
        .status();

    #[cfg(not(target_os = "windows"))]
    let status = std::process::Command::new("sh")
        .args(["-c", &cmd_str])
        .status();

    match status {
        Ok(st) => {
            let code = st.code().unwrap_or(-1) as i64;
            bunker_result_ok(code)
        }
        Err(e) => {
            let err_ptr = alloc_bunker_string(&e.to_string());
            bunker_result_err(err_ptr)
        }
    }
}

// Free function to convert types (kept in sync with object codegen)
fn convert_ast_type(ty: &ast::Type) -> types::Type {
    match ty {
        ast::Type::I32 => types::I32,
        ast::Type::I64 => types::I64,
        ast::Type::F32 => types::F32,
        ast::Type::F64 => types::F64,
        ast::Type::Bool => types::I8,
        ast::Type::Option(_) => types::I64,
        _ => types::I64, // Pointers, refs, arrays, structs all use I64 (pointer)
    }
}

// Get the size of a type in bytes
fn type_size(ty: &ast::Type, structs: &HashMap<String, StructLayout>) -> u32 {
    match ty {
        ast::Type::I32 => 4,
        ast::Type::I64 => 8,
        ast::Type::F32 => 4,
        ast::Type::F64 => 8,
        ast::Type::Bool => 1,
        ast::Type::Option(_) => 8,
        // For now, arrays are represented as pointers.
        ast::Type::Array(_, _) => 8,
        ast::Type::Named(name) => structs.get(name).map(|s| s.size).unwrap_or(8),
        _ => 8, // Default pointer size
    }
}

#[derive(Clone, Debug)]
struct StructLayout {
    size: u32,
    fields: Vec<(String, u32, ast::Type)>, // (name, offset, type)
}

fn compute_struct_layout(
    def: &ast::StructDef,
    structs: &HashMap<String, StructLayout>,
) -> StructLayout {
    let mut offset = 0u32;
    let mut fields = Vec::new();

    for field in &def.fields {
        let size = type_size(&field.ty, structs);
        // Simple alignment: align to type size (max 8)
        let align = size.min(8);
        offset = (offset + align - 1) & !(align - 1);

        fields.push((field.name.clone(), offset, field.ty.clone()));
        offset += size;
    }

    // Align total size to 8 bytes
    let size = (offset + 7) & !7;

    StructLayout { size, fields }
}

/// Result of running Kernel main().
#[derive(Debug)]
pub enum MainResult {
    I32(i32),
    I64(i64),
    F64(f64),
    Bool(bool),
}

impl std::fmt::Display for MainResult {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            MainResult::I32(n) => write!(f, "{}", n),
            MainResult::I64(n) => write!(f, "{}", n),
            MainResult::F64(n) => write!(f, "{}", n),
            MainResult::Bool(b) => write!(f, "{}", b),
        }
    }
}

/// Find the return type of the Kernel main() function.
fn find_main_return_type(file: &ast::File) -> Option<ast::Type> {
    let mut aliases = HashMap::new();
    for kernel in &file.kernels {
        for item in &kernel.items {
            if let ast::KernelItem::TypeAlias(a) = item {
                aliases.insert(a.name.clone(), a.target.clone());
            }
        }
    }
    for kernel in &file.kernels {
        for item in &kernel.items {
            match item {
                ast::KernelItem::Function(f) | ast::KernelItem::ComptimeFn(f)
                    if f.name == "main" && f.params.is_empty() =>
                {
                    if let Some(mut ret_ty) = f.return_type.clone() {
                        while let ast::Type::Named(ref name) = ret_ty {
                            if let Some(target) = aliases.get(name) {
                                ret_ty = target.clone();
                            } else {
                                break;
                            }
                        }
                        return Some(ret_ty);
                    }
                    return None;
                }
                _ => {}
            }
        }
    }
    None
}

/// Run the Kernel main() function with support for multiple return types.
pub fn run_kernel_main_flex(file: &ast::File) -> Result<MainResult> {
    let return_type = find_main_return_type(file).ok_or_else(|| {
        anyhow!("No runnable Kernel entry point found (expected `fn main() -> <type>`)")
    })?;

    let mut jit = KernelJit::from_file(file)?;

    match return_type {
        ast::Type::I32 => Ok(MainResult::I32(jit.run_main_i32()?)),
        ast::Type::I64 => Ok(MainResult::I64(jit.run_main_i64()?)),
        ast::Type::F64 => Ok(MainResult::F64(jit.run_main_f64()?)),
        ast::Type::Bool => {
            let result = jit.run_main_bool()?;
            Ok(MainResult::Bool(result))
        }
        other => Err(anyhow!(
            "Unsupported main() return type: {:?}. Expected i32, i64, f64, or bool",
            other
        )),
    }
}

#[allow(dead_code)]
pub fn run_kernel_main(file: &ast::File) -> Result<i32> {
    // Legacy function for backwards compatibility
    let main_ok = file.kernels.iter().any(|k| {
        k.items.iter().any(|item| match item {
            ast::KernelItem::Function(f) | ast::KernelItem::ComptimeFn(f) => {
                f.name == "main"
                    && f.params.is_empty()
                    && matches!(f.return_type, Some(ast::Type::I32))
            }
            _ => false,
        })
    });
    if !main_ok {
        return Err(anyhow!(
            "No runnable Kernel entry point found (expected `fn main() -> i32`)"
        ));
    }

    let mut jit = KernelJit::from_file(file)?;
    jit.run_main_i32()
}

// Runtime allocation function for heap values that can outlive block scopes.
extern "C" fn bunker_alloc(size: i64, align: i64) -> i64 {
    let Ok(size) = usize::try_from(size) else {
        std::process::abort();
    };
    let Ok(align) = usize::try_from(align) else {
        std::process::abort();
    };

    if size == 0 {
        return 0;
    }

    let layout = match std::alloc::Layout::from_size_align(size, align) {
        Ok(layout) => layout,
        Err(_) => std::process::abort(),
    };
    let ptr = unsafe { std::alloc::alloc_zeroed(layout) };
    if ptr.is_null() {
        std::process::abort();
    }
    ptr as i64
}

pub struct KernelJit {
    module: JITModule,
    ctx: codegen::Context,
    functions: HashMap<String, FuncId>,
    structs: HashMap<String, StructLayout>,
    fn_sigs: HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
    alloc_func: FuncId,
    arena_push_func: FuncId,
    arena_pop_func: FuncId,
    _read_file_func: FuncId,
    _write_file_func: FuncId,
    _file_exists_func: FuncId,
    _str_eq_func: FuncId,
    constants: HashMap<String, (ast::Type, ast::Expr)>,
}

fn register_runtime_builtin(
    functions: &mut HashMap<String, FuncId>,
    fn_sigs: &mut HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
    name: &str,
    func_id: FuncId,
) -> Result<()> {
    let Some(signature) = builtins::runtime_signature(name) else {
        return Err(anyhow!("Missing runtime builtin signature for {}", name));
    };

    functions.insert(name.to_string(), func_id);
    fn_sigs.insert(name.to_string(), signature);
    Ok(())
}

#[derive(Debug, Clone, PartialEq)]
enum ConstVal {
    Int(i64),
    Float(f64),
    Bool(bool),
    Str(String),
}

fn eval_const_expr(expr: &ast::Expr, evaluated: &HashMap<String, ConstVal>) -> Option<ConstVal> {
    match expr {
        ast::Expr::Literal(lit) => match lit {
            ast::Literal::Int(n) => Some(ConstVal::Int(*n)),
            ast::Literal::Float(f) => Some(ConstVal::Float(*f)),
            ast::Literal::Bool(b) => Some(ConstVal::Bool(*b)),
            ast::Literal::String(s) => Some(ConstVal::Str(s.clone())),
            _ => None,
        },
        ast::Expr::Ident(name) => evaluated.get(name).cloned(),
        ast::Expr::Unary { op, expr } => {
            let inner = eval_const_expr(expr, evaluated)?;
            match (op, inner) {
                (ast::UnaryOp::Neg, ConstVal::Int(n)) => Some(ConstVal::Int(-n)),
                (ast::UnaryOp::Neg, ConstVal::Float(f)) => Some(ConstVal::Float(-f)),
                (ast::UnaryOp::Not, ConstVal::Bool(b)) => Some(ConstVal::Bool(!b)),
                _ => None,
            }
        }
        ast::Expr::Binary { op, left, right } => {
            let l = eval_const_expr(left, evaluated)?;
            let r = eval_const_expr(right, evaluated)?;
            match (op, l, r) {
                (ast::BinaryOp::Add, ConstVal::Int(a), ConstVal::Int(b)) => Some(ConstVal::Int(a + b)),
                (ast::BinaryOp::Sub, ConstVal::Int(a), ConstVal::Int(b)) => Some(ConstVal::Int(a - b)),
                (ast::BinaryOp::Mul, ConstVal::Int(a), ConstVal::Int(b)) => Some(ConstVal::Int(a * b)),
                (ast::BinaryOp::Div, ConstVal::Int(a), ConstVal::Int(b)) if b != 0 => Some(ConstVal::Int(a / b)),
                (ast::BinaryOp::Mod, ConstVal::Int(a), ConstVal::Int(b)) if b != 0 => Some(ConstVal::Int(a % b)),
                (ast::BinaryOp::Shl, ConstVal::Int(a), ConstVal::Int(b)) => Some(ConstVal::Int(a << (b as u32))),
                (ast::BinaryOp::Shr, ConstVal::Int(a), ConstVal::Int(b)) => Some(ConstVal::Int(a >> (b as u32))),
                (ast::BinaryOp::BitAnd, ConstVal::Int(a), ConstVal::Int(b)) => Some(ConstVal::Int(a & b)),
                (ast::BinaryOp::BitOr, ConstVal::Int(a), ConstVal::Int(b)) => Some(ConstVal::Int(a | b)),
                (ast::BinaryOp::BitXor, ConstVal::Int(a), ConstVal::Int(b)) => Some(ConstVal::Int(a ^ b)),
                (ast::BinaryOp::Add, ConstVal::Float(a), ConstVal::Float(b)) => Some(ConstVal::Float(a + b)),
                (ast::BinaryOp::Sub, ConstVal::Float(a), ConstVal::Float(b)) => Some(ConstVal::Float(a - b)),
                (ast::BinaryOp::Mul, ConstVal::Float(a), ConstVal::Float(b)) => Some(ConstVal::Float(a * b)),
                (ast::BinaryOp::Div, ConstVal::Float(a), ConstVal::Float(b)) => Some(ConstVal::Float(a / b)),
                (ast::BinaryOp::Add, ConstVal::Str(a), ConstVal::Str(b)) => Some(ConstVal::Str(format!("{}{}", a, b))),
                (ast::BinaryOp::Eq, ConstVal::Int(a), ConstVal::Int(b)) => Some(ConstVal::Bool(a == b)),
                (ast::BinaryOp::Ne, ConstVal::Int(a), ConstVal::Int(b)) => Some(ConstVal::Bool(a != b)),
                (ast::BinaryOp::Lt, ConstVal::Int(a), ConstVal::Int(b)) => Some(ConstVal::Bool(a < b)),
                (ast::BinaryOp::Le, ConstVal::Int(a), ConstVal::Int(b)) => Some(ConstVal::Bool(a <= b)),
                (ast::BinaryOp::Gt, ConstVal::Int(a), ConstVal::Int(b)) => Some(ConstVal::Bool(a > b)),
                (ast::BinaryOp::Ge, ConstVal::Int(a), ConstVal::Int(b)) => Some(ConstVal::Bool(a >= b)),
                (ast::BinaryOp::And, ConstVal::Bool(a), ConstVal::Bool(b)) => Some(ConstVal::Bool(a && b)),
                (ast::BinaryOp::Or, ConstVal::Bool(a), ConstVal::Bool(b)) => Some(ConstVal::Bool(a || b)),
                _ => None,
            }
        }
        _ => None,
    }
}


impl KernelJit {
    pub fn from_file(file: &ast::File) -> Result<Self> {
        let mut jit = Self::new()?;
        for kernel in &file.kernels {
            jit.collect_kernel_declarations(kernel)?;
        }
        for kernel in &file.kernels {
            jit.declare_kernel_functions(kernel)?;
        }
        for kernel in &file.kernels {
            jit.define_kernel_functions(kernel)?;
        }
        jit.finalize_definitions()?;
        Ok(jit)
    }

    fn new() -> Result<Self> {
        let mut flag_builder = settings::builder();
        flag_builder.set("opt_level", "speed").unwrap();

        let isa_builder = cranelift_native::builder()
            .map_err(|e| anyhow!("Failed to create ISA builder: {}", e))?;

        let isa = isa_builder
            .finish(settings::Flags::new(flag_builder))
            .map_err(|e| anyhow!("Failed to create ISA: {}", e))?;

        let mut builder = JITBuilder::with_isa(isa, cranelift_module::default_libcall_names());
        builder.symbol("bunker_alloc", bunker_alloc as *const u8);
        builder.symbol("bunker_arena_push", bunker_arena_push as *const u8);
        builder.symbol("bunker_arena_pop", bunker_arena_pop as *const u8);
        builder.symbol("bunker_panic", bunker_panic as *const u8);
        builder.symbol("bunker_assert", bunker_assert as *const u8);
        builder.symbol("bunker_read_file", bunker_read_file as *const u8);
        builder.symbol("bunker_write_file", bunker_write_file as *const u8);
        builder.symbol("bunker_file_exists", bunker_file_exists as *const u8);
        builder.symbol("bunker_args_count", bunker_args_count as *const u8);
        builder.symbol("bunker_arg_at", bunker_arg_at as *const u8);
        builder.symbol("bunker_char_at", bunker_char_at as *const u8);
        builder.symbol("bunker_substring", bunker_substring as *const u8);
        builder.symbol("bunker_contains", bunker_contains as *const u8);
        builder.symbol("bunker_starts_with", bunker_starts_with as *const u8);
        builder.symbol("bunker_ends_with", bunker_ends_with as *const u8);
        builder.symbol("bunker_trim", bunker_trim as *const u8);
        builder.symbol("bunker_parse_int", bunker_parse_int as *const u8);
        builder.symbol("bunker_int_to_string", bunker_int_to_string as *const u8);
        builder.symbol("bunker_char_code", bunker_char_code as *const u8);
        builder.symbol("bunker_char_code_at", bunker_char_code_at as *const u8);
        builder.symbol("bunker_from_char_code", bunker_from_char_code as *const u8);
        builder.symbol("bunker_str_eq", bunker_str_eq as *const u8);
        builder.symbol("bunker_join_lines", bunker_join_lines as *const u8);
        // Vec operations
        builder.symbol("bunker_vec_new", bunker_vec_new as *const u8);
        builder.symbol("bunker_vec_push", bunker_vec_push as *const u8);
        builder.symbol("bunker_vec_pop", bunker_vec_pop as *const u8);
        builder.symbol("bunker_vec_len", bunker_vec_len as *const u8);
        builder.symbol("bunker_vec_capacity", bunker_vec_capacity as *const u8);
        builder.symbol("bunker_vec_get", bunker_vec_get as *const u8);
        builder.symbol("bunker_vec_set", bunker_vec_set as *const u8);
        builder.symbol("bunker_vec_clear", bunker_vec_clear as *const u8);
        builder.symbol("bunker_vec_contains", bunker_vec_contains as *const u8);
        builder.symbol("bunker_vec_contains_str", bunker_vec_contains_str as *const u8);
        builder.symbol("bunker_vec_is_empty", bunker_vec_is_empty as *const u8);
        builder.symbol("bunker_vec_clone", bunker_vec_clone as *const u8);
        builder.symbol("bunker_vec_reverse", bunker_vec_reverse as *const u8);
        builder.symbol("bunker_vec_map", bunker_vec_map as *const u8);
        builder.symbol("bunker_vec_filter", bunker_vec_filter as *const u8);
        builder.symbol("bunker_vec_fold", bunker_vec_fold as *const u8);
        builder.symbol("bunker_vec_find", bunker_vec_find as *const u8);
        builder.symbol("bunker_hashmap_is_empty", bunker_hashmap_is_empty as *const u8);
        builder.symbol("bunker_hashmap_values", bunker_hashmap_values as *const u8);
        // Result operations
        builder.symbol("bunker_result_ok", bunker_result_ok as *const u8);
        builder.symbol("bunker_result_err", bunker_result_err as *const u8);
        builder.symbol("bunker_result_is_ok", bunker_result_is_ok as *const u8);
        builder.symbol("bunker_result_is_err", bunker_result_is_err as *const u8);
        builder.symbol("bunker_result_unwrap", bunker_result_unwrap as *const u8);
        builder.symbol(
            "bunker_result_unwrap_err",
            bunker_result_unwrap_err as *const u8,
        );
        builder.symbol("bunker_result_tag", bunker_result_tag as *const u8);
        builder.symbol("bunker_result_value", bunker_result_value as *const u8);
        // HashMap operations
        builder.symbol("bunker_hashmap_new", bunker_hashmap_new as *const u8);
        builder.symbol("bunker_hashmap_insert", bunker_hashmap_insert as *const u8);
        builder.symbol("bunker_hashmap_get", bunker_hashmap_get as *const u8);
        builder.symbol(
            "bunker_hashmap_contains",
            bunker_hashmap_contains as *const u8,
        );
        builder.symbol("bunker_hashmap_remove", bunker_hashmap_remove as *const u8);
        builder.symbol("bunker_hashmap_len", bunker_hashmap_len as *const u8);
        builder.symbol("bunker_hashmap_clear", bunker_hashmap_clear as *const u8);
        builder.symbol("bunker_hashmap_keys", bunker_hashmap_keys as *const u8);
        builder.symbol("bunker_hashmap_get_opt", bunker_hashmap_get_opt as *const u8);
        builder.symbol("bunker_hashmap_new_str", bunker_hashmap_new_str as *const u8);
        builder.symbol("bunker_hashmap_insert_str", bunker_hashmap_insert_str as *const u8);
        builder.symbol("bunker_vec_get_opt", bunker_vec_get_opt as *const u8);
        builder.symbol("bunker_vec_pop_opt", bunker_vec_pop_opt as *const u8);
        builder.symbol("bunker_read_file_result", bunker_read_file_result as *const u8);
        builder.symbol("bunker_write_file_result", bunker_write_file_result as *const u8);
        builder.symbol("bunker_parse_int_result", bunker_parse_int_result as *const u8);
        builder.symbol("bunker_str_index_of", bunker_str_index_of as *const u8);
        builder.symbol("bunker_str_replace", bunker_str_replace as *const u8);
        builder.symbol("bunker_str_split", bunker_str_split as *const u8);
        builder.symbol("bunker_str_to_upper", bunker_str_to_upper as *const u8);
        builder.symbol("bunker_str_to_lower", bunker_str_to_lower as *const u8);
        builder.symbol("bunker_str_repeat", bunker_str_repeat as *const u8);
        builder.symbol("bunker_path_join", bunker_path_join as *const u8);
        builder.symbol("bunker_path_dir", bunker_path_dir as *const u8);
        builder.symbol("bunker_path_base", bunker_path_base as *const u8);
        builder.symbol("bunker_path_ext", bunker_path_ext as *const u8);
        builder.symbol("bunker_path_is_abs", bunker_path_is_abs as *const u8);
        builder.symbol("bunker_env_var", bunker_env_var as *const u8);
        builder.symbol("bunker_env_get", bunker_env_get as *const u8);
        builder.symbol("bunker_env_set", bunker_env_set as *const u8);
        builder.symbol("bunker_env_has", bunker_env_has as *const u8);
        builder.symbol("bunker_time_now_ms", bunker_time_now_ms as *const u8);
        builder.symbol("bunker_time_now_unix", bunker_time_now_unix as *const u8);
        builder.symbol("bunker_bytes_new", bunker_bytes_new as *const u8);
        builder.symbol("bunker_bytes_len", bunker_bytes_len as *const u8);
        builder.symbol("bunker_bytes_capacity", bunker_bytes_capacity as *const u8);
        builder.symbol("bunker_bytes_get", bunker_bytes_get as *const u8);
        builder.symbol("bunker_bytes_set", bunker_bytes_set as *const u8);
        builder.symbol("bunker_bytes_push", bunker_bytes_push as *const u8);
        builder.symbol("bunker_bytes_from_str", bunker_bytes_from_str as *const u8);
        builder.symbol("bunker_bytes_to_str", bunker_bytes_to_str as *const u8);
        builder.symbol("bunker_slice_new", bunker_slice_new as *const u8);
        builder.symbol("bunker_slice_len", bunker_slice_len as *const u8);
        builder.symbol("bunker_slice_get", bunker_slice_get as *const u8);
        builder.symbol("bunker_slice_sub", bunker_slice_sub as *const u8);
        builder.symbol("bunker_slice_contains", bunker_slice_contains as *const u8);
        builder.symbol("bunker_slice_to_vec", bunker_slice_to_vec as *const u8);
        builder.symbol("bunker_vec_as_slice", bunker_vec_as_slice as *const u8);
        builder.symbol("bunker_vec_slice", bunker_vec_slice as *const u8);
        builder.symbol("bunker_bytes_as_slice", bunker_bytes_as_slice as *const u8);
        builder.symbol("bunker_bytes_slice", bunker_bytes_slice as *const u8);
        builder.symbol("bunker_path_exists", bunker_path_exists as *const u8);
        builder.symbol("bunker_path_is_file", bunker_path_is_file as *const u8);
        builder.symbol("bunker_path_is_dir", bunker_path_is_dir as *const u8);
        builder.symbol("bunker_file_read", bunker_file_read as *const u8);
        builder.symbol("bunker_file_write", bunker_file_write as *const u8);
        builder.symbol("bunker_file_size", bunker_file_size as *const u8);
        builder.symbol("bunker_file_remove", bunker_file_remove as *const u8);
        builder.symbol("bunker_file_read_bytes", bunker_file_read_bytes as *const u8);
        builder.symbol("bunker_file_write_bytes", bunker_file_write_bytes as *const u8);
        builder.symbol("bunker_dir_create", bunker_dir_create as *const u8);
        builder.symbol("bunker_dir_remove", bunker_dir_remove as *const u8);
        builder.symbol("bunker_process_run", bunker_process_run as *const u8);
        builder.symbol("bunker_process_run_status", bunker_process_run_status as *const u8);
        builder.symbol("bunker_process_exit", bunker_process_exit as *const u8);
        builder.symbol("bunker_process_pid", bunker_process_pid as *const u8);
        builder.symbol("bunker_process_is_sandboxed", bunker_process_is_sandboxed as *const u8);

        let mut module = JITModule::new(builder);
        let alloc_func = declare_alloc_func(&mut module)?;
        let arena_push_func = declare_arena_push_func(&mut module)?;
        let arena_pop_func = declare_arena_pop_func(&mut module)?;
        let panic_func = declare_panic_func(&mut module)?;
        let assert_func = declare_assert_func(&mut module)?;
        let read_file_func = declare_read_file_func(&mut module)?;
        let write_file_func = declare_write_file_func(&mut module)?;
        let file_exists_func = declare_file_exists_func(&mut module)?;
        let args_count_func = declare_args_count_func(&mut module)?;
        let arg_at_func = declare_arg_at_func(&mut module)?;
        let char_at_func = declare_char_at_func(&mut module)?;
        let substring_func = declare_substring_func(&mut module)?;
        let contains_func = declare_contains_func(&mut module)?;
        let starts_with_func = declare_starts_with_func(&mut module)?;
        let ends_with_func = declare_ends_with_func(&mut module)?;
        let trim_func = declare_trim_func(&mut module)?;
        let parse_int_func = declare_parse_int_func(&mut module)?;
        let int_to_string_func = declare_int_to_string_func(&mut module)?;
        let char_code_func = declare_char_code_func(&mut module)?;
        let char_code_at_func = declare_char_code_at_func(&mut module)?;
        let from_char_code_func = declare_from_char_code_func(&mut module)?;
        let str_eq_func = declare_str_eq_func(&mut module)?;
        let join_lines_func = declare_join_lines_func(&mut module)?;
        // Vec operations
        let vec_new_func = declare_vec_new_func(&mut module)?;
        let vec_push_func = declare_vec_push_func(&mut module)?;
        let vec_pop_func = declare_vec_pop_func(&mut module)?;
        let vec_len_func = declare_vec_len_func(&mut module)?;
        let vec_capacity_func = declare_vec_capacity_func(&mut module)?;
        let vec_get_func = declare_vec_get_func(&mut module)?;
        let vec_set_func = declare_vec_set_func(&mut module)?;
        let vec_clear_func = declare_vec_clear_func(&mut module)?;
        let vec_contains_func = declare_vec_contains_func(&mut module)?;
        let vec_contains_str_func = declare_vec_contains_str_func(&mut module)?;
        let vec_is_empty_func = declare_vec_is_empty_func(&mut module)?;
        let vec_clone_func = declare_vec_clone_func(&mut module)?;
        let vec_reverse_func = declare_vec_reverse_func(&mut module)?;
        let vec_map_func = declare_vec_map_func(&mut module)?;
        let vec_filter_func = declare_vec_filter_func(&mut module)?;
        let vec_fold_func = declare_vec_fold_func(&mut module)?;
        let vec_find_func = declare_vec_find_func(&mut module)?;
        let hashmap_is_empty_func = declare_hashmap_is_empty_func(&mut module)?;
        let hashmap_values_func = declare_hashmap_values_func(&mut module)?;
        // Result operations
        let result_ok_func = declare_result_ok_func(&mut module)?;
        let result_err_func = declare_result_err_func(&mut module)?;
        let result_is_ok_func = declare_result_is_ok_func(&mut module)?;
        let result_is_err_func = declare_result_is_err_func(&mut module)?;
        let result_unwrap_func = declare_result_unwrap_func(&mut module)?;
        let result_unwrap_err_func = declare_result_unwrap_err_func(&mut module)?;
        let result_tag_func = declare_result_tag_func(&mut module)?;
        let result_value_func = declare_result_value_func(&mut module)?;
        // HashMap operations
        let hashmap_new_func = declare_hashmap_new_func(&mut module)?;
        let hashmap_insert_func = declare_hashmap_insert_func(&mut module)?;
        let hashmap_get_func = declare_hashmap_get_func(&mut module)?;
        let hashmap_contains_func = declare_hashmap_contains_func(&mut module)?;
        let hashmap_remove_func = declare_hashmap_remove_func(&mut module)?;
        let hashmap_len_func = declare_hashmap_len_func(&mut module)?;
        let hashmap_clear_func = declare_hashmap_clear_func(&mut module)?;
        let hashmap_keys_func = declare_hashmap_keys_func(&mut module)?;
        let hashmap_get_opt_func = declare_hashmap_get_opt_func(&mut module)?;
        let hashmap_new_str_func = declare_hashmap_new_str_func(&mut module)?;
        let hashmap_insert_str_func = declare_hashmap_insert_str_func(&mut module)?;
        let vec_get_opt_func = declare_vec_get_opt_func(&mut module)?;
        let vec_pop_opt_func = declare_vec_pop_opt_func(&mut module)?;
        let read_file_result_func = declare_read_file_result_func(&mut module)?;
        let write_file_result_func = declare_write_file_result_func(&mut module)?;
        let parse_int_result_func = declare_parse_int_result_func(&mut module)?;
        let str_index_of_func = declare_str_index_of_func(&mut module)?;
        let str_replace_func = declare_str_replace_func(&mut module)?;
        let str_split_func = declare_str_split_func(&mut module)?;
        let str_to_upper_func = declare_str_to_upper_func(&mut module)?;
        let str_to_lower_func = declare_str_to_lower_func(&mut module)?;
        let str_repeat_func = declare_str_repeat_func(&mut module)?;
        let path_join_func = declare_path_join_func(&mut module)?;
        let path_dir_func = declare_path_dir_func(&mut module)?;
        let path_base_func = declare_path_base_func(&mut module)?;
        let path_ext_func = declare_path_ext_func(&mut module)?;
        let path_is_abs_func = declare_path_is_abs_func(&mut module)?;
        let env_var_func = declare_env_var_func(&mut module)?;
        let env_get_func = declare_env_get_func(&mut module)?;
        let env_set_func = declare_env_set_func(&mut module)?;
        let env_has_func = declare_env_has_func(&mut module)?;
        let time_now_ms_func = declare_time_now_ms_func(&mut module)?;
        let time_now_unix_func = declare_time_now_unix_func(&mut module)?;
        let bytes_new_func = declare_bytes_new_func(&mut module)?;
        let bytes_len_func = declare_bytes_len_func(&mut module)?;
        let bytes_capacity_func = declare_bytes_capacity_func(&mut module)?;
        let bytes_get_func = declare_bytes_get_func(&mut module)?;
        let bytes_set_func = declare_bytes_set_func(&mut module)?;
        let bytes_push_func = declare_bytes_push_func(&mut module)?;
        let bytes_from_str_func = declare_bytes_from_str_func(&mut module)?;
        let bytes_to_str_func = declare_bytes_to_str_func(&mut module)?;
        let slice_new_func = declare_slice_new_func(&mut module)?;
        let slice_len_func = declare_slice_len_func(&mut module)?;
        let slice_get_func = declare_slice_get_func(&mut module)?;
        let slice_sub_func = declare_slice_sub_func(&mut module)?;
        let slice_contains_func = declare_slice_contains_func(&mut module)?;
        let slice_to_vec_func = declare_slice_to_vec_func(&mut module)?;
        let vec_as_slice_func = declare_vec_as_slice_func(&mut module)?;
        let vec_slice_func = declare_vec_slice_func(&mut module)?;
        let bytes_as_slice_func = declare_bytes_as_slice_func(&mut module)?;
        let bytes_slice_func = declare_bytes_slice_func(&mut module)?;
        let path_exists_func = declare_path_exists_func(&mut module)?;
        let path_is_file_func = declare_path_is_file_func(&mut module)?;
        let path_is_dir_func = declare_path_is_dir_func(&mut module)?;
        let file_read_func = declare_file_read_func(&mut module)?;
        let file_write_func = declare_file_write_func(&mut module)?;
        let file_size_func = declare_file_size_func(&mut module)?;
        let file_remove_func = declare_file_remove_func(&mut module)?;
        let file_read_bytes_func = declare_file_read_bytes_func(&mut module)?;
        let file_write_bytes_func = declare_file_write_bytes_func(&mut module)?;
        let dir_create_func = declare_dir_create_func(&mut module)?;
        let dir_remove_func = declare_dir_remove_func(&mut module)?;
        let process_run_func = declare_process_run_func(&mut module)?;
        let process_run_status_func = declare_process_run_status_func(&mut module)?;
        let process_exit_func = declare_process_exit_func(&mut module)?;
        let process_pid_func = declare_process_pid_func(&mut module)?;
        let process_is_sandboxed_func = declare_process_is_sandboxed_func(&mut module)?;
        let ctx = module.make_context();

        // Initialize with builtin functions
        let mut functions = HashMap::new();
        let mut fn_sigs = HashMap::new();
        for (name, func_id) in [
            ("read_file", read_file_func),
            ("write_file", write_file_func),
            ("file_exists", file_exists_func),
            ("args_count", args_count_func),
            ("arg_at", arg_at_func),
            ("char_at", char_at_func),
            ("substring", substring_func),
            ("contains", contains_func),
            ("starts_with", starts_with_func),
            ("ends_with", ends_with_func),
            ("trim", trim_func),
            ("parse_int", parse_int_func),
            ("int_to_string", int_to_string_func),
            ("char_code", char_code_func),
            ("char_code_at", char_code_at_func),
            ("from_char_code", from_char_code_func),
            ("str_eq", str_eq_func),
            ("join_lines", join_lines_func),
            ("vec_new", vec_new_func),
            ("vec_push", vec_push_func),
            ("vec_pop", vec_pop_func),
            ("vec_len", vec_len_func),
            ("vec_capacity", vec_capacity_func),
            ("vec_get", vec_get_func),
            ("vec_set", vec_set_func),
            ("vec_clear", vec_clear_func),
            ("vec_contains", vec_contains_func),
            ("vec_contains_str", vec_contains_str_func),
            ("vec_is_empty", vec_is_empty_func),
            ("vec_clone", vec_clone_func),
            ("vec_reverse", vec_reverse_func),
            ("vec_map", vec_map_func),
            ("vec_filter", vec_filter_func),
            ("vec_fold", vec_fold_func),
            ("vec_find", vec_find_func),
            ("hashmap_is_empty", hashmap_is_empty_func),
            ("hashmap_values", hashmap_values_func),
            ("result_ok", result_ok_func),
            ("result_err", result_err_func),
            ("Ok", result_ok_func),
            ("Err", result_err_func),
            ("result_is_ok", result_is_ok_func),
            ("result_is_err", result_is_err_func),
            ("result_unwrap", result_unwrap_func),
            ("result_unwrap_err", result_unwrap_err_func),
            ("result_tag", result_tag_func),
            ("result_value", result_value_func),
            ("hashmap_new", hashmap_new_func),
            ("hashmap_insert", hashmap_insert_func),
            ("hashmap_get", hashmap_get_func),
            ("hashmap_contains", hashmap_contains_func),
            ("hashmap_remove", hashmap_remove_func),
            ("hashmap_len", hashmap_len_func),
            ("hashmap_clear", hashmap_clear_func),
            ("hashmap_keys", hashmap_keys_func),
            ("hashmap_get_opt", hashmap_get_opt_func),
            ("hashmap_new_str", hashmap_new_str_func),
            ("hashmap_insert_str", hashmap_insert_str_func),
            ("vec_get_opt", vec_get_opt_func),
            ("vec_pop_opt", vec_pop_opt_func),
            ("read_file_result", read_file_result_func),
            ("write_file_result", write_file_result_func),
            ("parse_int_result", parse_int_result_func),
            ("str_index_of", str_index_of_func),
            ("str_replace", str_replace_func),
            ("str_split", str_split_func),
            ("str_to_upper", str_to_upper_func),
            ("str_to_lower", str_to_lower_func),
            ("str_repeat", str_repeat_func),
            ("path_join", path_join_func),
            ("path_dir", path_dir_func),
            ("path_base", path_base_func),
            ("path_ext", path_ext_func),
            ("path_is_abs", path_is_abs_func),
            ("env_var", env_var_func),
            ("env_get", env_get_func),
            ("env_set", env_set_func),
            ("env_has", env_has_func),
            ("time_now_ms", time_now_ms_func),
            ("time_now_unix", time_now_unix_func),
            ("bytes_new", bytes_new_func),
            ("bytes_len", bytes_len_func),
            ("bytes_capacity", bytes_capacity_func),
            ("bytes_get", bytes_get_func),
            ("bytes_set", bytes_set_func),
            ("bytes_push", bytes_push_func),
            ("bytes_from_str", bytes_from_str_func),
            ("bytes_to_str", bytes_to_str_func),
            ("slice_new", slice_new_func),
            ("slice_len", slice_len_func),
            ("slice_get", slice_get_func),
            ("slice_sub", slice_sub_func),
            ("slice_contains", slice_contains_func),
            ("slice_to_vec", slice_to_vec_func),
            ("vec_as_slice", vec_as_slice_func),
            ("vec_slice", vec_slice_func),
            ("bytes_as_slice", bytes_as_slice_func),
            ("bytes_slice", bytes_slice_func),
            ("path_exists", path_exists_func),
            ("path_is_file", path_is_file_func),
            ("path_is_dir", path_is_dir_func),
            ("file_read", file_read_func),
            ("file_write", file_write_func),
            ("file_size", file_size_func),
            ("file_remove", file_remove_func),
            ("file_read_bytes", file_read_bytes_func),
            ("file_write_bytes", file_write_bytes_func),
            ("dir_create", dir_create_func),
            ("dir_remove", dir_remove_func),
            ("process_run", process_run_func),
            ("process_run_status", process_run_status_func),
            ("process_exit", process_exit_func),
            ("process_pid", process_pid_func),
            ("process_is_sandboxed", process_is_sandboxed_func),
        ] {
            register_runtime_builtin(&mut functions, &mut fn_sigs, name, func_id)?;
        }
        functions.insert("bunker_panic".to_string(), panic_func);
        functions.insert("bunker_assert".to_string(), assert_func);
        Ok(Self {
            module,
            ctx,
            functions,
            structs: HashMap::new(),
            fn_sigs,
            alloc_func,
            arena_push_func,
            arena_pop_func,
            _read_file_func: read_file_func,
            _write_file_func: write_file_func,
            _file_exists_func: file_exists_func,
            _str_eq_func: str_eq_func,
            constants: HashMap::new(),
        })
    }

        #[allow(dead_code)]
        #[allow(dead_code)]
    fn compile_kernel(&mut self, kernel: &ast::Kernel) -> Result<()> {
        self.collect_kernel_declarations(kernel)?;
        self.declare_kernel_functions(kernel)?;
        self.define_kernel_functions(kernel)?;
        Ok(())
    }

    fn collect_kernel_declarations(&mut self, kernel: &ast::Kernel) -> Result<()> {
        for item in &kernel.items {
            match item {
                ast::KernelItem::Struct(s) => {
                    let layout = compute_struct_layout(s, &self.structs);
                    self.structs.insert(s.name.clone(), layout.clone());
                    self.structs.insert(format!("{}::{}", kernel.name, s.name), layout);
                }
                ast::KernelItem::Const(c) => {
                    self.constants
                        .insert(c.name.clone(), (c.ty.clone(), c.value.clone()));
                    self.constants
                        .insert(format!("{}::{}", kernel.name, c.name), (c.ty.clone(), c.value.clone()));
                }
                _ => {}
            }
        }
        Ok(())
    }

    fn declare_kernel_functions(&mut self, kernel: &ast::Kernel) -> Result<()> {
        for item in &kernel.items {
            if let ast::KernelItem::Function(func) = item {
                let params: Vec<_> = func.params.iter().map(|p| p.ty.clone()).collect();
                self.fn_sigs
                    .insert(func.name.clone(), (params.clone(), func.return_type.clone()));
                self.fn_sigs
                    .insert(format!("{}::{}", kernel.name, func.name), (params, func.return_type.clone()));
                let func_id = self.declare_function(&kernel.name, func)?;
                self.functions
                    .insert(format!("{}::{}", kernel.name, func.name), func_id);
            }
        }
        Ok(())
    }

    fn define_kernel_functions(&mut self, kernel: &ast::Kernel) -> Result<()> {
        for item in &kernel.items {
            if let ast::KernelItem::Function(func) = item {
                self.compile_function(&kernel.name, func)?;
            }
        }
        Ok(())
    }

    fn declare_function(&mut self, kernel_name: &str, func: &ast::Function) -> Result<FuncId> {
        let mut sig = self.module.make_signature();

        for param in &func.params {
            sig.params.push(AbiParam::new(convert_ast_type(&param.ty)));
        }

        if let Some(ref ret_ty) = func.return_type {
            if *ret_ty != ast::Type::Unit && *ret_ty != ast::Type::Never {
                sig.returns.push(AbiParam::new(convert_ast_type(ret_ty)));
            }
        }

        let symbol_name = if func.name == "main" {
            "main".to_string()
        } else {
            format!("{}::{}", kernel_name, func.name)
        };

        let linkage = if func.name == "main" {
            Linkage::Export
        } else {
            Linkage::Local
        };

        let func_id = self
            .module
            .declare_function(&symbol_name, linkage, &sig)
            .map_err(|e| anyhow!("Failed to declare function {}: {}", symbol_name, e))?;

        self.functions.insert(format!("{}::{}", kernel_name, func.name), func_id);
        self.functions.insert(func.name.clone(), func_id);
        Ok(func_id)
    }

    fn compile_function(&mut self, kernel_name: &str, func: &ast::Function) -> Result<()> {
        let qualified_fn = format!("{}::{}", kernel_name, func.name);
        let func_id = *self
            .functions
            .get(&qualified_fn)
            .or_else(|| self.functions.get(&func.name))
            .ok_or_else(|| anyhow!("Function {} not declared", func.name))?;

        self.ctx.func.signature = self
            .module
            .declarations()
            .get_function_decl(func_id)
            .signature
            .clone();

        let param_types: Vec<_> = func
            .params
            .iter()
            .map(|p| convert_ast_type(&p.ty))
            .collect();

        let mut builder_ctx = FunctionBuilderContext::new();
        {
            let mut builder = FunctionBuilder::new(&mut self.ctx.func, &mut builder_ctx);

            let entry_block = builder.create_block();
            builder.append_block_params_for_function_params(entry_block);
            builder.switch_to_block(entry_block);

            let mut variables: HashMap<String, Variable> = HashMap::new();
            let mut var_index = 0u32;
            let mut var_types: HashMap<String, ast::Type> = HashMap::new();

            for (i, param) in func.params.iter().enumerate() {
                let var = Variable::new(var_index as usize);
                var_index += 1;
                builder.declare_var(var, param_types[i]);
                let val = builder.block_params(entry_block)[i];
                builder.def_var(var, val);
                variables.insert(param.name.clone(), var);
                var_types.insert(param.name.clone(), param.ty.clone());
            }

            // Scoped function map for body compilation: local unqualified calls within this kernel resolve locally
            let mut scoped_functions = self.functions.clone();
            let kernel_prefix = format!("{}::", kernel_name);
            for (fname, &fid) in &self.functions {
                if let Some(short_name) = fname.strip_prefix(&kernel_prefix) {
                    scoped_functions.insert(short_name.to_string(), fid);
                }
            }

            // Iteratively evaluate all constants
            let mut evaluated_constants: HashMap<String, ConstVal> = HashMap::new();
            let mut changed = true;
            while changed {
                changed = false;
                for (name, (_, expr)) in &self.constants {
                    if !evaluated_constants.contains_key(name) {
                        if let Some(val) = eval_const_expr(expr, &evaluated_constants) {
                            evaluated_constants.insert(name.clone(), val);
                            changed = true;
                        }
                    }
                }
            }

            // Initialize constants as variables
            for (name, (ty, _)) in &self.constants {
                if let Some(val) = evaluated_constants.get(name) {
                    let cr_type = convert_ast_type(ty);
                    let var = Variable::new(var_index as usize);
                    var_index += 1;
                    builder.declare_var(var, cr_type);

                    let cr_val = match val {
                        ConstVal::Int(n) => builder.ins().iconst(cr_type, *n),
                        ConstVal::Float(f) => {
                            if cr_type == types::F64 {
                                builder.ins().f64const(*f)
                            } else {
                                builder.ins().f32const(*f as f32)
                            }
                        }
                        ConstVal::Bool(b) => {
                            builder.ins().iconst(cr_type, if *b { 1 } else { 0 })
                        }
                        ConstVal::Str(s) => {
                            compile_string_literal(&mut builder, &mut self.module, self.alloc_func, s)?
                        }
                    };
                    builder.def_var(var, cr_val);
                    variables.insert(name.clone(), var);
                    var_types.insert(name.clone(), ty.clone());
                    if let Some(short_name) = name.strip_prefix(&kernel_prefix) {
                        variables.insert(short_name.to_string(), var);
                        var_types.insert(short_name.to_string(), ty.clone());
                    }
                }
            }

            let mut returned = false;
            let mut defer_stack: Vec<Vec<ast::Block>> = Vec::new();
            compile_block_inline_inner(
                &mut builder,
                &mut self.module,
                self.alloc_func,
                self.arena_push_func,
                self.arena_pop_func,
                &scoped_functions,
                &self.structs,
                &self.fn_sigs,
                &mut variables,
                &mut var_types,
                &mut var_index,
                &func.body,
                &mut returned,
                &mut defer_stack,
                &[], // loop_stack - not in a loop
                false,
            )?;

            if !returned {
                if builder.func.signature.returns.is_empty() {
                    builder.ins().return_(&[]);
                } else {
                    let ret_ty = builder.func.signature.returns[0].value_type;
                    let default_ret = zero_value(&mut builder, ret_ty);
                    builder.ins().return_(&[default_ret]);
                }
            }

            builder.seal_all_blocks();
            builder.finalize();
        }

        self.module
            .define_function(func_id, &mut self.ctx)
            .map_err(|e| anyhow!("Failed to define function {}: {:?}", func.name, e))?;

        self.module.clear_context(&mut self.ctx);
        Ok(())
    }

    fn finalize_definitions(&mut self) -> Result<()> {
        self.module
            .finalize_definitions()
            .map_err(|e| anyhow!("Failed to finalize JIT definitions: {}", e))
    }

    pub fn run_main_i32(&mut self) -> Result<i32> {
        self.call_i32("main", &[])
    }

    pub fn run_main_i64(&mut self) -> Result<i64> {
        self.call_i64("main", &[])
    }

    pub fn run_main_f64(&mut self) -> Result<f64> {
        self.call_f64("main", &[])
    }

    pub fn run_main_bool(&mut self) -> Result<bool> {
        self.call_bool("main", &[])
    }

    pub fn call_i32(&mut self, func_name: &str, args: &[i32]) -> Result<i32> {
        let func_id = *self
            .functions
            .get(func_name)
            .ok_or_else(|| anyhow!("Undefined Kernel function: {}", func_name))?;

        let code_ptr = self.module.get_finalized_function(func_id);
        unsafe {
            match args.len() {
                0 => {
                    let f = std::mem::transmute::<*const u8, extern "C" fn() -> i32>(code_ptr);
                    Ok(f())
                }
                1 => {
                    let f = std::mem::transmute::<*const u8, extern "C" fn(i32) -> i32>(code_ptr);
                    Ok(f(args[0]))
                }
                2 => {
                    let f =
                        std::mem::transmute::<*const u8, extern "C" fn(i32, i32) -> i32>(code_ptr);
                    Ok(f(args[0], args[1]))
                }
                3 => {
                    let f = std::mem::transmute::<*const u8, extern "C" fn(i32, i32, i32) -> i32>(
                        code_ptr,
                    );
                    Ok(f(args[0], args[1], args[2]))
                }
                4 => {
                    let f = std::mem::transmute::<
                        *const u8,
                        extern "C" fn(i32, i32, i32, i32) -> i32,
                    >(code_ptr);
                    Ok(f(args[0], args[1], args[2], args[3]))
                }
                _ => Err(anyhow!(
                    "Kernel call not supported for {} args (function {})",
                    args.len(),
                    func_name
                )),
            }
        }
    }

    pub fn call_i64(&mut self, func_name: &str, args: &[i64]) -> Result<i64> {
        let func_id = *self
            .functions
            .get(func_name)
            .ok_or_else(|| anyhow!("Undefined Kernel function: {}", func_name))?;

        let code_ptr = self.module.get_finalized_function(func_id);
        unsafe {
            match args.len() {
                0 => {
                    let f = std::mem::transmute::<*const u8, extern "C" fn() -> i64>(code_ptr);
                    Ok(f())
                }
                1 => {
                    let f = std::mem::transmute::<*const u8, extern "C" fn(i64) -> i64>(code_ptr);
                    Ok(f(args[0]))
                }
                2 => {
                    let f =
                        std::mem::transmute::<*const u8, extern "C" fn(i64, i64) -> i64>(code_ptr);
                    Ok(f(args[0], args[1]))
                }
                3 => {
                    let f = std::mem::transmute::<*const u8, extern "C" fn(i64, i64, i64) -> i64>(
                        code_ptr,
                    );
                    Ok(f(args[0], args[1], args[2]))
                }
                4 => {
                    let f = std::mem::transmute::<
                        *const u8,
                        extern "C" fn(i64, i64, i64, i64) -> i64,
                    >(code_ptr);
                    Ok(f(args[0], args[1], args[2], args[3]))
                }
                _ => Err(anyhow!(
                    "Kernel call not supported for {} args (function {})",
                    args.len(),
                    func_name
                )),
            }
        }
    }

    pub fn call_f64(&mut self, func_name: &str, args: &[f64]) -> Result<f64> {
        let func_id = *self
            .functions
            .get(func_name)
            .ok_or_else(|| anyhow!("Undefined Kernel function: {}", func_name))?;

        let code_ptr = self.module.get_finalized_function(func_id);
        unsafe {
            match args.len() {
                0 => {
                    let f = std::mem::transmute::<*const u8, extern "C" fn() -> f64>(code_ptr);
                    Ok(f())
                }
                1 => {
                    let f = std::mem::transmute::<*const u8, extern "C" fn(f64) -> f64>(code_ptr);
                    Ok(f(args[0]))
                }
                2 => {
                    let f =
                        std::mem::transmute::<*const u8, extern "C" fn(f64, f64) -> f64>(code_ptr);
                    Ok(f(args[0], args[1]))
                }
                3 => {
                    let f = std::mem::transmute::<*const u8, extern "C" fn(f64, f64, f64) -> f64>(
                        code_ptr,
                    );
                    Ok(f(args[0], args[1], args[2]))
                }
                4 => {
                    let f = std::mem::transmute::<
                        *const u8,
                        extern "C" fn(f64, f64, f64, f64) -> f64,
                    >(code_ptr);
                    Ok(f(args[0], args[1], args[2], args[3]))
                }
                _ => Err(anyhow!(
                    "Kernel call not supported for {} args (function {})",
                    args.len(),
                    func_name
                )),
            }
        }
    }

    pub fn call_bool(&mut self, func_name: &str, args: &[bool]) -> Result<bool> {
        let func_id = *self
            .functions
            .get(func_name)
            .ok_or_else(|| anyhow!("Undefined Kernel function: {}", func_name))?;

        let code_ptr = self.module.get_finalized_function(func_id);
        // Bool is returned as i8 (0 or 1) in Cranelift's calling convention
        unsafe {
            match args.len() {
                0 => {
                    let f = std::mem::transmute::<*const u8, extern "C" fn() -> i8>(code_ptr);
                    Ok(f() != 0)
                }
                1 => {
                    let f = std::mem::transmute::<*const u8, extern "C" fn(i8) -> i8>(code_ptr);
                    Ok(f(args[0] as i8) != 0)
                }
                2 => {
                    let f = std::mem::transmute::<*const u8, extern "C" fn(i8, i8) -> i8>(code_ptr);
                    Ok(f(args[0] as i8, args[1] as i8) != 0)
                }
                _ => Err(anyhow!(
                    "Kernel call not supported for {} bool args (function {})",
                    args.len(),
                    func_name
                )),
            }
        }
    }
}

#[allow(clippy::too_many_arguments)]
fn compile_block_inline(
    builder: &mut FunctionBuilder,
    module: &mut JITModule,
    alloc_func: FuncId,
    arena_push_func: FuncId,
    arena_pop_func: FuncId,
    functions: &HashMap<String, FuncId>,
    structs: &HashMap<String, StructLayout>,
    fn_sigs: &HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
    variables: &mut HashMap<String, Variable>,
    var_types: &mut HashMap<String, ast::Type>,
    var_index: &mut u32,
    block: &ast::Block,
    returned: &mut bool,
    defer_stack: &mut Vec<Vec<ast::Block>>,
    loop_stack: &[(Option<String>, Block, Block)],
) -> Result<()> {
    compile_block_inline_inner(
        builder,
        module,
        alloc_func,
        arena_push_func,
        arena_pop_func,
        functions,
        structs,
        fn_sigs,
        variables,
        var_types,
        var_index,
        block,
        returned,
        defer_stack,
        loop_stack,
        // Runtime allocations currently bypass JIT_ARENA, so emitted block
        // watermarks only add leak risk on early returns in self-host runs.
        false,
    )
}

#[allow(clippy::too_many_arguments)]
fn compile_block_inline_inner(
    builder: &mut FunctionBuilder,
    module: &mut JITModule,
    alloc_func: FuncId,
    arena_push_func: FuncId,
    arena_pop_func: FuncId,
    functions: &HashMap<String, FuncId>,
    structs: &HashMap<String, StructLayout>,
    fn_sigs: &HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
    variables: &mut HashMap<String, Variable>,
    var_types: &mut HashMap<String, ast::Type>,
    var_index: &mut u32,
    block: &ast::Block,
    returned: &mut bool,
    defer_stack: &mut Vec<Vec<ast::Block>>,
    loop_stack: &[(Option<String>, Block, Block)],
    track_arena_scope: bool,
) -> Result<()> {
    // Arena scope: save watermark at block entry
    if track_arena_scope {
        let push_ref = module.declare_func_in_func(arena_push_func, builder.func);
        builder.ins().call(push_ref, &[]);
    }

    defer_stack.push(Vec::new());
    for stmt in &block.statements {
        if *returned {
            break;
        }
        compile_stmt_inline(
            builder,
            module,
            alloc_func,
            arena_push_func,
            arena_pop_func,
            functions,
            structs,
            fn_sigs,
            variables,
            var_types,
            var_index,
            stmt,
            returned,
            defer_stack,
            loop_stack,
        )?;
    }
    if !*returned {
        // Execute defer blocks first (they may still need access to memory)
        if let Some(defers) = defer_stack.last() {
            emit_defer_blocks(
                builder,
                module,
                alloc_func,
                arena_push_func,
                arena_pop_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defers,
            )?;
        }
        // Arena scope: restore watermark after defers, before leaving block
        if track_arena_scope {
            let pop_ref = module.declare_func_in_func(arena_pop_func, builder.func);
            builder.ins().call(pop_ref, &[]);
        }
    }
    defer_stack.pop();
    Ok(())
}

#[allow(clippy::too_many_arguments)]
fn compile_stmt_inline(
    builder: &mut FunctionBuilder,
    module: &mut JITModule,
    alloc_func: FuncId,
    arena_push_func: FuncId,
    arena_pop_func: FuncId,
    functions: &HashMap<String, FuncId>,
    structs: &HashMap<String, StructLayout>,
    fn_sigs: &HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
    variables: &mut HashMap<String, Variable>,
    var_types: &mut HashMap<String, ast::Type>,
    var_index: &mut u32,
    stmt: &ast::Stmt,
    returned: &mut bool,
    defer_stack: &mut Vec<Vec<ast::Block>>,
    loop_stack: &[(Option<String>, Block, Block)],
) -> Result<()> {
    match stmt {
        ast::Stmt::Let { name, ty, value, .. } => {
            let val_opt = if let ast::Expr::Call { func, args, .. } = value {
                if let ast::Expr::Ident(fn_name) = func.as_ref() {
                    if fn_name == "hashmap_new" && args.is_empty() {
                        if let Some(ast::Type::HashMap(key_ty, _)) = ty {
                            if matches!(key_ty.as_ref(), ast::Type::Str) {
                                if let Some(&func_id) = functions.get("hashmap_new_str") {
                                    let func_ref = module.declare_func_in_func(func_id, builder.func);
                                    let call = builder.ins().call(func_ref, &[]);
                                    Some(builder.inst_results(call)[0])
                                } else {
                                    None
                                }
                            } else {
                                None
                            }
                        } else {
                            None
                        }
                    } else {
                        None
                    }
                } else {
                    None
                }
            } else {
                None
            };
            let mut val = if let Some(v) = val_opt {
                v
            } else {
                compile_expr_inline(
                builder,
                module,
                alloc_func,
                arena_push_func,
                arena_pop_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                value,
            )?
            };
            let var = Variable::new(*var_index as usize);
            *var_index += 1;

            let inferred_type = if let Some(t) = ty {
                t.clone()
            } else {
                infer_expr_type(value, var_types, structs, fn_sigs)
            };
            var_types.insert(name.clone(), inferred_type.clone());

            let var_type = if let Some(t) = ty {
                convert_ast_type(t)
            } else {
                convert_ast_type(&inferred_type)
            };

            val = cast_value(builder, val, var_type);

            builder.declare_var(var, var_type);
            builder.def_var(var, val);
            variables.insert(name.clone(), var);
        }
        ast::Stmt::Assign { target, value } => {
            let val = compile_expr_inline(
                builder,
                module,
                alloc_func,
                arena_push_func,
                arena_pop_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                value,
            )?;

            match target {
                ast::Expr::Ident(name) => {
                    if let Some(&var) = variables.get(name) {
                        let cur = builder.use_var(var);
                        let var_ty = builder.func.dfg.value_type(cur);
                        let val = cast_value(builder, val, var_ty);
                        builder.def_var(var, val);
                    }
                }
                ast::Expr::Field { expr, field } => {
                    let obj_ptr = compile_expr_inline(
                        builder,
                        module,
                        alloc_func,
                        arena_push_func,
                        arena_pop_func,
                        functions,
                        structs,
                        fn_sigs,
                        variables,
                        var_types,
                        var_index,
                        defer_stack,
                        expr,
                    )?;

                    if let Some((offset, ty)) = resolve_field(structs, expr, field, var_types) {
                        let val = cast_value(builder, val, convert_ast_type(&ty));
                        builder
                            .ins()
                            .store(MemFlags::new(), val, obj_ptr, offset as i32);
                    }
                }
                ast::Expr::Index { expr, index } => {
                    let arr_ptr = compile_expr_inline(
                        builder,
                        module,
                        alloc_func,
                        arena_push_func,
                        arena_pop_func,
                        functions,
                        structs,
                        fn_sigs,
                        variables,
                        var_types,
                        var_index,
                        defer_stack,
                        expr,
                    )?;
                    let idx = compile_expr_inline(
                        builder,
                        module,
                        alloc_func,
                        arena_push_func,
                        arena_pop_func,
                        functions,
                        structs,
                        fn_sigs,
                        variables,
                        var_types,
                        var_index,
                        defer_stack,
                        index,
                    )?;

                    let arr_ty = infer_expr_type(expr, var_types, structs, fn_sigs);
                    let base_data_ptr = match arr_ty {
                        ast::Type::Slice(_) => {
                            builder.ins().load(types::I64, MemFlags::new(), arr_ptr, 0)
                        }
                        _ => arr_ptr,
                    };

                    let (elem_ty, elem_size_bytes) =
                        infer_array_elem_type(expr, var_types, structs, fn_sigs)
                            .map(|ty| {
                                let size = type_size(&ty, structs);
                                (ty, size)
                            })
                            .unwrap_or((ast::Type::I32, 4));
                    let val = cast_value(builder, val, convert_ast_type(&elem_ty));
                    let idx = cast_value(builder, idx, types::I32);
                    let elem_size = builder.ins().iconst(types::I64, elem_size_bytes as i64);
                    let idx_ext = builder.ins().sextend(types::I64, idx);
                    let offset = builder.ins().imul(idx_ext, elem_size);
                    let elem_addr = builder.ins().iadd(base_data_ptr, offset);

                    builder.ins().store(MemFlags::new(), val, elem_addr, 0);
                }
                _ => {}
            }
        }
        ast::Stmt::Return(expr) => {
            if let Some(e) = expr {
                let mut val = compile_expr_inline(
                    builder,
                    module,
                    alloc_func,
                    arena_push_func,
                    arena_pop_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    defer_stack,
                    e,
                )?;
                if let Some(ret) = builder.func.signature.returns.first() {
                    val = cast_value(builder, val, ret.value_type);
                    emit_defer_stack(
                        builder,
                        module,
                        alloc_func,
                        arena_push_func,
                        arena_pop_func,
                        functions,
                        structs,
                        fn_sigs,
                        variables,
                        var_types,
                        var_index,
                        defer_stack,
                    )?;
                    builder.ins().return_(&[val]);
                } else {
                    emit_defer_stack(
                        builder,
                        module,
                        alloc_func,
                        arena_push_func,
                        arena_pop_func,
                        functions,
                        structs,
                        fn_sigs,
                        variables,
                        var_types,
                        var_index,
                        defer_stack,
                    )?;
                    builder.ins().return_(&[]);
                }
            } else {
                emit_defer_stack(
                    builder,
                    module,
                    alloc_func,
                    arena_push_func,
                    arena_pop_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    defer_stack,
                )?;
                // NOTE: Do NOT pop watermarks on return - see note above.
                builder.ins().return_(&[]);
            }
            *returned = true;
        }
        ast::Stmt::Defer(block) => {
            let Some(scope_defers) = defer_stack.last_mut() else {
                return Err(anyhow!("defer used outside of a block"));
            };
            scope_defers.push(block.clone());
        }
        ast::Stmt::If {
            condition,
            then_block,
            else_block,
        } => {
            let cond_val = compile_expr_inline(
                builder,
                module,
                alloc_func,
                arena_push_func,
                arena_pop_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                condition,
            )?;
            let cond_val = bool_value_to_i8(builder, cond_val)?;

            let then_bb = builder.create_block();
            let else_bb = builder.create_block();
            let merge_bb = builder.create_block();

            builder.ins().brif(cond_val, then_bb, &[], else_bb, &[]);

            let parent_vars = variables.clone();
            let parent_types = var_types.clone();

            builder.switch_to_block(then_bb);
            *variables = parent_vars.clone();
            *var_types = parent_types.clone();
            let mut then_returned = false;
            compile_block_inline(
                builder,
                module,
                alloc_func,
                arena_push_func,
                arena_pop_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                then_block,
                &mut then_returned,
                defer_stack,
                loop_stack,
            )?;
            if !then_returned {
                builder.ins().jump(merge_bb, &[]);
            }

            builder.switch_to_block(else_bb);
            *variables = parent_vars.clone();
            *var_types = parent_types.clone();
            let mut else_returned = false;
            if let Some(else_block) = else_block {
                compile_block_inline(
                    builder,
                    module,
                    alloc_func,
                    arena_push_func,
                    arena_pop_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    else_block,
                    &mut else_returned,
                    defer_stack,
                    loop_stack,
                )?;
            }
            if !else_returned {
                builder.ins().jump(merge_bb, &[]);
            }

            *variables = parent_vars;
            *var_types = parent_types;
            if then_returned && else_returned {
                *returned = true;
                return Ok(());
            }

            builder.switch_to_block(merge_bb);
        }
        ast::Stmt::For {
            label,
            var,
            iter,
            body,
        } => {
            // Check if iterator is a range expression
            if let ast::Expr::Range {
                start,
                end,
                inclusive,
            } = iter
            {
                // Range-based for loop: for i in start..end or start..=end
                let start_val = compile_expr_inline(
                    builder,
                    module,
                    alloc_func,
                    arena_push_func,
                    arena_pop_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    defer_stack,
                    start,
                )?;
                let end_val = compile_expr_inline(
                    builder,
                    module,
                    alloc_func,
                    arena_push_func,
                    arena_pop_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    defer_stack,
                    end,
                )?;

                // Infer the element type from the start expression
                let elem_ty = infer_expr_type(start, var_types, structs, fn_sigs);
                let cr_type = convert_ast_type(&elem_ty);

                // For inclusive ranges, add 1 to end
                let end_val = if *inclusive {
                    builder.ins().iadd_imm(end_val, 1)
                } else {
                    end_val
                };

                // Create the loop index variable (initialized to start)
                let idx_var = Variable::new(*var_index as usize);
                *var_index += 1;
                builder.declare_var(idx_var, cr_type);
                builder.def_var(idx_var, start_val);

                let loop_bb = builder.create_block();
                let body_bb = builder.create_block();
                let continue_bb = builder.create_block(); // continue jumps here
                let exit_bb = builder.create_block();

                builder.ins().jump(loop_bb, &[]);

                // Loop header: check if idx < end
                builder.switch_to_block(loop_bb);
                let idx_val = builder.use_var(idx_var);
                let cond = builder.ins().icmp(IntCC::SignedLessThan, idx_val, end_val);
                builder.ins().brif(cond, body_bb, &[], exit_bb, &[]);

                // Loop body
                builder.switch_to_block(body_bb);
                let parent_vars = variables.clone();
                let parent_types = var_types.clone();

                // Bind the loop variable to the current index value
                let loop_var = Variable::new(*var_index as usize);
                *var_index += 1;
                builder.declare_var(loop_var, cr_type);
                variables.insert(var.clone(), loop_var);
                var_types.insert(var.clone(), elem_ty.clone());

                let idx_val = builder.use_var(idx_var);
                builder.def_var(loop_var, idx_val);

                let mut body_returned = false;
                let mut inner_loop_stack = loop_stack.to_vec();
                inner_loop_stack.push((label.clone(), exit_bb, continue_bb));
                compile_block_inline(
                    builder,
                    module,
                    alloc_func,
                    arena_push_func,
                    arena_pop_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    body,
                    &mut body_returned,
                    defer_stack,
                    &inner_loop_stack,
                )?;

                if !body_returned {
                    builder.ins().jump(continue_bb, &[]);
                }

                // Continue block: increment index and jump to loop header
                builder.switch_to_block(continue_bb);
                let idx_val = builder.use_var(idx_var);
                let next = builder.ins().iadd_imm(idx_val, 1);
                builder.def_var(idx_var, next);
                builder.ins().jump(loop_bb, &[]);

                *variables = parent_vars;
                *var_types = parent_types;

                builder.switch_to_block(exit_bb);
            } else {
                // Array-based for loop (existing implementation)
                let arr_ptr = compile_expr_inline(
                    builder,
                    module,
                    alloc_func,
                    arena_push_func,
                    arena_pop_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    defer_stack,
                    iter,
                )?;

                let Some(elem_ty) = infer_array_elem_type(iter, var_types, structs, fn_sigs) else {
                    return Err(anyhow!("for-loop requires an array or range expression"));
                };
                let arr_ty = infer_expr_type(iter, var_types, structs, fn_sigs);
                let (arr_base_data, len_val) = match arr_ty {
                    ast::Type::Slice(_) => {
                        let data = builder.ins().load(types::I64, MemFlags::new(), arr_ptr, 0);
                        let len = builder.ins().load(types::I64, MemFlags::new(), arr_ptr, 8);
                        (data, len)
                    }
                    _ => {
                        let Some(len) = infer_array_len(iter, var_types, structs, fn_sigs) else {
                            return Err(anyhow!("for-loop requires an array or slice"));
                        };
                        (arr_ptr, builder.ins().iconst(types::I64, len as i64))
                    }
                };

                let idx_var = Variable::new(*var_index as usize);
                *var_index += 1;
                builder.declare_var(idx_var, types::I64);
                let zero = builder.ins().iconst(types::I64, 0);
                builder.def_var(idx_var, zero);

                let loop_bb = builder.create_block();
                let body_bb = builder.create_block();
                let continue_bb = builder.create_block(); // continue jumps here
                let exit_bb = builder.create_block();

                builder.ins().jump(loop_bb, &[]);

                builder.switch_to_block(loop_bb);
                let idx_val = builder.use_var(idx_var);
                let cond = builder
                    .ins()
                    .icmp(IntCC::UnsignedLessThan, idx_val, len_val);
                builder.ins().brif(cond, body_bb, &[], exit_bb, &[]);

                builder.switch_to_block(body_bb);
                let parent_vars = variables.clone();
                let parent_types = var_types.clone();

                let loop_var = Variable::new(*var_index as usize);
                *var_index += 1;
                builder.declare_var(loop_var, convert_ast_type(&elem_ty));
                variables.insert(var.clone(), loop_var);
                var_types.insert(var.clone(), elem_ty.clone());

                let idx_val = builder.use_var(idx_var);
                let elem_size = type_size(&elem_ty, structs) as i64;
                let elem_size_val = builder.ins().iconst(types::I64, elem_size);
                let offset = builder.ins().imul(idx_val, elem_size_val);
                let elem_addr = builder.ins().iadd(arr_base_data, offset);
                let elem_val =
                    builder
                        .ins()
                        .load(convert_ast_type(&elem_ty), MemFlags::new(), elem_addr, 0);
                builder.def_var(loop_var, elem_val);

                let mut body_returned = false;
                let mut inner_loop_stack = loop_stack.to_vec();
                inner_loop_stack.push((label.clone(), exit_bb, continue_bb));
                compile_block_inline(
                    builder,
                    module,
                    alloc_func,
                    arena_push_func,
                    arena_pop_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    body,
                    &mut body_returned,
                    defer_stack,
                    &inner_loop_stack,
                )?;

                if !body_returned {
                    builder.ins().jump(continue_bb, &[]);
                }

                // Continue block: increment index and jump to loop header
                builder.switch_to_block(continue_bb);
                let idx_val = builder.use_var(idx_var);
                let next = builder.ins().iadd_imm(idx_val, 1);
                builder.def_var(idx_var, next);
                builder.ins().jump(loop_bb, &[]);

                *variables = parent_vars;
                *var_types = parent_types;

                builder.switch_to_block(exit_bb);
            }
        }
        ast::Stmt::Loop { label, body } => {
            let loop_bb = builder.create_block();
            let exit_bb = builder.create_block();

            builder.ins().jump(loop_bb, &[]);
            builder.switch_to_block(loop_bb);

            let parent_vars = variables.clone();
            let parent_types = var_types.clone();

            let mut body_returned = false;
            let mut inner_loop_stack = loop_stack.to_vec();
            inner_loop_stack.push((label.clone(), exit_bb, loop_bb));
            compile_block_inline(
                builder,
                module,
                alloc_func,
                arena_push_func,
                arena_pop_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                body,
                &mut body_returned,
                defer_stack,
                &inner_loop_stack,
            )?;

            if !body_returned {
                builder.ins().jump(loop_bb, &[]);
            }

            *variables = parent_vars;
            *var_types = parent_types;

            builder.switch_to_block(exit_bb);
        }
        ast::Stmt::While {
            label,
            condition,
            body,
        } => {
            let loop_header = builder.create_block();
            let loop_body = builder.create_block();
            let exit_bb = builder.create_block();

            builder.ins().jump(loop_header, &[]);
            builder.switch_to_block(loop_header);

            // Evaluate condition
            let cond_val = compile_expr_inline(
                builder,
                module,
                alloc_func,
                arena_push_func,
                arena_pop_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                condition,
            )?;
            let cond_bool = bool_value_to_i8(builder, cond_val)?;
            let cond = builder.ins().icmp_imm(IntCC::NotEqual, cond_bool, 0);
            builder.ins().brif(cond, loop_body, &[], exit_bb, &[]);

            builder.switch_to_block(loop_body);

            let parent_vars = variables.clone();
            let parent_types = var_types.clone();

            let mut body_returned = false;
            let mut inner_loop_stack = loop_stack.to_vec();
            inner_loop_stack.push((label.clone(), exit_bb, loop_header));
            compile_block_inline(
                builder,
                module,
                alloc_func,
                arena_push_func,
                arena_pop_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                body,
                &mut body_returned,
                defer_stack,
                &inner_loop_stack,
            )?;

            if !body_returned {
                builder.ins().jump(loop_header, &[]);
            }

            *variables = parent_vars;
            *var_types = parent_types;

            builder.switch_to_block(exit_bb);
        }
        ast::Stmt::Break(target_label) => {
            let target_entry = if let Some(target) = target_label {
                loop_stack
                    .iter()
                    .rev()
                    .find(|(lbl, _, _)| lbl.as_deref() == Some(target.as_str()))
            } else {
                loop_stack.last()
            };
            if let Some((_, exit_block, _)) = target_entry {
                // Pop watermark for current block before jumping to exit
                // TODO: For deeply nested blocks inside loops, we may need to pop more watermarks
                emit_arena_pops(builder, module, arena_pop_func, 1);
                builder.ins().jump(*exit_block, &[]);
                *returned = true; // Mark as returned to stop further code gen in this block
            } else {
                return Err(anyhow!("break statement outside of loop or invalid label"));
            }
        }
        ast::Stmt::Continue(target_label) => {
            let target_entry = if let Some(target) = target_label {
                loop_stack
                    .iter()
                    .rev()
                    .find(|(lbl, _, _)| lbl.as_deref() == Some(target.as_str()))
            } else {
                loop_stack.last()
            };
            if let Some((_, _, continue_block)) = target_entry {
                // Pop watermark for current block before jumping to continue point
                // TODO: For deeply nested blocks inside loops, we may need to pop more watermarks
                emit_arena_pops(builder, module, arena_pop_func, 1);
                builder.ins().jump(*continue_block, &[]);
                *returned = true; // Mark as returned to stop further code gen in this block
            } else {
                return Err(anyhow!("continue statement outside of loop or invalid label"));
            }
        }
        ast::Stmt::Match { expr, arms } => {
            if arms.is_empty() {
                return Ok(());
            }

            let match_val = compile_expr_inline(
                builder,
                module,
                alloc_func,
                arena_push_func,
                arena_pop_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                expr,
            )?;
            let match_expr_ty = infer_expr_type(expr, var_types, structs, fn_sigs);

            let merge_bb = builder.create_block();
            let default_bb = builder.create_block();

            let mut arm_blocks = Vec::new();
            for arm in arms {
                let block = builder.create_block();
                arm_blocks.push((arm, block));
            }

            for (i, (arm, arm_bb)) in arm_blocks.iter().enumerate() {
                let cond = if pattern_is_wildcard(&arm.pattern) {
                    builder.ins().iconst(types::I8, 1)
                } else {
                    compile_pattern_cond(builder, match_val, &arm.pattern, structs)?
                };
                let is_last = i == arm_blocks.len() - 1;
                let fallthrough = if is_last {
                    default_bb
                } else {
                    builder.create_block()
                };
                builder.ins().brif(cond, *arm_bb, &[], fallthrough, &[]);
                if !is_last {
                    builder.switch_to_block(fallthrough);
                    builder.seal_block(fallthrough);
                }
            }

            builder.switch_to_block(default_bb);
            builder.seal_block(default_bb);
            builder.ins().jump(merge_bb, &[]);

            let parent_vars = variables.clone();
            let parent_types = var_types.clone();
            let mut all_returned = true;
            let exhaustive = arms.iter().any(|arm| pattern_is_wildcard(&arm.pattern));

            for (arm, arm_bb) in arm_blocks {
                builder.switch_to_block(arm_bb);
                builder.seal_block(arm_bb);
                let mut local_vars = parent_vars.clone();
                let mut local_types = parent_types.clone();

                bind_match_pattern(
                    builder,
                    &arm.pattern,
                    match_val,
                    &match_expr_ty,
                    structs,
                    var_index,
                    &mut local_vars,
                    &mut local_types,
                );

                let mut arm_returned = false;
                match &arm.body {
                    ast::MatchBody::Expr(expr) => {
                        compile_expr_inline(
                            builder,
                            module,
                            alloc_func,
                            arena_push_func,
                            arena_pop_func,
                            functions,
                            structs,
                            fn_sigs,
                            &local_vars,
                            &local_types,
                            var_index,
                            defer_stack,
                            expr,
                        )?;
                    }
                    ast::MatchBody::Block(block) => {
                        compile_block_inline(
                            builder,
                            module,
                            alloc_func,
                            arena_push_func,
                            arena_pop_func,
                            functions,
                            structs,
                            fn_sigs,
                            &mut local_vars,
                            &mut local_types,
                            var_index,
                            block,
                            &mut arm_returned,
                            defer_stack,
                            loop_stack,
                        )?;
                    }
                }

                if !arm_returned {
                    builder.ins().jump(merge_bb, &[]);
                    all_returned = false;
                }
            }

            builder.switch_to_block(merge_bb);
            builder.seal_block(merge_bb);

            if exhaustive && all_returned {
                *returned = true;
            }
        }
        ast::Stmt::Expr(expr) => {
            compile_expr_inline(
                builder,
                module,
                alloc_func,
                arena_push_func,
                arena_pop_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                expr,
            )?;
        }
        _ => {}
    }
    Ok(())
}

/// Emit N arena_pop calls for early exit (return/break/continue).
/// This restores watermarks for all scopes being exited.
fn emit_arena_pops(
    builder: &mut FunctionBuilder,
    module: &mut JITModule,
    arena_pop_func: FuncId,
    count: usize,
) {
    let pop_ref = module.declare_func_in_func(arena_pop_func, builder.func);
    for _ in 0..count {
        builder.ins().call(pop_ref, &[]);
    }
}

#[allow(clippy::too_many_arguments)]
fn emit_defer_stack(
    builder: &mut FunctionBuilder,
    module: &mut JITModule,
    alloc_func: FuncId,
    arena_push_func: FuncId,
    arena_pop_func: FuncId,
    functions: &HashMap<String, FuncId>,
    structs: &HashMap<String, StructLayout>,
    fn_sigs: &HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
    variables: &mut HashMap<String, Variable>,
    var_types: &mut HashMap<String, ast::Type>,
    var_index: &mut u32,
    defer_stack: &[Vec<ast::Block>],
) -> Result<()> {
    for scope in defer_stack.iter().rev() {
        emit_defer_blocks(
            builder,
            module,
            alloc_func,
            arena_push_func,
            arena_pop_func,
            functions,
            structs,
            fn_sigs,
            variables,
            var_types,
            var_index,
            scope,
        )?;
    }
    Ok(())
}

#[allow(clippy::too_many_arguments)]
fn emit_defer_blocks(
    builder: &mut FunctionBuilder,
    module: &mut JITModule,
    alloc_func: FuncId,
    arena_push_func: FuncId,
    arena_pop_func: FuncId,
    functions: &HashMap<String, FuncId>,
    structs: &HashMap<String, StructLayout>,
    fn_sigs: &HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
    variables: &mut HashMap<String, Variable>,
    var_types: &mut HashMap<String, ast::Type>,
    var_index: &mut u32,
    defers: &[ast::Block],
) -> Result<()> {
    for block in defers.iter().rev() {
        let saved_vars = variables.clone();
        let saved_types = var_types.clone();
        let mut local_returned = false;
        let mut local_defer_stack: Vec<Vec<ast::Block>> = Vec::new();

        compile_block_inline(
            builder,
            module,
            alloc_func,
            arena_push_func,
            arena_pop_func,
            functions,
            structs,
            fn_sigs,
            variables,
            var_types,
            var_index,
            block,
            &mut local_returned,
            &mut local_defer_stack,
            &[], // no loop context in defer blocks
        )?;

        if local_returned {
            return Err(anyhow!(
                "return or break/continue inside defer is not supported"
            ));
        }

        *variables = saved_vars;
        *var_types = saved_types;
    }
    Ok(())
}

#[allow(clippy::too_many_arguments)]
fn compile_block_value(
    builder: &mut FunctionBuilder,
    module: &mut JITModule,
    alloc_func: FuncId,
    arena_push_func: FuncId,
    arena_pop_func: FuncId,
    functions: &HashMap<String, FuncId>,
    structs: &HashMap<String, StructLayout>,
    fn_sigs: &HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
    variables: &HashMap<String, Variable>,
    var_types: &HashMap<String, ast::Type>,
    var_index: &mut u32,
    block: &ast::Block,
    defer_stack: &mut Vec<Vec<ast::Block>>,
    loop_stack: &[(Option<String>, Block, Block)],
) -> Result<Option<Value>> {
    defer_stack.push(Vec::new());
    let mut last_val = None;
    let mut returned = false;
    let mut local_vars = variables.clone();
    let mut local_types = var_types.clone();

    for stmt in &block.statements {
        if returned {
            break;
        }
        match stmt {
            ast::Stmt::Expr(expr) => {
                last_val = Some(compile_expr_inline(
                    builder,
                    module,
                    alloc_func,
                    arena_push_func,
                    arena_pop_func,
                    functions,
                    structs,
                    fn_sigs,
                    &local_vars,
                    &local_types,
                    var_index,
                    defer_stack,
                    expr,
                )?);
            }
            _ => {
                compile_stmt_inline(
                    builder,
                    module,
                    alloc_func,
                    arena_push_func,
                    arena_pop_func,
                    functions,
                    structs,
                    fn_sigs,
                    &mut local_vars,
                    &mut local_types,
                    var_index,
                    stmt,
                    &mut returned,
                    defer_stack,
                    loop_stack,
                )?;
            }
        }
    }

    if returned {
        return Err(anyhow!(
            "return/break/continue inside match arm block expression is not supported yet"
        ));
    }

    if let Some(defers) = defer_stack.last() {
        emit_defer_blocks(
            builder,
            module,
            alloc_func,
            arena_push_func,
            arena_pop_func,
            functions,
            structs,
            fn_sigs,
            &mut local_vars,
            &mut local_types,
            var_index,
            defers,
        )?;
    }
    defer_stack.pop();

    Ok(last_val)
}

fn bind_enum_payload_fields(
    builder: &mut FunctionBuilder,
    match_val: Value,
    bindings: &[String],
    var_index: &mut u32,
    local_vars: &mut HashMap<String, Variable>,
    local_types: &mut HashMap<String, ast::Type>,
) {
    if bindings.is_empty() {
        return;
    }
    let val = cast_value(builder, match_val, types::I64);
    if bindings.len() == 1 {
        bind_shifted_payload(
            builder,
            val,
            &bindings[0],
            8,
            None,
            var_index,
            local_vars,
            local_types,
        );
        return;
    }
    if bindings.len() == 2 {
        bind_shifted_payload(
            builder,
            val,
            &bindings[0],
            20,
            None,
            var_index,
            local_vars,
            local_types,
        );
        bind_shifted_payload(
            builder,
            val,
            &bindings[1],
            8,
            Some(4095),
            var_index,
            local_vars,
            local_types,
        );
    }
}

#[allow(clippy::too_many_arguments)]
fn bind_shifted_payload(
    builder: &mut FunctionBuilder,
    val: Value,
    name: &str,
    shift: i64,
    mask: Option<i64>,
    var_index: &mut u32,
    local_vars: &mut HashMap<String, Variable>,
    local_types: &mut HashMap<String, ast::Type>,
) {
    if name == "_" {
        return;
    }
    let var = Variable::new(*var_index as usize);
    *var_index += 1;
    builder.declare_var(var, types::I64);
    let shift_val = builder.ins().iconst(types::I64, shift);
    let mut extracted = builder.ins().ushr(val, shift_val);
    if let Some(bits) = mask {
        extracted = builder.ins().band_imm(extracted, bits);
    }
    builder.def_var(var, extracted);
    local_vars.insert(name.to_string(), var);
    local_types.insert(name.to_string(), ast::Type::I64);
}

fn pattern_is_wildcard(pattern: &ast::Pattern) -> bool {
    matches!(pattern, ast::Pattern::Ident(_))
}

fn pattern_has_cond(pattern: &ast::Pattern) -> bool {
    match pattern {
        ast::Pattern::Ident(_) | ast::Pattern::Unit => false,
        ast::Pattern::Tuple(sub_pats) => sub_pats.iter().any(pattern_has_cond),
        ast::Pattern::Struct { fields, .. } => fields.iter().any(|(_, p)| pattern_has_cond(p)),
        ast::Pattern::Some(_) => true,
        ast::Pattern::None => true,
        ast::Pattern::ResultOk(_) => true,
        ast::Pattern::ResultErr(_) => true,
        ast::Pattern::Bool(_)
        | ast::Pattern::Literal(_)
        | ast::Pattern::EnumVariant { .. }
        | ast::Pattern::EnumPayload { .. } => true,
    }
}

fn compile_pattern_cond(
    builder: &mut FunctionBuilder,
    value: Value,
    pattern: &ast::Pattern,
    structs: &HashMap<String, StructLayout>,
) -> Result<Value> {
    match pattern {
        ast::Pattern::Ident(_) => Ok(builder.ins().iconst(types::I8, 1)),
        ast::Pattern::Unit => Ok(builder.ins().iconst(types::I8, 1)),
        ast::Pattern::Bool(b) => {
            let val = bool_value_to_i8(builder, value)?;
            let expected = builder.ins().iconst(types::I8, if *b { 1 } else { 0 });
            Ok(builder.ins().icmp(IntCC::Equal, val, expected))
        }
        ast::Pattern::Literal(lit) => {
            let val_ty = builder.func.dfg.value_type(value);
            match lit {
                ast::Literal::Int(n) => {
                    if is_float_type(val_ty) {
                        return Err(anyhow!("Cannot match int literal against float value"));
                    }
                    let expected = builder.ins().iconst(val_ty, *n);
                    Ok(builder.ins().icmp(IntCC::Equal, value, expected))
                }
                ast::Literal::Char(c) => {
                    if is_float_type(val_ty) {
                        return Err(anyhow!("Cannot match char literal against float value"));
                    }
                    let expected = builder.ins().iconst(val_ty, *c as i64);
                    Ok(builder.ins().icmp(IntCC::Equal, value, expected))
                }
                ast::Literal::Float(f) => {
                    if !is_float_type(val_ty) {
                        return Err(anyhow!("Cannot match float literal against int value"));
                    }
                    let expected = if val_ty == types::F32 {
                        builder.ins().f32const(*f as f32)
                    } else {
                        builder.ins().f64const(*f)
                    };
                    Ok(builder.ins().fcmp(FloatCC::Equal, value, expected))
                }
                ast::Literal::Bool(b) => {
                    let val = bool_value_to_i8(builder, value)?;
                    let expected = builder.ins().iconst(types::I8, if *b { 1 } else { 0 });
                    Ok(builder.ins().icmp(IntCC::Equal, val, expected))
                }
                ast::Literal::String(_) | ast::Literal::HexColor(_) => Err(anyhow!(
                    "Match on string/hex literals is not supported in Kernel JIT yet"
                )),
            }
        }
        ast::Pattern::Some(sub_pat) => {
            let val = cast_value(builder, value, types::I64);
            let not_null = builder.ins().icmp_imm(IntCC::NotEqual, val, 0);
            if !pattern_has_cond(sub_pat) {
                Ok(not_null)
            } else {
                let dummy_slot = builder.create_sized_stack_slot(StackSlotData::new(StackSlotKind::ExplicitSlot, 16, 3));
                let dummy_ptr = builder.ins().stack_addr(types::I64, dummy_slot, 0);
                let safe_ptr = builder.ins().select(not_null, val, dummy_ptr);
                let inner_val = builder.ins().load(types::I64, MemFlags::new(), safe_ptr, 0);
                let sub_cond = compile_pattern_cond(builder, inner_val, sub_pat, structs)?;
                let sub_cond_i8 = bool_value_to_i8(builder, sub_cond)?;
                let not_null_i8 = bool_value_to_i8(builder, not_null)?;
                Ok(builder.ins().band(not_null_i8, sub_cond_i8))
            }
        }
        ast::Pattern::None => {
            let val = cast_value(builder, value, types::I64);
            Ok(builder.ins().icmp_imm(IntCC::Equal, val, 0))
        }
        ast::Pattern::ResultOk(sub_pat) => {
            let ptr = cast_value(builder, value, types::I64);
            let tag = builder.ins().load(types::I64, MemFlags::new(), ptr, 0);
            let is_ok = builder.ins().icmp_imm(IntCC::Equal, tag, 0);
            if !pattern_has_cond(sub_pat) {
                Ok(is_ok)
            } else {
                let inner_val = builder.ins().load(types::I64, MemFlags::new(), ptr, 8);
                let sub_cond = compile_pattern_cond(builder, inner_val, sub_pat, structs)?;
                let sub_cond_i8 = bool_value_to_i8(builder, sub_cond)?;
                let is_ok_i8 = bool_value_to_i8(builder, is_ok)?;
                Ok(builder.ins().band(is_ok_i8, sub_cond_i8))
            }
        }
        ast::Pattern::ResultErr(sub_pat) => {
            let ptr = cast_value(builder, value, types::I64);
            let tag = builder.ins().load(types::I64, MemFlags::new(), ptr, 0);
            let is_err = builder.ins().icmp_imm(IntCC::Equal, tag, 1);
            if !pattern_has_cond(sub_pat) {
                Ok(is_err)
            } else {
                let inner_val = builder.ins().load(types::I64, MemFlags::new(), ptr, 8);
                let sub_cond = compile_pattern_cond(builder, inner_val, sub_pat, structs)?;
                let sub_cond_i8 = bool_value_to_i8(builder, sub_cond)?;
                let is_err_i8 = bool_value_to_i8(builder, is_err)?;
                Ok(builder.ins().band(is_err_i8, sub_cond_i8))
            }
        }
        ast::Pattern::Tuple(sub_pats) => {
            let ptr = cast_value(builder, value, types::I64);
            let mut cond = builder.ins().iconst(types::I8, 1);
            for (i, sub_pat) in sub_pats.iter().enumerate() {
                if pattern_has_cond(sub_pat) {
                    let offset = (i * 8) as i32;
                    let elem_val = builder.ins().load(types::I64, MemFlags::new(), ptr, offset);
                    let sub_cond = compile_pattern_cond(builder, elem_val, sub_pat, structs)?;
                    let sub_cond_i8 = bool_value_to_i8(builder, sub_cond)?;
                    cond = builder.ins().band(cond, sub_cond_i8);
                }
            }
            Ok(cond)
        }
        ast::Pattern::Struct { name, fields } => {
            let ptr = cast_value(builder, value, types::I64);
            let mut cond = builder.ins().iconst(types::I8, 1);
            if let Some(layout) = structs.get(name) {
                for (field_name, sub_pat) in fields {
                    if pattern_has_cond(sub_pat) {
                        if let Some((offset, field_ty)) = layout
                            .fields
                            .iter()
                            .find(|(n, _, _)| n == field_name)
                            .map(|(_, o, t)| (*o, t.clone()))
                        {
                            let cr_ty = convert_ast_type(&field_ty);
                            let field_val = builder.ins().load(cr_ty, MemFlags::new(), ptr, offset as i32);
                            let sub_cond = compile_pattern_cond(builder, field_val, sub_pat, structs)?;
                            let sub_cond_i8 = bool_value_to_i8(builder, sub_cond)?;
                            cond = builder.ins().band(cond, sub_cond_i8);
                        }
                    }
                }
            }
            Ok(cond)
        }
        ast::Pattern::EnumVariant {
            enum_name, variant, ..
        } => Err(anyhow!(
            "Enum variant pattern '{}.{}' must be lowered before JIT",
            enum_name,
            variant
        )),
        ast::Pattern::EnumPayload { tag, .. } => {
            let val = cast_value(builder, value, types::I64);
            let masked = builder.ins().band_imm(val, 255);
            Ok(builder.ins().icmp_imm(IntCC::Equal, masked, *tag))
        }
    }
}

fn bind_match_pattern(
    builder: &mut FunctionBuilder,
    pattern: &ast::Pattern,
    val: Value,
    val_ty: &ast::Type,
    structs: &HashMap<String, StructLayout>,
    var_index: &mut u32,
    local_vars: &mut HashMap<String, Variable>,
    local_types: &mut HashMap<String, ast::Type>,
) {
    match pattern {
        ast::Pattern::Ident(name) if name != "_" => {
            let var = Variable::new(*var_index as usize);
            *var_index += 1;
            let match_ty = convert_ast_type(val_ty);
            builder.declare_var(var, match_ty);
            let bound_val = cast_value(builder, val, match_ty);
            builder.def_var(var, bound_val);
            local_vars.insert(name.clone(), var);
            local_types.insert(name.clone(), val_ty.clone());
        }
        ast::Pattern::Some(sub_pat) => {
            if let ast::Type::Option(inner) = val_ty {
                let inner_ty = convert_ast_type(inner);
                let ptr = cast_value(builder, val, types::I64);
                let loaded = builder.ins().load(inner_ty, MemFlags::new(), ptr, 0);
                bind_match_pattern(
                    builder,
                    sub_pat,
                    loaded,
                    inner,
                    structs,
                    var_index,
                    local_vars,
                    local_types,
                );
            }
        }
        ast::Pattern::ResultOk(sub_pat) => {
            if let ast::Type::Result(ok_ty, _) = val_ty {
                let cr_ty = convert_ast_type(ok_ty);
                let ptr = cast_value(builder, val, types::I64);
                let loaded = builder.ins().load(cr_ty, MemFlags::new(), ptr, 8);
                bind_match_pattern(
                    builder,
                    sub_pat,
                    loaded,
                    ok_ty,
                    structs,
                    var_index,
                    local_vars,
                    local_types,
                );
            }
        }
        ast::Pattern::ResultErr(sub_pat) => {
            if let ast::Type::Result(_, err_ty) = val_ty {
                let cr_ty = convert_ast_type(err_ty);
                let ptr = cast_value(builder, val, types::I64);
                let loaded = builder.ins().load(cr_ty, MemFlags::new(), ptr, 8);
                bind_match_pattern(
                    builder,
                    sub_pat,
                    loaded,
                    err_ty,
                    structs,
                    var_index,
                    local_vars,
                    local_types,
                );
            }
        }
        ast::Pattern::Tuple(sub_pats) => {
            let ptr = cast_value(builder, val, types::I64);
            let elem_tys = if let ast::Type::Tuple(tys) = val_ty {
                tys.clone()
            } else {
                vec![]
            };
            for (i, sub_pat) in sub_pats.iter().enumerate() {
                let elem_ty = elem_tys.get(i).cloned().unwrap_or(ast::Type::I64);
                let cr_ty = convert_ast_type(&elem_ty);
                let offset = (i * 8) as i32;
                let loaded = builder.ins().load(cr_ty, MemFlags::new(), ptr, offset);
                bind_match_pattern(
                    builder,
                    sub_pat,
                    loaded,
                    &elem_ty,
                    structs,
                    var_index,
                    local_vars,
                    local_types,
                );
            }
        }
        ast::Pattern::Struct { name, fields } => {
            let ptr = cast_value(builder, val, types::I64);
            if let Some(layout) = structs.get(name) {
                for (field_name, sub_pat) in fields {
                    if let Some((offset, field_ty)) = layout
                        .fields
                        .iter()
                        .find(|(n, _, _)| n == field_name)
                        .map(|(_, o, t)| (*o, t.clone()))
                    {
                        let cr_ty = convert_ast_type(&field_ty);
                        let loaded = builder.ins().load(cr_ty, MemFlags::new(), ptr, offset as i32);
                        bind_match_pattern(
                            builder,
                            sub_pat,
                            loaded,
                            &field_ty,
                            structs,
                            var_index,
                            local_vars,
                            local_types,
                        );
                    }
                }
            }
        }
        ast::Pattern::EnumPayload { bindings, .. } => {
            bind_enum_payload_fields(
                builder,
                val,
                bindings,
                var_index,
                local_vars,
                local_types,
            );
        }
        _ => {}
    }
}

fn zero_value(builder: &mut FunctionBuilder, ty: types::Type) -> Value {
    if ty == types::F32 {
        builder.ins().f32const(0.0)
    } else if ty == types::F64 {
        builder.ins().f64const(0.0)
    } else {
        builder.ins().iconst(ty, 0)
    }
}

#[allow(clippy::too_many_arguments)]
fn compile_expr_inline(
    builder: &mut FunctionBuilder,
    module: &mut JITModule,
    alloc_func: FuncId,
    arena_push_func: FuncId,
    arena_pop_func: FuncId,
    functions: &HashMap<String, FuncId>,
    structs: &HashMap<String, StructLayout>,
    fn_sigs: &HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
    variables: &HashMap<String, Variable>,
    var_types: &HashMap<String, ast::Type>,
    var_index: &mut u32,
    defer_stack: &mut Vec<Vec<ast::Block>>,
    expr: &ast::Expr,
) -> Result<Value> {
    match expr {
        ast::Expr::Literal(lit) => {
            // Handle string literals specially as they need allocation
            if let ast::Literal::String(s) = lit {
                compile_string_literal(builder, module, alloc_func, s)
            } else {
                compile_literal_inline(builder, lit)
            }
        }
        ast::Expr::Ident(name) => {
            if let Some(&var) = variables.get(name) {
                Ok(builder.use_var(var))
            } else if let Some(&func_id) = functions.get(name) {
                let func_ref = module.declare_func_in_func(func_id, builder.func);
                Ok(builder.ins().func_addr(types::I64, func_ref))
            } else {
                Err(anyhow!("Undefined variable: {}", name))
            }
        }
        ast::Expr::Binary { op, left, right } => {
            // First, infer expression types to detect string operations
            let left_ty = infer_expr_type(left, var_types, structs, fn_sigs);
            let right_ty = infer_expr_type(right, var_types, structs, fn_sigs);

            // Handle string concatenation specially
            if matches!(op, ast::BinaryOp::Add)
                && matches!(left_ty, ast::Type::Str)
                && matches!(right_ty, ast::Type::Str)
            {
                let lhs = compile_expr_inline(
                    builder,
                    module,
                    alloc_func,
                    arena_push_func,
                    arena_pop_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    defer_stack,
                    left,
                )?;
                let rhs = compile_expr_inline(
                    builder,
                    module,
                    alloc_func,
                    arena_push_func,
                    arena_pop_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    defer_stack,
                    right,
                )?;
                return emit_string_concat(builder, module, alloc_func, lhs, rhs, var_index);
            }

            // Handle string equality comparison
            if (matches!(op, ast::BinaryOp::Eq) || matches!(op, ast::BinaryOp::Ne))
                && matches!(left_ty, ast::Type::Str)
                && matches!(right_ty, ast::Type::Str)
            {
                let lhs = compile_expr_inline(
                    builder,
                    module,
                    alloc_func,
                    arena_push_func,
                    arena_pop_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    defer_stack,
                    left,
                )?;
                let rhs = compile_expr_inline(
                    builder,
                    module,
                    alloc_func,
                    arena_push_func,
                    arena_pop_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    defer_stack,
                    right,
                )?;

                // Call bunker_str_eq runtime function
                let str_eq_func = functions
                    .get("str_eq")
                    .ok_or_else(|| anyhow!("str_eq function not found"))?;
                let func_ref = module.declare_func_in_func(*str_eq_func, builder.func);
                let call = builder.ins().call(func_ref, &[lhs, rhs]);
                let result = builder.inst_results(call)[0];

                // str_eq returns i64 (1 for equal, 0 for not equal)
                // For Ne, we need to invert the result
                if matches!(op, ast::BinaryOp::Ne) {
                    let zero = builder.ins().iconst(types::I64, 0);
                    return Ok(builder.ins().icmp(IntCC::Equal, result, zero));
                } else {
                    // For Eq, convert to i8 bool (1 if equal)
                    let one = builder.ins().iconst(types::I64, 1);
                    return Ok(builder.ins().icmp(IntCC::Equal, result, one));
                }
            }

            // Standard numeric operations
            let lhs = compile_expr_inline(
                builder,
                module,
                alloc_func,
                arena_push_func,
                arena_pop_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                left,
            )?;
            let rhs = compile_expr_inline(
                builder,
                module,
                alloc_func,
                arena_push_func,
                arena_pop_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                right,
            )?;

            let lhs_cranelift_ty = builder.func.dfg.value_type(lhs);
            let rhs_cranelift_ty = builder.func.dfg.value_type(rhs);
            let common_ty = common_numeric_type(lhs_cranelift_ty, rhs_cranelift_ty);

            let (lhs, rhs) = if let Some(common_ty) = common_ty {
                (
                    cast_value(builder, lhs, common_ty),
                    cast_value(builder, rhs, common_ty),
                )
            } else {
                (lhs, rhs)
            };

            let is_float = common_ty.is_some_and(is_float_type);
            let result = match op {
                ast::BinaryOp::Add => {
                    if is_float {
                        builder.ins().fadd(lhs, rhs)
                    } else {
                        builder.ins().iadd(lhs, rhs)
                    }
                }
                ast::BinaryOp::Sub => {
                    if is_float {
                        builder.ins().fsub(lhs, rhs)
                    } else {
                        builder.ins().isub(lhs, rhs)
                    }
                }
                ast::BinaryOp::Mul => {
                    if is_float {
                        builder.ins().fmul(lhs, rhs)
                    } else {
                        builder.ins().imul(lhs, rhs)
                    }
                }
                ast::BinaryOp::Div => {
                    if is_float {
                        builder.ins().fdiv(lhs, rhs)
                    } else {
                        builder.ins().sdiv(lhs, rhs)
                    }
                }
                ast::BinaryOp::Mod => {
                    if is_float {
                        return Err(anyhow!(
                            "Floating-point remainder is not supported yet in Kernel JIT"
                        ));
                    }
                    builder.ins().srem(lhs, rhs)
                }
                ast::BinaryOp::Eq => {
                    let b = if is_float {
                        builder.ins().fcmp(FloatCC::Equal, lhs, rhs)
                    } else {
                        builder.ins().icmp(IntCC::Equal, lhs, rhs)
                    };
                    b
                }
                ast::BinaryOp::Ne => {
                    let b = if is_float {
                        builder.ins().fcmp(FloatCC::NotEqual, lhs, rhs)
                    } else {
                        builder.ins().icmp(IntCC::NotEqual, lhs, rhs)
                    };
                    b
                }
                ast::BinaryOp::Lt => {
                    let b = if is_float {
                        builder.ins().fcmp(FloatCC::LessThan, lhs, rhs)
                    } else {
                        builder.ins().icmp(IntCC::SignedLessThan, lhs, rhs)
                    };
                    b
                }
                ast::BinaryOp::Le => {
                    let b = if is_float {
                        builder.ins().fcmp(FloatCC::LessThanOrEqual, lhs, rhs)
                    } else {
                        builder.ins().icmp(IntCC::SignedLessThanOrEqual, lhs, rhs)
                    };
                    b
                }
                ast::BinaryOp::Gt => {
                    let b = if is_float {
                        builder.ins().fcmp(FloatCC::GreaterThan, lhs, rhs)
                    } else {
                        builder.ins().icmp(IntCC::SignedGreaterThan, lhs, rhs)
                    };
                    b
                }
                ast::BinaryOp::Ge => {
                    let b = if is_float {
                        builder.ins().fcmp(FloatCC::GreaterThanOrEqual, lhs, rhs)
                    } else {
                        builder
                            .ins()
                            .icmp(IntCC::SignedGreaterThanOrEqual, lhs, rhs)
                    };
                    b
                }
                ast::BinaryOp::And => builder.ins().band(lhs, rhs),
                ast::BinaryOp::Or => builder.ins().bor(lhs, rhs),
                ast::BinaryOp::BitAnd => builder.ins().band(lhs, rhs),
                ast::BinaryOp::BitOr => builder.ins().bor(lhs, rhs),
                ast::BinaryOp::BitXor => builder.ins().bxor(lhs, rhs),
                ast::BinaryOp::Shl => builder.ins().ishl(lhs, rhs),
                ast::BinaryOp::Shr => builder.ins().sshr(lhs, rhs),
                ast::BinaryOp::As => lhs,
            };
            Ok(result)
        }
        ast::Expr::Unary { op, expr: inner } => {
            let val = compile_expr_inline(
                builder,
                module,
                alloc_func,
                arena_push_func,
                arena_pop_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                inner,
            )?;
            let result = match op {
                ast::UnaryOp::Neg => {
                    if is_float_type(builder.func.dfg.value_type(val)) {
                        builder.ins().fneg(val)
                    } else {
                        builder.ins().ineg(val)
                    }
                }
                ast::UnaryOp::Not => {
                    let bool_val = bool_value_to_i8(builder, val)?;
                    builder.ins().icmp_imm(IntCC::Equal, bool_val, 0)
                }
            };
            Ok(result)
        }
        ast::Expr::If {
            condition,
            then_expr,
            else_expr,
        } => {
            let cond_val = compile_expr_inline(
                builder,
                module,
                alloc_func,
                arena_push_func,
                arena_pop_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                condition,
            )?;
            let cond_val = bool_value_to_i8(builder, cond_val)?;

            let then_bb = builder.create_block();
            let else_bb = builder.create_block();
            let merge_bb = builder.create_block();

            builder.ins().brif(cond_val, then_bb, &[], else_bb, &[]);

            builder.switch_to_block(then_bb);
            let then_val = compile_expr_inline(
                builder,
                module,
                alloc_func,
                arena_push_func,
                arena_pop_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                then_expr,
            )?;
            let result_ty = builder.func.dfg.value_type(then_val);
            builder.append_block_param(merge_bb, result_ty);
            let then_val = cast_value(builder, then_val, result_ty);
            builder.ins().jump(merge_bb, &[then_val]);

            builder.switch_to_block(else_bb);
            let else_val = compile_expr_inline(
                builder,
                module,
                alloc_func,
                arena_push_func,
                arena_pop_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                else_expr,
            )?;
            let else_val = cast_value(builder, else_val, result_ty);
            builder.ins().jump(merge_bb, &[else_val]);

            builder.switch_to_block(merge_bb);
            Ok(builder.block_params(merge_bb)[0])
        }
        ast::Expr::Call { func, args, .. } => {
            if let ast::Expr::Ident(name) = func.as_ref() {
                // Built-in functions
                if name == "panic" {
                    if let Some(&panic_func) = functions.get("bunker_panic") {
                        let msg_ptr = if let Some(arg) = args.first() {
                            compile_expr_inline(
                                builder,
                                module,
                                alloc_func,
                                arena_push_func,
                                arena_pop_func,
                                functions,
                                structs,
                                fn_sigs,
                                variables,
                                var_types,
                                var_index,
                                defer_stack,
                                arg,
                            )?
                        } else {
                            builder.ins().iconst(types::I64, 0)
                        };
                        let panic_ref = module.declare_func_in_func(panic_func, builder.func);
                        builder.ins().call(panic_ref, &[msg_ptr]);
                    }
                    return Ok(builder.ins().iconst(types::I32, 0));
                }
                if name == "assert" {
                    if let Some(&assert_func) = functions.get("bunker_assert") {
                        if let Some(cond_arg) = args.first() {
                            let cond_val = compile_expr_inline(
                                builder,
                                module,
                                alloc_func,
                                arena_push_func,
                                arena_pop_func,
                                functions,
                                structs,
                                fn_sigs,
                                variables,
                                var_types,
                                var_index,
                                defer_stack,
                                cond_arg,
                            )?;
                            let cond_bool = bool_value_to_i8(builder, cond_val)?;
                            let msg_ptr = if args.len() > 1 {
                                compile_expr_inline(
                                    builder,
                                    module,
                                    alloc_func,
                                    arena_push_func,
                                    arena_pop_func,
                                    functions,
                                    structs,
                                    fn_sigs,
                                    variables,
                                    var_types,
                                    var_index,
                                    defer_stack,
                                    &args[1],
                                )?
                            } else {
                                builder.ins().iconst(types::I64, 0)
                            };
                            let assert_ref = module.declare_func_in_func(assert_func, builder.func);
                            builder.ins().call(assert_ref, &[cond_bool, msg_ptr]);
                        }
                    }
                    return Ok(builder.ins().iconst(types::I32, 0));
                }
                if matches!(name.as_str(), "log" | "print" | "println") {
                    return Ok(builder.ins().iconst(types::I32, 0));
                }
                // strlen builtin: returns the length of a string
                if name == "strlen" {
                    if args.len() != 1 {
                        return Err(anyhow!("strlen expects 1 argument, got {}", args.len()));
                    }
                    let str_ptr = compile_expr_inline(
                        builder,
                        module,
                        alloc_func,
                        arena_push_func,
                        arena_pop_func,
                        functions,
                        structs,
                        fn_sigs,
                        variables,
                        var_types,
                        var_index,
                        defer_stack,
                        &args[0],
                    )?;
                    // Read the length from offset 0 of the string (i64)
                    let len = get_string_len(builder, str_ptr);
                    // Convert to i32 for return
                    return Ok(builder.ins().ireduce(types::I32, len));
                }
                // len builtin: returns the length of an array or string
                if name == "len" {
                    if args.len() != 1 {
                        return Err(anyhow!("len expects 1 argument, got {}", args.len()));
                    }
                    let arg_ty = infer_expr_type(&args[0], var_types, structs, fn_sigs);
                    match arg_ty {
                        ast::Type::Array(_, size) => {
                            // For arrays, the length is known at compile time
                            return Ok(builder.ins().iconst(types::I32, size as i64));
                        }
                        ast::Type::Str => {
                            // For strings, read the length from the pointer
                            let str_ptr = compile_expr_inline(
                                builder,
                                module,
                                alloc_func,
                                arena_push_func,
                                arena_pop_func,
                                functions,
                                structs,
                                fn_sigs,
                                variables,
                                var_types,
                                var_index,
                                defer_stack,
                                &args[0],
                            )?;
                            let len = get_string_len(builder, str_ptr);
                            return Ok(builder.ins().ireduce(types::I32, len));
                        }
                        _ => {
                            return Err(anyhow!("len expects array or str, got {:?}", arg_ty));
                        }
                    }
                }
                let resolved_name = if name == "hashmap_insert" && args.len() == 3 {
                    let key_ty = infer_expr_type(&args[1], var_types, structs, fn_sigs);
                    if matches!(key_ty, ast::Type::Str) {
                        "hashmap_insert_str"
                    } else {
                        name.as_str()
                    }
                } else if name == "vec_contains" && args.len() == 2 {
                    let item_ty = infer_expr_type(&args[1], var_types, structs, fn_sigs);
                    if matches!(item_ty, ast::Type::Str) {
                        "vec_contains_str"
                    } else {
                        name.as_str()
                    }
                } else {
                    name.as_str()
                };
                if let Some(layout) = structs.get(name) {
                    let ptr = emit_alloc(builder, module, alloc_func, layout.size as i64, 8)?;
                    for (i, arg) in args.iter().enumerate() {
                        if let Some((_fname, offset, field_ty)) = layout.fields.get(i) {
                            let val = compile_expr_inline(
                                builder,
                                module,
                                alloc_func,
                                arena_push_func,
                                arena_pop_func,
                                functions,
                                structs,
                                fn_sigs,
                                variables,
                                var_types,
                                var_index,
                                defer_stack,
                                arg,
                            )?;
                            let val = cast_value(builder, val, convert_ast_type(field_ty));
                            builder.ins().store(MemFlags::new(), val, ptr, *offset as i32);
                        }
                    }
                    return Ok(ptr);
                }
                if let Some(&var) = variables.get(name) {
                    let callee_val = builder.use_var(var);
                    let (param_types, ret_ty, has_return) = match var_types.get(name) {
                        Some(ast::Type::Fn(params, ret)) => {
                            let p_tys = params.iter().map(convert_ast_type).collect::<Vec<_>>();
                            let r_ty = convert_ast_type(ret);
                            let has_ret = !matches!(ret.as_ref(), ast::Type::Unit | ast::Type::Never);
                            (p_tys, r_ty, has_ret)
                        }
                        _ => {
                            let p_tys = vec![types::I64; args.len()];
                            (p_tys, types::I64, true)
                        }
                    };

                    let mut arg_vals = vec![];
                    for (i, arg) in args.iter().enumerate() {
                        let param_ty = param_types.get(i).copied().unwrap_or(types::I64);
                        let val = compile_expr_inline(
                            builder,
                            module,
                            alloc_func,
                            arena_push_func,
                            arena_pop_func,
                            functions,
                            structs,
                            fn_sigs,
                            variables,
                            var_types,
                            var_index,
                            defer_stack,
                            arg,
                        )?;
                        arg_vals.push(cast_value(builder, val, param_ty));
                    }

                    let mut sig = module.make_signature();
                    for &p_ty in &param_types {
                        sig.params.push(AbiParam::new(p_ty));
                    }
                    if has_return {
                        sig.returns.push(AbiParam::new(ret_ty));
                    }
                    let sig_ref = builder.func.import_signature(sig);
                    let call = builder.ins().call_indirect(sig_ref, callee_val, &arg_vals);
                    let results = builder.inst_results(call);

                    if !has_return || results.is_empty() {
                        Ok(builder.ins().iconst(types::I32, 0))
                    } else {
                        Ok(results[0])
                    }
                } else if let Some(&func_id) = functions.get(resolved_name) {
                    let (param_types, has_return) = {
                        let decl = module.declarations().get_function_decl(func_id);
                        (
                            decl.signature
                                .params
                                .iter()
                                .map(|p| p.value_type)
                                .collect::<Vec<_>>(),
                            !decl.signature.returns.is_empty(),
                        )
                    };

                    let func_ref = module.declare_func_in_func(func_id, builder.func);

                    let mut arg_vals = vec![];
                    for (i, arg) in args.iter().enumerate() {
                        let Some(param_ty) = param_types.get(i).copied() else {
                            return Err(anyhow!(
                                "Too many arguments in call to {} (expected {}, got {})",
                                name,
                                param_types.len(),
                                args.len()
                            ));
                        };

                        let val = compile_expr_inline(
                            builder,
                            module,
                            alloc_func,
                            arena_push_func,
                            arena_pop_func,
                            functions,
                            structs,
                            fn_sigs,
                            variables,
                            var_types,
                            var_index,
                            defer_stack,
                            arg,
                        )?;
                        arg_vals.push(cast_value(builder, val, param_ty));
                    }

                    let call = builder.ins().call(func_ref, &arg_vals);
                    let results = builder.inst_results(call);

                    if !has_return || results.is_empty() {
                        Ok(builder.ins().iconst(types::I32, 0))
                    } else {
                        Ok(results[0])
                    }
                } else {
                    Err(anyhow!("Undefined function: {}", name))
                }
            } else if let ast::Expr::Field { expr, field } = func.as_ref() {
                let base_ty = infer_expr_type(expr, var_types, structs, fn_sigs);
                let struct_name = match &base_ty {
                    ast::Type::Named(name) => Some(name.clone()),
                    _ => None,
                };
                if let Some(sname) = struct_name {
                    let method_name = format!("{}::{}", sname, field);
                    if let Some(&func_id) = functions.get(&method_name) {
                        let (param_types, has_return) = {
                            let decl = module.declarations().get_function_decl(func_id);
                            (
                                decl.signature
                                    .params
                                    .iter()
                                    .map(|p| p.value_type)
                                    .collect::<Vec<_>>(),
                                !decl.signature.returns.is_empty(),
                            )
                        };

                        let func_ref = module.declare_func_in_func(func_id, builder.func);
                        let mut full_args = vec![expr.as_ref().clone()];
                        full_args.extend(args.iter().cloned());

                        let mut arg_vals = vec![];
                        for (i, arg) in full_args.iter().enumerate() {
                            let Some(param_ty) = param_types.get(i).copied() else {
                                return Err(anyhow!(
                                    "Too many arguments in call to {} (expected {}, got {})",
                                    method_name,
                                    param_types.len(),
                                    full_args.len()
                                ));
                            };

                            let val = compile_expr_inline(
                                builder,
                                module,
                                alloc_func,
                                arena_push_func,
                                arena_pop_func,
                                functions,
                                structs,
                                fn_sigs,
                                variables,
                                var_types,
                                var_index,
                                defer_stack,
                                arg,
                            )?;
                            arg_vals.push(cast_value(builder, val, param_ty));
                        }

                        let call = builder.ins().call(func_ref, &arg_vals);
                        let results = builder.inst_results(call);

                        if !has_return || results.is_empty() {
                            Ok(builder.ins().iconst(types::I32, 0))
                        } else {
                            Ok(results[0])
                        }
                    } else {
                        Err(anyhow!("Undefined method: {}", method_name))
                    }
                } else {
                    Err(anyhow!("Cannot call method '{}' on non-struct type {:?}", field, base_ty))
                }
            } else {
                let callee_val = compile_expr_inline(
                    builder,
                    module,
                    alloc_func,
                    arena_push_func,
                    arena_pop_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    defer_stack,
                    func,
                )?;
                let func_ty = infer_expr_type(func, var_types, structs, fn_sigs);
                let (param_types, ret_ty, has_return) = match func_ty {
                    ast::Type::Fn(params, ret) => {
                        let p_tys = params.iter().map(convert_ast_type).collect::<Vec<_>>();
                        let r_ty = convert_ast_type(&ret);
                        let has_ret = !matches!(ret.as_ref(), ast::Type::Unit | ast::Type::Never);
                        (p_tys, r_ty, has_ret)
                    }
                    _ => {
                        let p_tys = vec![types::I64; args.len()];
                        (p_tys, types::I64, true)
                    }
                };

                let mut arg_vals = vec![];
                for (i, arg) in args.iter().enumerate() {
                    let param_ty = param_types.get(i).copied().unwrap_or(types::I64);
                    let val = compile_expr_inline(
                        builder,
                        module,
                        alloc_func,
                        arena_push_func,
                        arena_pop_func,
                        functions,
                        structs,
                        fn_sigs,
                        variables,
                        var_types,
                        var_index,
                        defer_stack,
                        arg,
                    )?;
                    arg_vals.push(cast_value(builder, val, param_ty));
                }

                let mut sig = module.make_signature();
                for &p_ty in &param_types {
                    sig.params.push(AbiParam::new(p_ty));
                }
                if has_return {
                    sig.returns.push(AbiParam::new(ret_ty));
                }
                let sig_ref = builder.func.import_signature(sig);
                let call = builder.ins().call_indirect(sig_ref, callee_val, &arg_vals);
                let results = builder.inst_results(call);

                if !has_return || results.is_empty() {
                    Ok(builder.ins().iconst(types::I32, 0))
                } else {
                    Ok(results[0])
                }
            }
        }
        ast::Expr::Index { expr: arr, index } => {
            if let ast::Expr::Range { start, end, inclusive } = index.as_ref() {
                let arr_ptr = compile_expr_inline(
                    builder,
                    module,
                    alloc_func,
                    arena_push_func,
                    arena_pop_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    defer_stack,
                    arr,
                )?;
                let start_val = compile_expr_inline(
                    builder,
                    module,
                    alloc_func,
                    arena_push_func,
                    arena_pop_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    defer_stack,
                    start,
                )?;
                let end_val = compile_expr_inline(
                    builder,
                    module,
                    alloc_func,
                    arena_push_func,
                    arena_pop_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    defer_stack,
                    end,
                )?;
                let start_i64 = cast_value(builder, start_val, types::I64);
                let end_i64 = cast_value(builder, end_val, types::I64);
                let sub_len = if *inclusive {
                    let diff = builder.ins().isub(end_i64, start_i64);
                    builder.ins().iadd_imm(diff, 1)
                } else {
                    builder.ins().isub(end_i64, start_i64)
                };
                let arr_ty = infer_expr_type(arr, var_types, structs, fn_sigs);
                match arr_ty {
                    ast::Type::Slice(_) => {
                        let sub_func = functions.get("slice_sub").copied().ok_or_else(|| anyhow!("missing slice_sub function"))?;
                        let local_func = module.declare_func_in_func(sub_func, builder.func);
                        let call = builder.ins().call(local_func, &[arr_ptr, start_i64, sub_len]);
                        return Ok(builder.inst_results(call)[0]);
                    }
                    ast::Type::Vec(_) => {
                        let vec_sub_func = functions.get("vec_slice").copied().ok_or_else(|| anyhow!("missing vec_slice function"))?;
                        let local_func = module.declare_func_in_func(vec_sub_func, builder.func);
                        let call = builder.ins().call(local_func, &[arr_ptr, start_i64, sub_len]);
                        return Ok(builder.inst_results(call)[0]);
                    }
                    _ => {
                        let (_elem_ty, elem_size_bytes) =
                            infer_array_elem_type(arr, var_types, structs, fn_sigs)
                                .map(|ty| {
                                    let size = type_size(&ty, structs);
                                    (ty, size)
                                })
                                .unwrap_or((ast::Type::I32, 4));
                        let elem_size = builder.ins().iconst(types::I64, elem_size_bytes as i64);
                        let byte_offset = builder.ins().imul(start_i64, elem_size);
                        let start_addr = builder.ins().iadd(arr_ptr, byte_offset);
                        let slice_new_func = functions.get("slice_new").copied().ok_or_else(|| anyhow!("missing slice_new function"))?;
                        let local_func = module.declare_func_in_func(slice_new_func, builder.func);
                        let call = builder.ins().call(local_func, &[start_addr, sub_len, elem_size]);
                        return Ok(builder.inst_results(call)[0]);
                    }
                }
            }

            let arr_ptr = compile_expr_inline(
                builder,
                module,
                alloc_func,
                arena_push_func,
                arena_pop_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                arr,
            )?;
            let idx = compile_expr_inline(
                builder,
                module,
                alloc_func,
                arena_push_func,
                arena_pop_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                index,
            )?;
            let arr_ty = infer_expr_type(arr, var_types, structs, fn_sigs);
            let base_data_ptr = match arr_ty {
                ast::Type::Slice(_) => {
                    builder.ins().load(types::I64, MemFlags::new(), arr_ptr, 0)
                }
                _ => arr_ptr,
            };
            let (elem_ty, elem_size_bytes) =
                infer_array_elem_type(arr, var_types, structs, fn_sigs)
                    .map(|ty| {
                        let size = type_size(&ty, structs);
                        (ty, size)
                    })
                    .unwrap_or((ast::Type::I32, 4));
            let idx = cast_value(builder, idx, types::I32);
            let elem_size = builder.ins().iconst(types::I64, elem_size_bytes as i64);
            let idx_ext = builder.ins().sextend(types::I64, idx);
            let offset = builder.ins().imul(idx_ext, elem_size);
            let elem_addr = builder.ins().iadd(base_data_ptr, offset);
            Ok(builder
                .ins()
                .load(convert_ast_type(&elem_ty), MemFlags::new(), elem_addr, 0))
        }
        ast::Expr::Field { expr: obj, field } => {
            let obj_ptr = compile_expr_inline(
                builder,
                module,
                alloc_func,
                arena_push_func,
                arena_pop_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                obj,
            )?;
            if let Some((offset, ty)) = resolve_field(structs, obj, field, var_types) {
                let elem_type = convert_ast_type(&ty);
                return Ok(builder
                    .ins()
                    .load(elem_type, MemFlags::new(), obj_ptr, offset as i32));
            }
            Ok(builder.ins().iconst(types::I32, 0))
        }
        ast::Expr::Match { expr, arms } => {
            if arms.is_empty() {
                return Ok(builder.ins().iconst(types::I32, 0));
            }

            let match_val = compile_expr_inline(
                builder,
                module,
                alloc_func,
                arena_push_func,
                arena_pop_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                expr,
            )?;
            let match_expr_ty = infer_expr_type(expr, var_types, structs, fn_sigs);

            let result_ast_ty = infer_match_expr_type(arms, var_types, structs, fn_sigs);
            let result_ty = convert_ast_type(&result_ast_ty);

            let merge_bb = builder.create_block();
            builder.append_block_param(merge_bb, result_ty);
            let default_bb = builder.create_block();

            let parent_vars = variables.clone();
            let parent_types = var_types.clone();

            for (i, arm) in arms.iter().enumerate() {
                let is_last = i == arms.len() - 1;
                let fallthrough_bb = if is_last {
                    default_bb
                } else {
                    builder.create_block()
                };

                let cond = if pattern_is_wildcard(&arm.pattern) {
                    builder.ins().iconst(types::I8, 1)
                } else {
                    compile_pattern_cond(builder, match_val, &arm.pattern, structs)?
                };

                let matched_bb = builder.create_block();
                builder.ins().brif(cond, matched_bb, &[], fallthrough_bb, &[]);
                builder.switch_to_block(matched_bb);
                builder.seal_block(matched_bb);

                let mut local_vars = parent_vars.clone();
                let mut local_types = parent_types.clone();

                bind_match_pattern(
                    builder,
                    &arm.pattern,
                    match_val,
                    &match_expr_ty,
                    structs,
                    var_index,
                    &mut local_vars,
                    &mut local_types,
                );

                if let Some(guard) = &arm.guard {
                    let guard_val = compile_expr_inline(
                        builder,
                        module,
                        alloc_func,
                        arena_push_func,
                        arena_pop_func,
                        functions,
                        structs,
                        fn_sigs,
                        &local_vars,
                        &local_types,
                        var_index,
                        defer_stack,
                        guard,
                    )?;
                    let guard_cond = bool_value_to_i8(builder, guard_val)?;
                    let guarded_body_bb = builder.create_block();
                    builder.ins().brif(guard_cond, guarded_body_bb, &[], fallthrough_bb, &[]);
                    builder.switch_to_block(guarded_body_bb);
                    builder.seal_block(guarded_body_bb);
                }

                let arm_val = match &arm.body {
                    ast::MatchBody::Expr(expr) => compile_expr_inline(
                        builder,
                        module,
                        alloc_func,
                        arena_push_func,
                        arena_pop_func,
                        functions,
                        structs,
                        fn_sigs,
                        &local_vars,
                        &local_types,
                        var_index,
                        defer_stack,
                        expr,
                    )?,
                    ast::MatchBody::Block(block) => {
                        compile_block_value(
                            builder,
                            module,
                            alloc_func,
                            arena_push_func,
                            arena_pop_func,
                            functions,
                            structs,
                            fn_sigs,
                            &local_vars,
                            &local_types,
                            var_index,
                            block,
                            defer_stack,
                            &[], // no break/continue from match arm block expression
                        )?
                        .ok_or_else(|| {
                            anyhow!("match arm block must yield a value in expression context")
                        })?
                    }
                };

                let arm_val = cast_value(builder, arm_val, result_ty);
                builder.ins().jump(merge_bb, &[arm_val]);

                if !is_last {
                    builder.switch_to_block(fallthrough_bb);
                    builder.seal_block(fallthrough_bb);
                }
            }

            builder.switch_to_block(default_bb);
            builder.seal_block(default_bb);
            let default_val = zero_value(builder, result_ty);
            builder.ins().jump(merge_bb, &[default_val]);

            builder.switch_to_block(merge_bb);
            builder.seal_block(merge_bb);
            Ok(builder.block_params(merge_bb)[0])
        }
        ast::Expr::Block(block) => {
            let val = compile_block_value(
                builder,
                module,
                alloc_func,
                arena_push_func,
                arena_pop_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                block,
                defer_stack,
                &[], // no break/continue from block expression
            )?;
            val.ok_or_else(|| anyhow!("block expression must yield a value"))
        }
        ast::Expr::Some(inner) => {
            let inner_ty = infer_expr_type(inner, var_types, structs, fn_sigs);
            let inner_val = compile_expr_inline(
                builder,
                module,
                alloc_func,
                arena_push_func,
                arena_pop_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                inner,
            )?;
            let inner_val = cast_value(builder, inner_val, convert_ast_type(&inner_ty));
            let size_bytes = type_size(&inner_ty, structs) as i64;
            let align = size_bytes.max(1);
            let ptr = emit_alloc(builder, module, alloc_func, size_bytes, align)?;
            if size_bytes > 0 {
                builder.ins().store(MemFlags::new(), inner_val, ptr, 0);
            }
            Ok(ptr)
        }
        ast::Expr::Unit => Ok(builder.ins().iconst(types::I32, 0)),
        ast::Expr::Tuple(elements) => {
            let size_bytes = (elements.len() * 8) as i64;
            let ptr = emit_alloc(builder, module, alloc_func, size_bytes, 8)?;
            for (i, elem) in elements.iter().enumerate() {
                let elem_ty = infer_expr_type(elem, var_types, structs, fn_sigs);
                let val = compile_expr_inline(
                    builder,
                    module,
                    alloc_func,
                    arena_push_func,
                    arena_pop_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    defer_stack,
                    elem,
                )?;
                let val = cast_value(builder, val, convert_ast_type(&elem_ty));
                let offset = (i * 8) as i32;
                builder.ins().store(MemFlags::new(), val, ptr, offset);
            }
            Ok(ptr)
        }
        ast::Expr::None => Ok(builder.ins().iconst(types::I64, 0)),
        ast::Expr::Array(elements) => {
            let elem_ty = infer_array_literal_type(elements, var_types, structs, fn_sigs);
            let elem_size = type_size(&elem_ty, structs) as i64;
            let count = elements.len() as i64;
            let size_bytes = count.saturating_mul(elem_size);
            let ptr = emit_alloc(builder, module, alloc_func, size_bytes, elem_size)?;

            let is_all_zero = elements.iter().all(|e| match e {
                ast::Expr::Literal(ast::Literal::Int(0)) => true,
                ast::Expr::Literal(ast::Literal::Float(f)) => *f == 0.0,
                ast::Expr::Literal(ast::Literal::Bool(false)) => true,
                _ => false,
            });
            if !is_all_zero {
                for (i, elem) in elements.iter().enumerate() {
                    let val = compile_expr_inline(
                        builder,
                        module,
                        alloc_func,
                        arena_push_func,
                        arena_pop_func,
                        functions,
                        structs,
                        fn_sigs,
                        variables,
                        var_types,
                        var_index,
                        defer_stack,
                        elem,
                    )?;
                    let val = cast_value(builder, val, convert_ast_type(&elem_ty));
                    let offset = (i as i32).saturating_mul(elem_size as i32);
                    builder.ins().store(MemFlags::new(), val, ptr, offset);
                }
            }

            Ok(ptr)
        }
        ast::Expr::Struct { name, fields, base, .. } => {
            let Some(layout) = structs.get(name) else {
                return Ok(builder.ins().iconst(types::I64, 0));
            };

            let ptr = emit_alloc(builder, module, alloc_func, layout.size as i64, 8)?;

            if let Some(base_expr) = base {
                let base_ptr = compile_expr_inline(
                    builder,
                    module,
                    alloc_func,
                    arena_push_func,
                    arena_pop_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    defer_stack,
                    base_expr,
                )?;
                for (_fname, offset, field_ty) in &layout.fields {
                    let cr_ty = convert_ast_type(field_ty);
                    let val = builder.ins().load(cr_ty, MemFlags::new(), base_ptr, *offset as i32);
                    builder.ins().store(MemFlags::new(), val, ptr, *offset as i32);
                }
            }

            for (field_name, field_expr) in fields {
                let Some((offset, field_ty)) = layout
                    .fields
                    .iter()
                    .find(|(n, _o, _t)| n == field_name)
                    .map(|(_n, o, t)| (*o, t.clone()))
                else {
                    continue;
                };

                let val = compile_expr_inline(
                    builder,
                    module,
                    alloc_func,
                    arena_push_func,
                    arena_pop_func,
                    functions,
                    structs,
                    fn_sigs,
                    variables,
                    var_types,
                    var_index,
                    defer_stack,
                    field_expr,
                )?;

                let val = cast_value(builder, val, convert_ast_type(&field_ty));
                builder
                    .ins()
                    .store(MemFlags::new(), val, ptr, offset as i32);
            }

            Ok(ptr)
        }
        ast::Expr::Cast { expr, target_type } => {
            let val = compile_expr_inline(
                builder,
                module,
                alloc_func,
                arena_push_func,
                arena_pop_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                expr,
            )?;
            let source_ty = infer_expr_type(expr, var_types, structs, fn_sigs);
            let result = emit_type_cast(builder, val, &source_ty, target_type)?;
            Ok(result)
        }
        ast::Expr::Try(inner) => {
            let inner_ty = infer_expr_type(inner, var_types, structs, fn_sigs);
            let inner_val = compile_expr_inline(
                builder,
                module,
                alloc_func,
                arena_push_func,
                arena_pop_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                inner,
            )?;

            if matches!(inner_ty, ast::Type::Option(_)) {
                let val_ty = match &inner_ty {
                    ast::Type::Option(v) => v.as_ref().clone(),
                    _ => ast::Type::I32,
                };
                let inner_val_i64 = cast_value(builder, inner_val, types::I64);
                let is_none = builder.ins().icmp_imm(IntCC::Equal, inner_val_i64, 0);

                let none_bb = builder.create_block();
                let some_bb = builder.create_block();

                builder.ins().brif(is_none, none_bb, &[], some_bb, &[]);

                builder.switch_to_block(none_bb);
                builder.seal_block(none_bb);
                let mut local_vars = variables.clone();
                let mut local_types = var_types.clone();
                emit_defer_stack(
                    builder,
                    module,
                    alloc_func,
                    arena_push_func,
                    arena_pop_func,
                    functions,
                    structs,
                    fn_sigs,
                    &mut local_vars,
                    &mut local_types,
                    var_index,
                    defer_stack,
                )?;
                let ret_ty = builder.func.signature.returns.first().map(|r| r.value_type);
                if let Some(ret_ty) = ret_ty {
                    let zero = builder.ins().iconst(ret_ty, 0);
                    builder.ins().return_(&[zero]);
                } else {
                    builder.ins().return_(&[]);
                }

                builder.switch_to_block(some_bb);
                builder.seal_block(some_bb);
                let some_cr_ty = convert_ast_type(&val_ty);
                let loaded = builder.ins().load(some_cr_ty, MemFlags::new(), inner_val_i64, 0);
                Ok(loaded)
            } else {
                let ok_ty = match &inner_ty {
                    ast::Type::Result(ok, _) => ok.as_ref().clone(),
                    _ => ast::Type::I32,
                };
                let inner_val_i64 = cast_value(builder, inner_val, types::I64);
                let tag = builder.ins().load(types::I64, MemFlags::new(), inner_val_i64, 0);
                let is_err = builder.ins().icmp_imm(IntCC::NotEqual, tag, 0);

                let err_bb = builder.create_block();
                let ok_bb = builder.create_block();

                builder.ins().brif(is_err, err_bb, &[], ok_bb, &[]);

                builder.switch_to_block(err_bb);
                builder.seal_block(err_bb);
                let mut local_vars = variables.clone();
                let mut local_types = var_types.clone();
                emit_defer_stack(
                    builder,
                    module,
                    alloc_func,
                    arena_push_func,
                    arena_pop_func,
                    functions,
                    structs,
                    fn_sigs,
                    &mut local_vars,
                    &mut local_types,
                    var_index,
                    defer_stack,
                )?;
                let ret_ty = builder.func.signature.returns.first().map(|r| r.value_type);
                if let Some(ret_ty) = ret_ty {
                    let ret_val = cast_value(builder, inner_val_i64, ret_ty);
                    builder.ins().return_(&[ret_val]);
                } else {
                    builder.ins().return_(&[]);
                }

                builder.switch_to_block(ok_bb);
                builder.seal_block(ok_bb);
                let ok_cr_ty = convert_ast_type(&ok_ty);
                let loaded = builder.ins().load(ok_cr_ty, MemFlags::new(), inner_val_i64, 8);
                Ok(loaded)
            }
        }
        ast::Expr::Copy(inner) => {
            // Deep copy: for primitives, return value as-is; for composites, allocate and copy
            let inner_ty = infer_expr_type(inner, var_types, structs, fn_sigs);
            let val = compile_expr_inline(
                builder,
                module,
                alloc_func,
                arena_push_func,
                arena_pop_func,
                functions,
                structs,
                fn_sigs,
                variables,
                var_types,
                var_index,
                defer_stack,
                inner,
            )?;

            match &inner_ty {
                // Primitives: already value types, just return
                ast::Type::I32
                | ast::Type::I64
                | ast::Type::F32
                | ast::Type::F64
                | ast::Type::Bool => Ok(val),
                // Structs: allocate new memory and copy bytes
                ast::Type::Named(name) => {
                    if let Some(layout) = structs.get(name) {
                        let size = layout.size as i64;
                        let new_ptr = emit_alloc(builder, module, alloc_func, size, 8)?;
                        let len_val = builder.ins().iconst(types::I64, size);
                        // Use a unique var_index for the memcpy loop
                        let copy_var_idx = 20000 + (*var_index as usize);
                        *var_index += 1;
                        emit_memcpy_loop(builder, new_ptr, val, len_val, copy_var_idx)?;
                        Ok(new_ptr)
                    } else {
                        Ok(val)
                    }
                }
                // Fixed-size arrays: allocate new memory and copy bytes
                ast::Type::Array(elem_ty, len) => {
                    let elem_size = type_size(elem_ty, structs) as i64;
                    let total_size = elem_size * (*len as i64);
                    if total_size > 0 {
                        let new_ptr =
                            emit_alloc(builder, module, alloc_func, total_size, elem_size.max(8))?;
                        let len_val = builder.ins().iconst(types::I64, total_size);
                        let copy_var_idx = 20000 + (*var_index as usize);
                        *var_index += 1;
                        emit_memcpy_loop(builder, new_ptr, val, len_val, copy_var_idx)?;
                        Ok(new_ptr)
                    } else {
                        Ok(val)
                    }
                }
                // Strings: deep copy (length + data)
                ast::Type::Str => {
                    // String layout: [length: i64][data: bytes...]
                    let len = get_string_len(builder, val);
                    let total_size = builder.ins().iadd_imm(len, 8); // 8 bytes for length header
                    let func_ref = module.declare_func_in_func(alloc_func, builder.func);
                    let align = builder.ins().iconst(types::I64, 8);
                    let call = builder.ins().call(func_ref, &[total_size, align]);
                    let new_ptr = builder.inst_results(call)[0];
                    // Copy length
                    builder.ins().store(MemFlags::new(), len, new_ptr, 0);
                    // Copy data bytes
                    let src_data = get_string_data(builder, val);
                    let dest_data = builder.ins().iadd_imm(new_ptr, 8);
                    let copy_var_idx = 20000 + (*var_index as usize);
                    *var_index += 1;
                    emit_memcpy_loop(builder, dest_data, src_data, len, copy_var_idx)?;
                    Ok(new_ptr)
                }
                // Option<T>: for now treat as value (tagged union representation)
                ast::Type::Option(_) => Ok(val),
                // Other types: return as-is
                _ => Ok(val),
            }
        }
        _ => Ok(builder.ins().iconst(types::I32, 0)),
    }
}

/// Emit code for type casting between numeric types
fn emit_type_cast(
    builder: &mut FunctionBuilder,
    val: Value,
    source_type: &ast::Type,
    target_type: &ast::Type,
) -> Result<Value> {
    use ast::Type;

    match (source_type, target_type) {
        // Same type - no conversion needed
        (a, b) if a == b => Ok(val),

        // Integer to larger integer (sign extend)
        (Type::I32, Type::I64) => Ok(builder.ins().sextend(types::I64, val)),

        // Integer to smaller integer (truncate)
        (Type::I64, Type::I32) => Ok(builder.ins().ireduce(types::I32, val)),

        // Integer to float
        (Type::I32 | Type::I64, Type::F64) => {
            // First convert to i64 if needed, then to f64
            let i64_val = if matches!(source_type, Type::I32) {
                builder.ins().sextend(types::I64, val)
            } else {
                val
            };
            Ok(builder.ins().fcvt_from_sint(types::F64, i64_val))
        }

        // Float to integer (truncate toward zero)
        (Type::F64, Type::I32) => {
            let i64_val = builder.ins().fcvt_to_sint(types::I64, val);
            Ok(builder.ins().ireduce(types::I32, i64_val))
        }
        (Type::F64, Type::I64) => Ok(builder.ins().fcvt_to_sint(types::I64, val)),

        // Bool to integer (zero extend)
        (Type::Bool, Type::I32 | Type::I64) => {
            if matches!(target_type, Type::I64) {
                Ok(builder.ins().uextend(types::I64, val))
            } else {
                Ok(builder.ins().uextend(types::I32, val))
            }
        }

        // Integer to bool (non-zero check)
        (Type::I32 | Type::I64, Type::Bool) => {
            let zero = if matches!(source_type, Type::I64) {
                builder.ins().iconst(types::I64, 0)
            } else {
                builder.ins().iconst(types::I32, 0)
            };
            let is_nonzero = builder.ins().icmp(IntCC::NotEqual, val, zero);
            Ok(is_nonzero)
        }

        // Fallback: use existing cast_value function behavior
        _ => Ok(cast_value(builder, val, convert_ast_type(target_type))),
    }
}

fn compile_literal_inline(builder: &mut FunctionBuilder, lit: &ast::Literal) -> Result<Value> {
    match lit {
        ast::Literal::Int(n) => {
            if i32::try_from(*n).is_ok() {
                Ok(builder.ins().iconst(types::I32, *n))
            } else {
                Ok(builder.ins().iconst(types::I64, *n))
            }
        }
        ast::Literal::Float(f) => Ok(builder.ins().f64const(*f)),
        ast::Literal::Bool(b) => Ok(builder.ins().iconst(types::I8, if *b { 1 } else { 0 })),
        ast::Literal::Char(c) => Ok(builder.ins().iconst(types::I32, *c as i64)),
        _ => Ok(builder.ins().iconst(types::I32, 0)),
    }
}

/// Compile a string literal - allocates memory and stores (ptr, len) as a 128-bit value
/// String representation: pointer to allocated memory containing the string bytes
/// We use a simple approach: allocate len+1 bytes and null-terminate
fn compile_string_literal(
    builder: &mut FunctionBuilder,
    module: &mut JITModule,
    alloc_func: FuncId,
    s: &str,
) -> Result<Value> {
    let len = s.len() as i64;
    // Allocate len + 8 bytes: 8 bytes for length prefix, then the string data
    // Layout: [len: i64][string bytes...]
    let size = len + 8;
    let ptr = emit_alloc(builder, module, alloc_func, size, 8)?;

    // Store the length at the beginning
    let len_val = builder.ins().iconst(types::I64, len);
    builder.ins().store(MemFlags::new(), len_val, ptr, 0);

    // Store each byte of the string
    for (i, byte) in s.bytes().enumerate() {
        let byte_val = builder.ins().iconst(types::I8, byte as i64);
        builder
            .ins()
            .store(MemFlags::new(), byte_val, ptr, (8 + i) as i32);
    }

    // Return the pointer (which points to the length-prefixed string)
    Ok(ptr)
}

/// Get the length of a string (stored at offset 0)
fn get_string_len(builder: &mut FunctionBuilder, str_ptr: Value) -> Value {
    builder.ins().load(types::I64, MemFlags::new(), str_ptr, 0)
}

/// Get the data pointer of a string (at offset 8)
fn get_string_data(builder: &mut FunctionBuilder, str_ptr: Value) -> Value {
    builder.ins().iadd_imm(str_ptr, 8)
}

/// Concatenate two strings - allocates new memory for the result
fn emit_string_concat(
    builder: &mut FunctionBuilder,
    module: &mut JITModule,
    alloc_func: FuncId,
    left: Value,
    right: Value,
    var_index: &mut u32,
) -> Result<Value> {
    // Get lengths
    let len1 = get_string_len(builder, left);
    let len2 = get_string_len(builder, right);

    // Calculate total length
    let total_len = builder.ins().iadd(len1, len2);

    // Allocate new buffer: 8 bytes for length + total string bytes
    let size = builder.ins().iadd_imm(total_len, 8);

    let func_ref = module.declare_func_in_func(alloc_func, builder.func);
    let align = builder.ins().iconst(types::I64, 8);
    let call = builder.ins().call(func_ref, &[size, align]);
    let result_ptr = builder.inst_results(call)[0];

    // Store the new length
    builder
        .ins()
        .store(MemFlags::new(), total_len, result_ptr, 0);

    // Copy first string bytes using a loop
    // For simplicity, we'll use individual byte copies (can be optimized later)
    let data1 = get_string_data(builder, left);
    let result_data = builder.ins().iadd_imm(result_ptr, 8);

    // We need to emit a byte copy loop for the first string
    // For now, use Cranelift's memcpy intrinsic if available, or manual copy
    // Since Cranelift doesn't have a direct memcpy, we'll call a runtime function
    // or copy byte-by-byte in a loop.

    // Simple approach: use call to external memcpy (requires linking to libc)
    // For now, let's do a simpler approach: inline byte copy using loops
    // But loops in code generation are complex. Let's use a helper.

    // Alternative: Store values directly for small strings (for testing)
    // For a proper implementation, we'd need to emit a copy loop or call memcpy

    // For now, let's implement a simplified version that copies byte-by-byte
    // using a loop-like structure with basic blocks
    // Use unique variable indices for each memcpy call (with 20000 offset to avoid collisions)
    let copy_var_idx1 = 20000 + (*var_index as usize);
    *var_index += 1;
    emit_memcpy_loop(builder, result_data, data1, len1, copy_var_idx1)?;

    // Copy second string after the first
    let dest2 = builder.ins().iadd(result_data, len1);
    let data2 = get_string_data(builder, right);
    let copy_var_idx2 = 20000 + (*var_index as usize);
    *var_index += 1;
    emit_memcpy_loop(builder, dest2, data2, len2, copy_var_idx2)?;

    Ok(result_ptr)
}

/// Emit a byte-copy loop from src to dest for len bytes
fn emit_memcpy_loop(
    builder: &mut FunctionBuilder,
    dest: Value,
    src: Value,
    len: Value,
    var_idx: usize,
) -> Result<()> {
    // Create loop structure
    let loop_header = builder.create_block();
    let loop_body = builder.create_block();
    let loop_exit = builder.create_block();

    // Initialize loop counter with unique variable index
    let idx_var = Variable::new(var_idx);
    builder.declare_var(idx_var, types::I64);
    let zero = builder.ins().iconst(types::I64, 0);
    builder.def_var(idx_var, zero);

    builder.ins().jump(loop_header, &[]);

    // Loop header: check if idx < len
    builder.switch_to_block(loop_header);
    let idx = builder.use_var(idx_var);
    let cond = builder.ins().icmp(IntCC::UnsignedLessThan, idx, len);
    builder.ins().brif(cond, loop_body, &[], loop_exit, &[]);

    // Loop body: copy one byte
    builder.switch_to_block(loop_body);
    let idx = builder.use_var(idx_var);
    let src_addr = builder.ins().iadd(src, idx);
    let byte_val = builder.ins().load(types::I8, MemFlags::new(), src_addr, 0);
    let dest_addr = builder.ins().iadd(dest, idx);
    builder.ins().store(MemFlags::new(), byte_val, dest_addr, 0);

    // Increment counter
    let next_idx = builder.ins().iadd_imm(idx, 1);
    builder.def_var(idx_var, next_idx);
    builder.ins().jump(loop_header, &[]);

    // Exit block
    builder.switch_to_block(loop_exit);

    Ok(())
}

fn cast_value(builder: &mut FunctionBuilder, val: Value, target: types::Type) -> Value {
    let src = builder.func.dfg.value_type(val);
    if src == target {
        return val;
    }
    match (src, target) {
        (types::I8, types::I32) => builder.ins().sextend(types::I32, val),
        (types::I8, types::I64) => builder.ins().sextend(types::I64, val),
        (types::I32, types::I8) => builder.ins().ireduce(types::I8, val),
        (types::I64, types::I8) => builder.ins().ireduce(types::I8, val),
        (types::I32, types::I64) => builder.ins().sextend(types::I64, val),
        (types::I64, types::I32) => builder.ins().ireduce(types::I32, val),
        (types::F32, types::F64) => builder.ins().fpromote(types::F64, val),
        (types::F64, types::F32) => builder.ins().fdemote(types::F32, val),
        (types::I32, types::F32) | (types::I64, types::F32) => {
            builder.ins().fcvt_from_sint(types::F32, val)
        }
        (types::I32, types::F64) | (types::I64, types::F64) => {
            builder.ins().fcvt_from_sint(types::F64, val)
        }
        (types::F32, types::I32) | (types::F64, types::I32) => {
            builder.ins().fcvt_to_sint(types::I32, val)
        }
        (types::F32, types::I64) | (types::F64, types::I64) => {
            builder.ins().fcvt_to_sint(types::I64, val)
        }
        _ => val,
    }
}

fn bool_value_to_i8(builder: &mut FunctionBuilder, val: Value) -> Result<Value> {
    match builder.func.dfg.value_type(val) {
        types::I8 => Ok(val),
        types::I32 | types::I64 => Ok(builder.ins().icmp_imm(IntCC::NotEqual, val, 0)),
        other => Err(anyhow!("Expected bool condition (I8), got {:?}", other)),
    }
}

fn is_float_type(ty: types::Type) -> bool {
    matches!(ty, types::F32 | types::F64)
}

fn is_numeric_type(ty: types::Type) -> bool {
    matches!(ty, types::I32 | types::I64 | types::F32 | types::F64)
}

fn common_numeric_type(lhs_ty: types::Type, rhs_ty: types::Type) -> Option<types::Type> {
    if !is_numeric_type(lhs_ty) || !is_numeric_type(rhs_ty) {
        return None;
    }
    Some(if lhs_ty == types::F64 || rhs_ty == types::F64 {
        types::F64
    } else if lhs_ty == types::F32 || rhs_ty == types::F32 {
        types::F32
    } else if lhs_ty == types::I64 || rhs_ty == types::I64 {
        types::I64
    } else {
        types::I32
    })
}

fn infer_expr_type(
    expr: &ast::Expr,
    var_types: &HashMap<String, ast::Type>,
    structs: &HashMap<String, StructLayout>,
    fn_sigs: &HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
) -> ast::Type {
    match expr {
        ast::Expr::Literal(lit) => match lit {
            ast::Literal::Int(_) => ast::Type::I32,
            ast::Literal::Float(_) => ast::Type::F64,
            ast::Literal::Bool(_) => ast::Type::Bool,
            ast::Literal::Char(_) => ast::Type::I32,
            ast::Literal::String(_) => ast::Type::Str,
            ast::Literal::HexColor(_) => ast::Type::I32,
        },
        ast::Expr::Ident(name) => {
            if let Some(ty) = var_types.get(name) {
                ty.clone()
            } else if let Some((params, ret)) = fn_sigs.get(name) {
                ast::Type::Fn(params.clone(), Box::new(ret.clone().unwrap_or(ast::Type::I32)))
            } else {
                ast::Type::I32
            }
        },
        ast::Expr::Unary { op, expr } => {
            let inner = infer_expr_type(expr, var_types, structs, fn_sigs);
            match op {
                ast::UnaryOp::Neg => inner,
                ast::UnaryOp::Not => ast::Type::Bool,
            }
        }
        ast::Expr::Binary { op, left, right } => {
            let left_ty = infer_expr_type(left, var_types, structs, fn_sigs);
            let right_ty = infer_expr_type(right, var_types, structs, fn_sigs);
            match op {
                ast::BinaryOp::Add => {
                    // String concatenation
                    if matches!(left_ty, ast::Type::Str) && matches!(right_ty, ast::Type::Str) {
                        ast::Type::Str
                    } else {
                        merge_numeric_types(&left_ty, &right_ty)
                    }
                }
                ast::BinaryOp::Sub
                | ast::BinaryOp::Mul
                | ast::BinaryOp::Div
                | ast::BinaryOp::Mod => merge_numeric_types(&left_ty, &right_ty),
                ast::BinaryOp::Eq
                | ast::BinaryOp::Ne
                | ast::BinaryOp::Lt
                | ast::BinaryOp::Le
                | ast::BinaryOp::Gt
                | ast::BinaryOp::Ge
                | ast::BinaryOp::And
                | ast::BinaryOp::Or => ast::Type::Bool,
                ast::BinaryOp::BitAnd
                | ast::BinaryOp::BitOr
                | ast::BinaryOp::BitXor
                | ast::BinaryOp::Shl
                | ast::BinaryOp::Shr => {
                    // Bitwise operators return the wider integer type
                    if matches!(left_ty, ast::Type::I64) || matches!(right_ty, ast::Type::I64) {
                        ast::Type::I64
                    } else {
                        ast::Type::I32
                    }
                }
                ast::BinaryOp::As => left_ty,
            }
        }
        ast::Expr::Call { func, .. } => {
            if let ast::Expr::Ident(name) = func.as_ref() {
                if structs.contains_key(name) {
                    return ast::Type::Named(name.clone());
                }
                if let Some(ty) = var_types.get(name) {
                    if let ast::Type::Fn(_, ret) = ty {
                        return (**ret).clone();
                    }
                }
                let arg_types = if let ast::Expr::Call { args, .. } = expr {
                    args.iter()
                        .map(|arg| infer_expr_type(arg, var_types, structs, fn_sigs))
                        .collect::<Vec<_>>()
                } else {
                    Vec::new()
                };
                if let Some(ty) = builtins::infer_special_builtin_call_type(name, &arg_types, None)
                {
                    return ty;
                }
                if let Some((_, ret)) = fn_sigs.get(name) {
                    return ret.clone().unwrap_or(ast::Type::I32);
                }
            } else if let ast::Expr::Field { expr: recv, field } = func.as_ref() {
                let base_ty = infer_expr_type(recv, var_types, structs, fn_sigs);
                if let ast::Type::Named(struct_name) = &base_ty {
                    let method_name = format!("{}::{}", struct_name, field);
                    if let Some((_, ret)) = fn_sigs.get(&method_name) {
                        return ret.clone().unwrap_or(ast::Type::I32);
                    }
                }
            } else {
                let func_ty = infer_expr_type(func, var_types, structs, fn_sigs);
                if let ast::Type::Fn(_, ret) = func_ty {
                    return (*ret).clone();
                }
            }
            ast::Type::I32
        }
        ast::Expr::Index { expr, index } => {
            if matches!(index.as_ref(), ast::Expr::Range { .. }) {
                let expr_ty = infer_expr_type(expr, var_types, structs, fn_sigs);
                match expr_ty {
                    ast::Type::Array(elem, _) | ast::Type::Slice(elem) | ast::Type::Vec(elem) => {
                        return ast::Type::Slice(elem);
                    }
                    _ => return ast::Type::Slice(Box::new(ast::Type::I64)),
                }
            }
            if let Some(elem) = infer_array_elem_type(expr, var_types, structs, fn_sigs) {
                elem
            } else {
                ast::Type::I32
            }
        }
        ast::Expr::Field { expr, field } => {
            if let Some((_offset, ty)) = resolve_field(structs, expr, field, var_types) {
                ty
            } else {
                ast::Type::I32
            }
        }
        ast::Expr::Array(elements) => {
            let elem_ty = infer_array_literal_type(elements, var_types, structs, fn_sigs);
            ast::Type::Array(Box::new(elem_ty), elements.len())
        }
        ast::Expr::Struct { name, .. } => ast::Type::Named(name.clone()),
        ast::Expr::If {
            then_expr,
            else_expr,
            ..
        } => {
            let then_is_none = matches!(then_expr.as_ref(), ast::Expr::None)
                || matches!(
                    then_expr.as_ref(),
                    ast::Expr::Block(block)
                        if infer_block_value_type(block, var_types, structs, fn_sigs).is_none()
                );
            let else_is_none = matches!(else_expr.as_ref(), ast::Expr::None)
                || matches!(
                    else_expr.as_ref(),
                    ast::Expr::Block(block)
                        if infer_block_value_type(block, var_types, structs, fn_sigs).is_none()
                );
            if then_is_none && !else_is_none {
                return infer_expr_type(else_expr, var_types, structs, fn_sigs);
            }
            if else_is_none && !then_is_none {
                return infer_expr_type(then_expr, var_types, structs, fn_sigs);
            }
            let then_ty = infer_expr_type(then_expr, var_types, structs, fn_sigs);
            let else_ty = infer_expr_type(else_expr, var_types, structs, fn_sigs);
            if types_compatible_ast(&then_ty, &else_ty) {
                merge_types(&then_ty, &else_ty)
            } else {
                then_ty
            }
        }
        ast::Expr::Match { arms, .. } => infer_match_expr_type(arms, var_types, structs, fn_sigs),
        ast::Expr::Block(block) => {
            infer_block_value_type(block, var_types, structs, fn_sigs).unwrap_or(ast::Type::I32)
        }
        ast::Expr::Some(inner) => {
            let inner_ty = infer_expr_type(inner, var_types, structs, fn_sigs);
            ast::Type::Option(Box::new(inner_ty))
        }
        ast::Expr::None => ast::Type::Option(Box::new(ast::Type::I32)),
        ast::Expr::Copy(expr) => infer_expr_type(expr, var_types, structs, fn_sigs),
        ast::Expr::Try(inner) => {
            match infer_expr_type(inner, var_types, structs, fn_sigs) {
                ast::Type::Result(ok_ty, _) => *ok_ty,
                ast::Type::Option(val_ty) => *val_ty,
                _ => ast::Type::I32,
            }
        }
        ast::Expr::Tuple(elements) => {
            let elem_tys = elements
                .iter()
                .map(|e| infer_expr_type(e, var_types, structs, fn_sigs))
                .collect();
            ast::Type::Tuple(elem_tys)
        }
        ast::Expr::Unit => ast::Type::Unit,
        ast::Expr::Cast { target_type, .. } => target_type.clone(),
        _ => ast::Type::I32,
    }
}

fn infer_array_elem_type(
    expr: &ast::Expr,
    var_types: &HashMap<String, ast::Type>,
    structs: &HashMap<String, StructLayout>,
    fn_sigs: &HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
) -> Option<ast::Type> {
    match infer_expr_type(expr, var_types, structs, fn_sigs) {
        ast::Type::Array(elem, _) | ast::Type::Slice(elem) | ast::Type::Vec(elem) => Some(*elem),
        _ => None,
    }
}

fn infer_array_len(
    expr: &ast::Expr,
    var_types: &HashMap<String, ast::Type>,
    structs: &HashMap<String, StructLayout>,
    fn_sigs: &HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
) -> Option<usize> {
    match infer_expr_type(expr, var_types, structs, fn_sigs) {
        ast::Type::Array(_, len) => Some(len),
        _ => None,
    }
}

fn infer_array_literal_type(
    elements: &[ast::Expr],
    var_types: &HashMap<String, ast::Type>,
    structs: &HashMap<String, StructLayout>,
    fn_sigs: &HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
) -> ast::Type {
    if elements.is_empty() {
        return ast::Type::I32;
    }
    let mut current = infer_expr_type(&elements[0], var_types, structs, fn_sigs);
    for elem in elements.iter().skip(1) {
        let next = infer_expr_type(elem, var_types, structs, fn_sigs);
        current = merge_numeric_types(&current, &next);
    }
    current
}

fn infer_block_value_type(
    block: &ast::Block,
    var_types: &HashMap<String, ast::Type>,
    structs: &HashMap<String, StructLayout>,
    fn_sigs: &HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
) -> Option<ast::Type> {
    let mut env = var_types.clone();
    let mut last = None;
    for stmt in &block.statements {
        match stmt {
            ast::Stmt::Let { name, ty, value, .. } => {
                let inferred = ty
                    .clone()
                    .unwrap_or_else(|| infer_expr_type(value, &env, structs, fn_sigs));
                env.insert(name.clone(), inferred);
            }
            ast::Stmt::Expr(expr) => {
                if matches!(expr, ast::Expr::None) {
                    last = None;
                } else {
                    last = Some(infer_expr_type(expr, &env, structs, fn_sigs));
                }
            }
            _ => {}
        }
    }
    last
}

fn infer_match_expr_type(
    arms: &[ast::MatchArm],
    var_types: &HashMap<String, ast::Type>,
    structs: &HashMap<String, StructLayout>,
    fn_sigs: &HashMap<String, (Vec<ast::Type>, Option<ast::Type>)>,
) -> ast::Type {
    let mut result = None;
    let mut saw_none = false;
    for arm in arms {
        let arm_ty = match &arm.body {
            ast::MatchBody::Expr(expr) => {
                if matches!(expr, ast::Expr::None) {
                    saw_none = true;
                    None
                } else {
                    Some(infer_expr_type(expr, var_types, structs, fn_sigs))
                }
            }
            ast::MatchBody::Block(block) => {
                let inferred = infer_block_value_type(block, var_types, structs, fn_sigs);
                if inferred.is_none() {
                    saw_none = true;
                }
                inferred
            }
        };

        if let Some(arm_ty) = arm_ty {
            result = match result {
                None => Some(arm_ty),
                Some(existing) => Some(merge_types(&existing, &arm_ty)),
            };
        }
    }

    if saw_none {
        match result.as_ref() {
            Some(ast::Type::Option(_)) => {}
            None => return ast::Type::Option(Box::new(ast::Type::I32)),
            _ => {}
        }
    }

    result.unwrap_or(ast::Type::I32)
}

fn merge_numeric_types(left: &ast::Type, right: &ast::Type) -> ast::Type {
    use ast::Type::*;
    match (left, right) {
        (F64, _) | (_, F64) => F64,
        (F32, _) | (_, F32) => F32,
        (I64, _) | (_, I64) => I64,
        (I32, _) | (_, I32) => I32,
        (Bool, Bool) => Bool,
        _ => I32,
    }
}

fn merge_types(left: &ast::Type, right: &ast::Type) -> ast::Type {
    use ast::Type::*;

    if left == right {
        return left.clone();
    }
    if let (Option(a), Option(b)) = (left, right) {
        return Option(Box::new(merge_types(a, b)));
    }
    if let (Vec(a), Vec(b)) = (left, right) {
        return Vec(Box::new(merge_types(a, b)));
    }
    if let (HashMap(key_a, value_a), HashMap(key_b, value_b)) = (left, right) {
        return HashMap(
            Box::new(merge_types(key_a, key_b)),
            Box::new(merge_types(value_a, value_b)),
        );
    }
    if let (Result(ok_a, err_a), Result(ok_b, err_b)) = (left, right) {
        return Result(
            Box::new(merge_types(ok_a, ok_b)),
            Box::new(merge_types(err_a, err_b)),
        );
    }
    if let (Array(a, len_a), Array(b, len_b)) = (left, right) {
        if len_a == len_b {
            return Array(Box::new(merge_types(a, b)), *len_a);
        }
    }
    if matches!(left, I32 | I64 | F32 | F64) && matches!(right, I32 | I64 | F32 | F64) {
        return merge_numeric_types(left, right);
    }
    if matches!(left, Bool) && matches!(right, Bool) {
        return Bool;
    }
    if matches!(left, Str) && matches!(right, Str) {
        return Str;
    }
    if let (Named(a), Named(b)) = (left, right) {
        if a == b {
            return Named(a.clone());
        }
    }
    left.clone()
}

fn types_compatible_ast(expected: &ast::Type, actual: &ast::Type) -> bool {
    if expected == actual {
        return true;
    }
    if matches!(
        expected,
        ast::Type::I32 | ast::Type::I64 | ast::Type::F32 | ast::Type::F64
    ) && matches!(
        actual,
        ast::Type::I32 | ast::Type::I64 | ast::Type::F32 | ast::Type::F64
    ) {
        return true;
    }
    match (expected, actual) {
        (ast::Type::Option(e1), ast::Type::Option(e2)) => types_compatible_ast(e1, e2),
        (ast::Type::Vec(e1), ast::Type::Vec(e2)) => types_compatible_ast(e1, e2),
        (ast::Type::HashMap(key1, value1), ast::Type::HashMap(key2, value2)) => {
            types_compatible_ast(key1, key2) && types_compatible_ast(value1, value2)
        }
        (ast::Type::Result(ok1, err1), ast::Type::Result(ok2, err2)) => {
            types_compatible_ast(ok1, ok2) && types_compatible_ast(err1, err2)
        }
        (ast::Type::Array(e1, _), ast::Type::Array(e2, _)) => types_compatible_ast(e1, e2),
        (ast::Type::Slice(e1), ast::Type::Slice(e2)) => types_compatible_ast(e1, e2),
        (ast::Type::Slice(e1), ast::Type::Array(e2, _)) => types_compatible_ast(e1, e2),
        (ast::Type::Slice(e1), ast::Type::Vec(e2)) => types_compatible_ast(e1, e2),
        _ => false,
    }
}

fn resolve_field(
    structs: &HashMap<String, StructLayout>,
    expr: &ast::Expr,
    field: &str,
    var_types: &HashMap<String, ast::Type>,
) -> Option<(u32, ast::Type)> {
    let base_ty = match expr {
        ast::Expr::Ident(name) => var_types.get(name).cloned(),
        ast::Expr::Field { expr, field } => {
            resolve_field(structs, expr, field, var_types).map(|(_, ty)| ty)
        }
        _ => Some(infer_expr_type(expr, var_types, structs, &HashMap::new())),
    };

    if let Some(ast::Type::Tuple(elem_types)) = &base_ty {
        if let Ok(idx) = field.parse::<usize>() {
            if let Some(ty) = elem_types.get(idx) {
                return Some(((idx * 8) as u32, ty.clone()));
            }
        }
    }

    if let Some(ast::Type::Named(struct_name)) = base_ty {
        if let Some(layout) = structs.get(&struct_name) {
            for (name, offset, ty) in &layout.fields {
                if name == field {
                    return Some((*offset, ty.clone()));
                }
            }
        }
    }

    for layout in structs.values() {
        for (name, offset, ty) in &layout.fields {
            if name == field {
                return Some((*offset, ty.clone()));
            }
        }
    }

    None
}

fn declare_panic_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_panic", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_panic: {}", e))
}

fn declare_assert_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I8));
    sig.params.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_assert", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_assert: {}", e))
}

fn declare_alloc_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // size
    sig.params.push(AbiParam::new(types::I64)); // align
    sig.returns.push(AbiParam::new(types::I64)); // ptr

    module
        .declare_function("bunker_alloc", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_alloc: {}", e))
}

fn declare_arena_push_func(module: &mut JITModule) -> Result<FuncId> {
    let sig = module.make_signature(); // void -> void (no params, no return)

    module
        .declare_function("bunker_arena_push", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_arena_push: {}", e))
}

fn declare_arena_pop_func(module: &mut JITModule) -> Result<FuncId> {
    let sig = module.make_signature(); // void -> void (no params, no return)

    module
        .declare_function("bunker_arena_pop", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_arena_pop: {}", e))
}

fn declare_read_file_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // path_ptr
    sig.returns.push(AbiParam::new(types::I64)); // content_ptr (0 on error)

    module
        .declare_function("bunker_read_file", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_read_file: {}", e))
}

fn declare_write_file_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // path_ptr
    sig.params.push(AbiParam::new(types::I64)); // content_ptr
    sig.returns.push(AbiParam::new(types::I64)); // success (1) or failure (0)

    module
        .declare_function("bunker_write_file", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_write_file: {}", e))
}

fn declare_file_exists_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // path_ptr
    sig.returns.push(AbiParam::new(types::I64)); // exists (1) or not (0)

    module
        .declare_function("bunker_file_exists", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_file_exists: {}", e))
}

fn declare_args_count_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_args_count", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_args_count: {}", e))
}

fn declare_arg_at_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_arg_at", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_arg_at: {}", e))
}

// ============================================================================
// String Operation Function Declarations
// ============================================================================

fn declare_char_at_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // str_ptr
    sig.params.push(AbiParam::new(types::I64)); // index
    sig.returns.push(AbiParam::new(types::I64)); // single char string ptr (or 0 on error)

    module
        .declare_function("bunker_char_at", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_char_at: {}", e))
}

fn declare_substring_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // str_ptr
    sig.params.push(AbiParam::new(types::I64)); // start index
    sig.params.push(AbiParam::new(types::I64)); // end index
    sig.returns.push(AbiParam::new(types::I64)); // substring ptr

    module
        .declare_function("bunker_substring", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_substring: {}", e))
}

fn declare_contains_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // str_ptr
    sig.params.push(AbiParam::new(types::I64)); // substr_ptr
    sig.returns.push(AbiParam::new(types::I64)); // 1 if contains, 0 otherwise

    module
        .declare_function("bunker_contains", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_contains: {}", e))
}

fn declare_starts_with_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // str_ptr
    sig.params.push(AbiParam::new(types::I64)); // prefix_ptr
    sig.returns.push(AbiParam::new(types::I64)); // 1 if starts with, 0 otherwise

    module
        .declare_function("bunker_starts_with", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_starts_with: {}", e))
}

fn declare_ends_with_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // str_ptr
    sig.params.push(AbiParam::new(types::I64)); // suffix_ptr
    sig.returns.push(AbiParam::new(types::I64)); // 1 if ends with, 0 otherwise

    module
        .declare_function("bunker_ends_with", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_ends_with: {}", e))
}

fn declare_trim_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // str_ptr
    sig.returns.push(AbiParam::new(types::I64)); // trimmed string ptr

    module
        .declare_function("bunker_trim", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_trim: {}", e))
}

fn declare_parse_int_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // str_ptr
    sig.returns.push(AbiParam::new(types::I64)); // parsed integer (or 0 on error)

    module
        .declare_function("bunker_parse_int", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_parse_int: {}", e))
}

fn declare_int_to_string_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // integer value
    sig.returns.push(AbiParam::new(types::I64)); // string ptr

    module
        .declare_function("bunker_int_to_string", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_int_to_string: {}", e))
}

fn declare_char_code_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // string ptr
    sig.returns.push(AbiParam::new(types::I64)); // char code

    module
        .declare_function("bunker_char_code", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_char_code: {}", e))
}

fn declare_char_code_at_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // string ptr
    sig.params.push(AbiParam::new(types::I64)); // index
    sig.returns.push(AbiParam::new(types::I64)); // char code

    module
        .declare_function("bunker_char_code_at", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_char_code_at: {}", e))
}

fn declare_from_char_code_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // char code
    sig.returns.push(AbiParam::new(types::I64)); // string ptr

    module
        .declare_function("bunker_from_char_code", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_from_char_code: {}", e))
}

fn declare_str_eq_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // string ptr a
    sig.params.push(AbiParam::new(types::I64)); // string ptr b
    sig.returns.push(AbiParam::new(types::I64)); // 1 if equal, 0 otherwise

    module
        .declare_function("bunker_str_eq", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_str_eq: {}", e))
}

fn declare_join_lines_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // Vec<str> handle
    sig.returns.push(AbiParam::new(types::I64)); // joined string ptr

    module
        .declare_function("bunker_join_lines", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_join_lines: {}", e))
}

// ============================================================================
// Vec<T> Function Declarations
// ============================================================================

fn declare_vec_new_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.returns.push(AbiParam::new(types::I64)); // vec ptr

    module
        .declare_function("bunker_vec_new", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_vec_new: {}", e))
}

fn declare_vec_push_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // vec ptr
    sig.params.push(AbiParam::new(types::I64)); // value
    sig.returns.push(AbiParam::new(types::I64)); // new length

    module
        .declare_function("bunker_vec_push", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_vec_push: {}", e))
}

fn declare_vec_pop_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // vec ptr
    sig.returns.push(AbiParam::new(types::I64)); // popped value

    module
        .declare_function("bunker_vec_pop", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_vec_pop: {}", e))
}

fn declare_vec_len_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // vec ptr
    sig.returns.push(AbiParam::new(types::I64)); // length

    module
        .declare_function("bunker_vec_len", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_vec_len: {}", e))
}

fn declare_vec_capacity_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // vec ptr
    sig.returns.push(AbiParam::new(types::I64)); // capacity

    module
        .declare_function("bunker_vec_capacity", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_vec_capacity: {}", e))
}

fn declare_vec_get_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // vec ptr
    sig.params.push(AbiParam::new(types::I64)); // index
    sig.returns.push(AbiParam::new(types::I64)); // value

    module
        .declare_function("bunker_vec_get", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_vec_get: {}", e))
}

fn declare_vec_set_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // vec ptr
    sig.params.push(AbiParam::new(types::I64)); // index
    sig.params.push(AbiParam::new(types::I64)); // value
    sig.returns.push(AbiParam::new(types::I64)); // success (1) or failure (0)

    module
        .declare_function("bunker_vec_set", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_vec_set: {}", e))
}

fn declare_vec_clear_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // vec ptr

    module
        .declare_function("bunker_vec_clear", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_vec_clear: {}", e))
}

fn declare_vec_contains_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // vec ptr
    sig.params.push(AbiParam::new(types::I64)); // item
    sig.returns.push(AbiParam::new(types::I64)); // 1 if found, 0 if not

    module
        .declare_function("bunker_vec_contains", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_vec_contains: {}", e))
}

fn declare_vec_contains_str_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // vec ptr
    sig.params.push(AbiParam::new(types::I64)); // item str ptr
    sig.returns.push(AbiParam::new(types::I64)); // 1 if found, 0 if not

    module
        .declare_function("bunker_vec_contains_str", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_vec_contains_str: {}", e))
}

fn declare_vec_is_empty_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // vec ptr
    sig.returns.push(AbiParam::new(types::I64)); // 1 if empty, 0 if not

    module
        .declare_function("bunker_vec_is_empty", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_vec_is_empty: {}", e))
}

fn declare_vec_clone_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // vec ptr
    sig.returns.push(AbiParam::new(types::I64)); // new vec ptr

    module
        .declare_function("bunker_vec_clone", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_vec_clone: {}", e))
}

fn declare_vec_reverse_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // vec ptr
    sig.returns.push(AbiParam::new(types::I64)); // 1 on success, 0 on null

    module
        .declare_function("bunker_vec_reverse", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_vec_reverse: {}", e))
}

fn declare_vec_map_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // vec ptr
    sig.params.push(AbiParam::new(types::I64)); // fn ptr
    sig.returns.push(AbiParam::new(types::I64)); // new vec ptr

    module
        .declare_function("bunker_vec_map", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_vec_map: {}", e))
}

fn declare_vec_filter_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // vec ptr
    sig.params.push(AbiParam::new(types::I64)); // fn ptr
    sig.returns.push(AbiParam::new(types::I64)); // new vec ptr

    module
        .declare_function("bunker_vec_filter", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_vec_filter: {}", e))
}

fn declare_vec_fold_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // vec ptr
    sig.params.push(AbiParam::new(types::I64)); // init val
    sig.params.push(AbiParam::new(types::I64)); // fn ptr
    sig.returns.push(AbiParam::new(types::I64)); // accumulated val

    module
        .declare_function("bunker_vec_fold", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_vec_fold: {}", e))
}

fn declare_vec_find_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // vec ptr
    sig.params.push(AbiParam::new(types::I64)); // fn ptr
    sig.returns.push(AbiParam::new(types::I64)); // Option<T> box ptr or 0

    module
        .declare_function("bunker_vec_find", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_vec_find: {}", e))
}

fn declare_hashmap_is_empty_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // map ptr
    sig.returns.push(AbiParam::new(types::I64)); // 1 if empty, 0 if not

    module
        .declare_function("bunker_hashmap_is_empty", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_hashmap_is_empty: {}", e))
}

fn declare_hashmap_values_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // map ptr
    sig.returns.push(AbiParam::new(types::I64)); // vec ptr

    module
        .declare_function("bunker_hashmap_values", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_hashmap_values: {}", e))
}

// ============================================================================
// Result<T, E> Function Declarations
// ============================================================================

fn declare_result_ok_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // value
    sig.returns.push(AbiParam::new(types::I64)); // result ptr

    module
        .declare_function("bunker_result_ok", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_result_ok: {}", e))
}

fn declare_result_err_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // error
    sig.returns.push(AbiParam::new(types::I64)); // result ptr

    module
        .declare_function("bunker_result_err", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_result_err: {}", e))
}

fn declare_result_is_ok_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // result ptr
    sig.returns.push(AbiParam::new(types::I64)); // 1 if ok, 0 if err

    module
        .declare_function("bunker_result_is_ok", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_result_is_ok: {}", e))
}

fn declare_result_is_err_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // result ptr
    sig.returns.push(AbiParam::new(types::I64)); // 1 if err, 0 if ok

    module
        .declare_function("bunker_result_is_err", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_result_is_err: {}", e))
}

fn declare_result_unwrap_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // result ptr
    sig.returns.push(AbiParam::new(types::I64)); // ok value

    module
        .declare_function("bunker_result_unwrap", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_result_unwrap: {}", e))
}

fn declare_result_unwrap_err_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // result ptr
    sig.returns.push(AbiParam::new(types::I64)); // err value

    module
        .declare_function("bunker_result_unwrap_err", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_result_unwrap_err: {}", e))
}

fn declare_result_tag_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // result ptr
    sig.returns.push(AbiParam::new(types::I64)); // tag (0=ok, 1=err)

    module
        .declare_function("bunker_result_tag", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_result_tag: {}", e))
}

fn declare_result_value_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // result ptr
    sig.returns.push(AbiParam::new(types::I64)); // value

    module
        .declare_function("bunker_result_value", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_result_value: {}", e))
}

// ============================================================================
// HashMap<K, V> Function Declarations
// ============================================================================

fn declare_hashmap_new_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.returns.push(AbiParam::new(types::I64)); // hashmap ptr

    module
        .declare_function("bunker_hashmap_new", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_hashmap_new: {}", e))
}

fn declare_hashmap_new_str_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.returns.push(AbiParam::new(types::I64)); // hashmap ptr

    module
        .declare_function("bunker_hashmap_new_str", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_hashmap_new_str: {}", e))
}

fn declare_hashmap_insert_str_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // map ptr
    sig.params.push(AbiParam::new(types::I64)); // key
    sig.params.push(AbiParam::new(types::I64)); // value
    sig.returns.push(AbiParam::new(types::I64)); // success (1 or 0)

    module
        .declare_function("bunker_hashmap_insert_str", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_hashmap_insert_str: {}", e))
}

fn declare_hashmap_insert_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // map ptr
    sig.params.push(AbiParam::new(types::I64)); // key
    sig.params.push(AbiParam::new(types::I64)); // value
    sig.returns.push(AbiParam::new(types::I64)); // success (1 or 0)

    module
        .declare_function("bunker_hashmap_insert", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_hashmap_insert: {}", e))
}

fn declare_hashmap_get_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // map ptr
    sig.params.push(AbiParam::new(types::I64)); // key
    sig.returns.push(AbiParam::new(types::I64)); // value (0 if not found)

    module
        .declare_function("bunker_hashmap_get", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_hashmap_get: {}", e))
}

fn declare_hashmap_contains_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // map ptr
    sig.params.push(AbiParam::new(types::I64)); // key
    sig.returns.push(AbiParam::new(types::I64)); // 1 if found, 0 if not

    module
        .declare_function("bunker_hashmap_contains", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_hashmap_contains: {}", e))
}

fn declare_hashmap_remove_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // map ptr
    sig.params.push(AbiParam::new(types::I64)); // key
    sig.returns.push(AbiParam::new(types::I64)); // 1 if removed, 0 if not found

    module
        .declare_function("bunker_hashmap_remove", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_hashmap_remove: {}", e))
}

fn declare_hashmap_len_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // map ptr
    sig.returns.push(AbiParam::new(types::I64)); // length

    module
        .declare_function("bunker_hashmap_len", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_hashmap_len: {}", e))
}

fn declare_hashmap_clear_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // map ptr

    module
        .declare_function("bunker_hashmap_clear", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_hashmap_clear: {}", e))
}

fn declare_hashmap_keys_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64)); // map ptr
    sig.returns.push(AbiParam::new(types::I64)); // vec ptr containing keys

    module
        .declare_function("bunker_hashmap_keys", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_hashmap_keys: {}", e))
}

fn declare_hashmap_get_opt_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_hashmap_get_opt", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_hashmap_get_opt: {}", e))
}

fn declare_vec_get_opt_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_vec_get_opt", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_vec_get_opt: {}", e))
}

fn declare_vec_pop_opt_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_vec_pop_opt", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_vec_pop_opt: {}", e))
}

fn declare_read_file_result_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_read_file_result", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_read_file_result: {}", e))
}

fn declare_write_file_result_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_write_file_result", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_write_file_result: {}", e))
}

fn declare_parse_int_result_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_parse_int_result", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_parse_int_result: {}", e))
}

fn declare_str_index_of_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_str_index_of", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_str_index_of: {}", e))
}

fn declare_str_replace_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.params.push(AbiParam::new(types::I64));
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_str_replace", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_str_replace: {}", e))
}

fn declare_str_split_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_str_split", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_str_split: {}", e))
}

fn declare_str_to_upper_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_str_to_upper", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_str_to_upper: {}", e))
}

fn declare_str_to_lower_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_str_to_lower", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_str_to_lower: {}", e))
}

fn declare_str_repeat_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_str_repeat", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_str_repeat: {}", e))
}

fn declare_path_join_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_path_join", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_path_join: {}", e))
}

fn declare_path_dir_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_path_dir", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_path_dir: {}", e))
}

fn declare_path_base_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_path_base", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_path_base: {}", e))
}

fn declare_path_ext_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_path_ext", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_path_ext: {}", e))
}

fn declare_path_is_abs_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I8));
    module
        .declare_function("bunker_path_is_abs", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_path_is_abs: {}", e))
}

fn declare_env_var_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_env_var", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_env_var: {}", e))
}

fn declare_env_get_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_env_get", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_env_get: {}", e))
}

fn declare_env_set_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I8));
    module
        .declare_function("bunker_env_set", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_env_set: {}", e))
}

fn declare_env_has_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I8));
    module
        .declare_function("bunker_env_has", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_env_has: {}", e))
}

fn declare_time_now_ms_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_time_now_ms", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_time_now_ms: {}", e))
}

fn declare_time_now_unix_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_time_now_unix", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_time_now_unix: {}", e))
}

fn declare_bytes_new_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_bytes_new", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_bytes_new: {}", e))
}

fn declare_bytes_len_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_bytes_len", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_bytes_len: {}", e))
}

fn declare_bytes_capacity_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_bytes_capacity", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_bytes_capacity: {}", e))
}

fn declare_bytes_get_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I32));
    module
        .declare_function("bunker_bytes_get", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_bytes_get: {}", e))
}

fn declare_bytes_set_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.params.push(AbiParam::new(types::I64));
    sig.params.push(AbiParam::new(types::I32));
    sig.returns.push(AbiParam::new(types::I32));
    module
        .declare_function("bunker_bytes_set", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_bytes_set: {}", e))
}

fn declare_bytes_push_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.params.push(AbiParam::new(types::I32));
    sig.returns.push(AbiParam::new(types::I32));
    module
        .declare_function("bunker_bytes_push", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_bytes_push: {}", e))
}

fn declare_bytes_from_str_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_bytes_from_str", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_bytes_from_str: {}", e))
}

fn declare_bytes_to_str_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_bytes_to_str", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_bytes_to_str: {}", e))
}

fn declare_slice_new_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.params.push(AbiParam::new(types::I64));
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_slice_new", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_slice_new: {}", e))
}

fn declare_slice_len_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_slice_len", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_slice_len: {}", e))
}

fn declare_slice_get_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_slice_get", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_slice_get: {}", e))
}

fn declare_slice_sub_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.params.push(AbiParam::new(types::I64));
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_slice_sub", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_slice_sub: {}", e))
}

fn declare_slice_contains_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I8));
    module
        .declare_function("bunker_slice_contains", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_slice_contains: {}", e))
}

fn declare_slice_to_vec_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_slice_to_vec", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_slice_to_vec: {}", e))
}

fn declare_vec_as_slice_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_vec_as_slice", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_vec_as_slice: {}", e))
}

fn declare_vec_slice_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.params.push(AbiParam::new(types::I64));
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_vec_slice", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_vec_slice: {}", e))
}

fn declare_bytes_as_slice_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_bytes_as_slice", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_bytes_as_slice: {}", e))
}

fn declare_bytes_slice_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.params.push(AbiParam::new(types::I64));
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_bytes_slice", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_bytes_slice: {}", e))
}

fn declare_path_exists_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I8));
    module
        .declare_function("bunker_path_exists", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_path_exists: {}", e))
}

fn declare_path_is_file_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I8));
    module
        .declare_function("bunker_path_is_file", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_path_is_file: {}", e))
}

fn declare_path_is_dir_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I8));
    module
        .declare_function("bunker_path_is_dir", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_path_is_dir: {}", e))
}

fn declare_file_read_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_file_read", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_file_read: {}", e))
}

fn declare_file_write_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_file_write", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_file_write: {}", e))
}

fn declare_file_size_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_file_size", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_file_size: {}", e))
}

fn declare_file_remove_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_file_remove", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_file_remove: {}", e))
}

fn declare_file_read_bytes_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_file_read_bytes", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_file_read_bytes: {}", e))
}

fn declare_file_write_bytes_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_file_write_bytes", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_file_write_bytes: {}", e))
}

fn declare_dir_create_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_dir_create", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_dir_create: {}", e))
}

fn declare_dir_remove_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_dir_remove", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_dir_remove: {}", e))
}

fn declare_process_is_sandboxed_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.returns.push(AbiParam::new(types::I8));
    module
        .declare_function("bunker_process_is_sandboxed", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_process_is_sandboxed: {}", e))
}

fn declare_process_pid_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.returns.push(AbiParam::new(types::I32));
    module
        .declare_function("bunker_process_pid", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_process_pid: {}", e))
}

fn declare_process_exit_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I32));
    module
        .declare_function("bunker_process_exit", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_process_exit: {}", e))
}

fn declare_process_run_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_process_run", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_process_run: {}", e))
}

fn declare_process_run_status_func(module: &mut JITModule) -> Result<FuncId> {
    let mut sig = module.make_signature();
    sig.params.push(AbiParam::new(types::I64));
    sig.returns.push(AbiParam::new(types::I64));
    module
        .declare_function("bunker_process_run_status", Linkage::Import, &sig)
        .map_err(|e| anyhow!("Failed to declare runtime bunker_process_run_status: {}", e))
}

fn emit_alloc(
    builder: &mut FunctionBuilder,
    module: &mut JITModule,
    alloc_func: FuncId,
    size: i64,
    align: i64,
) -> Result<Value> {
    if size == 0 {
        return Ok(builder.ins().iconst(types::I64, 0));
    }

    let func_ref = module.declare_func_in_func(alloc_func, builder.func);
    let size_val = builder.ins().iconst(types::I64, size);
    let align_val = builder.ins().iconst(types::I64, align);
    let call = builder.ins().call(func_ref, &[size_val, align_val]);
    Ok(builder.inst_results(call)[0])
}
