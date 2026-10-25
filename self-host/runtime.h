/* Bunker Runtime Library for C Backend
 * This provides the runtime support for Bunker programs compiled to C
 */

#ifndef BUNKER_RUNTIME_H
#define BUNKER_RUNTIME_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#if defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#else
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

/* ============================================
 * Type Definitions
 * ============================================ */

typedef int32_t bkr_i32;
typedef int64_t bkr_i64;
typedef double  bkr_f64;
typedef int     bkr_bool;
typedef char*   bkr_str;

#define BKR_TRUE  1
#define BKR_FALSE 0

/* ============================================
 * Arena Allocator (64 KB Chunked Bump Allocator)
 * ============================================ */

#define BKR_ARENA_BLOCK_SIZE (64 * 1024)

typedef struct BkrArenaBlock {
    struct BkrArenaBlock* next;
    size_t capacity;
    size_t used;
    char data[];
} BkrArenaBlock;

typedef struct {
    BkrArenaBlock* head;
    BkrArenaBlock* current;
    size_t total_allocated;
} BkrArena;

static BkrArena g_bkr_arena = { NULL, NULL, 0 };
static int g_bkr_arena_atexit_registered = 0;

static inline void bkr_arena_free_all(void) {
    BkrArenaBlock* block = g_bkr_arena.head;
    while (block) {
        BkrArenaBlock* next = block->next;
        free(block);
        block = next;
    }
    g_bkr_arena.head = NULL;
    g_bkr_arena.current = NULL;
    g_bkr_arena.total_allocated = 0;
}

static inline void* bkr_arena_alloc(size_t size, size_t align) {
    if (size == 0) return NULL;
    if (align < 1) align = 1;
    if (!g_bkr_arena_atexit_registered) {
        atexit(bkr_arena_free_all);
        g_bkr_arena_atexit_registered = 1;
    }

    /* Check if current block has space */
    BkrArenaBlock* cur = g_bkr_arena.current;
    if (cur) {
        uintptr_t current_addr = (uintptr_t)(cur->data + cur->used);
        uintptr_t aligned_addr = (current_addr + align - 1) & ~(uintptr_t)(align - 1);
        size_t padding = (size_t)(aligned_addr - current_addr);
        if (cur->used + padding + size <= cur->capacity) {
            cur->used += padding + size;
            g_bkr_arena.total_allocated += size;
            return (void*)aligned_addr;
        }
    }

    /* Need a new block */
    size_t block_data_size = BKR_ARENA_BLOCK_SIZE;
    if (size + align > block_data_size) {
        block_data_size = size + align;
    }

    BkrArenaBlock* new_block = (BkrArenaBlock*)malloc(sizeof(BkrArenaBlock) + block_data_size);
    if (!new_block) return NULL;

    new_block->next = NULL;
    new_block->capacity = block_data_size;

    uintptr_t data_addr = (uintptr_t)new_block->data;
    uintptr_t aligned_addr = (data_addr + align - 1) & ~(uintptr_t)(align - 1);
    size_t padding = (size_t)(aligned_addr - data_addr);

    new_block->used = padding + size;
    g_bkr_arena.total_allocated += size;

    if (!g_bkr_arena.head) {
        g_bkr_arena.head = new_block;
    } else if (g_bkr_arena.current) {
        g_bkr_arena.current->next = new_block;
    }
    g_bkr_arena.current = new_block;

    return (void*)aligned_addr;
}

/* ============================================
 * ASCII Character Cache (Zero-allocation for ASCII)
 * ============================================ */

static char g_bkr_ascii_table[128][2];
static int g_bkr_ascii_table_init = 0;

static inline void bkr_init_ascii_table(void) {
    if (!g_bkr_ascii_table_init) {
        for (int i = 0; i < 128; i++) {
            g_bkr_ascii_table[i][0] = (char)i;
            g_bkr_ascii_table[i][1] = '\0';
        }
        g_bkr_ascii_table_init = 1;
    }
}

/* Cached string length for fast repeated index checks */
static bkr_str g_bkr_cached_str = NULL;
static bkr_i64 g_bkr_cached_len = 0;

/* ============================================
 * Vector (Dynamic Array)
 * ============================================ */

typedef struct {
    bkr_i64* data;
    bkr_i64 len;
    bkr_i64 cap;
} BkrVec;

static inline bkr_i64 vec_new(void) {
    BkrVec* v = (BkrVec*)bkr_arena_alloc(sizeof(BkrVec), sizeof(void*));
    if (!v) return 0;
    v->cap = 8;
    v->len = 0;
    v->data = (bkr_i64*)bkr_arena_alloc(sizeof(bkr_i64) * (size_t)v->cap, sizeof(bkr_i64));
    return (bkr_i64)(intptr_t)v;
}

static inline bkr_bool vec_push(bkr_i64 handle, bkr_i64 value) {
    BkrVec* v = (BkrVec*)(intptr_t)handle;
    if (!v) return BKR_FALSE;
    if (v->len >= v->cap) {
        bkr_i64 new_cap = v->cap * 2;
        bkr_i64* new_data = (bkr_i64*)bkr_arena_alloc(sizeof(bkr_i64) * (size_t)new_cap, sizeof(bkr_i64));
        if (!new_data) return BKR_FALSE;
        if (v->data && v->len > 0) {
            memcpy(new_data, v->data, sizeof(bkr_i64) * (size_t)v->len);
        }
        v->data = new_data;
        v->cap = new_cap;
    }
    v->data[v->len++] = value;
    return BKR_TRUE;
}

static inline bkr_i64 vec_get(bkr_i64 handle, bkr_i64 index) {
    BkrVec* v = (BkrVec*)(intptr_t)handle;
    if (!v || index < 0 || index >= v->len) return 0;
    return v->data[index];
}

static inline bkr_bool vec_set(bkr_i64 handle, bkr_i64 index, bkr_i64 value) {
    BkrVec* v = (BkrVec*)(intptr_t)handle;
    if (!v || index < 0 || index >= v->len) return BKR_FALSE;
    v->data[index] = value;
    return BKR_TRUE;
}

static inline bkr_i64 vec_len(bkr_i64 handle) {
    BkrVec* v = (BkrVec*)(intptr_t)handle;
    if (!v) return 0;
    return v->len;
}

static inline bkr_i64 vec_pop(bkr_i64 handle) {
    BkrVec* v = (BkrVec*)(intptr_t)handle;
    if (!v || v->len <= 0) return 0;
    v->len--;
    return v->data[v->len];
}

static inline void vec_free(bkr_i64 handle) {
    /* No-op: memory is managed by the arena */
    (void)handle;
}

static inline bkr_bool vec_contains(bkr_i64 handle, bkr_i64 item) {
    BkrVec* v = (BkrVec*)(intptr_t)handle;
    if (!v || !v->data) return BKR_FALSE;
    for (bkr_i64 i = 0; i < v->len; i++) {
        if (v->data[i] == item) return BKR_TRUE;
    }
    return BKR_FALSE;
}

static inline bkr_bool vec_contains_str(bkr_i64 handle, bkr_i64 item) {
    BkrVec* v = (BkrVec*)(intptr_t)handle;
    if (!v || !v->data) return BKR_FALSE;
    bkr_str s2 = (bkr_str)(intptr_t)item;
    for (bkr_i64 i = 0; i < v->len; i++) {
        bkr_str s1 = (bkr_str)(intptr_t)v->data[i];
        if (s1 == s2) return BKR_TRUE;
        if (s1 && s2 && strcmp(s1, s2) == 0) return BKR_TRUE;
    }
    return BKR_FALSE;
}

static inline bkr_bool vec_is_empty(bkr_i64 handle) {
    BkrVec* v = (BkrVec*)(intptr_t)handle;
    return (!v || v->len == 0) ? BKR_TRUE : BKR_FALSE;
}

static inline bkr_i64 vec_clone(bkr_i64 handle) {
    bkr_i64 new_v = vec_new();
    BkrVec* v = (BkrVec*)(intptr_t)handle;
    if (!v || !v->data) return new_v;
    for (bkr_i64 i = 0; i < v->len; i++) {
        vec_push(new_v, v->data[i]);
    }
    return new_v;
}

static inline bkr_bool vec_reverse(bkr_i64 handle) {
    BkrVec* v = (BkrVec*)(intptr_t)handle;
    if (!v || !v->data) return BKR_FALSE;
    if (v->len > 1) {
        bkr_i64 i = 0;
        bkr_i64 j = v->len - 1;
        while (i < j) {
            bkr_i64 tmp = v->data[i];
            v->data[i] = v->data[j];
            v->data[j] = tmp;
            i++;
            j--;
        }
    }
    return BKR_TRUE;
}

static inline bkr_i64 vec_map(bkr_i64 handle, bkr_i64 fn_ptr) {
    bkr_i64 res = vec_new();
    BkrVec* v = (BkrVec*)(intptr_t)handle;
    if (!v || !v->data || fn_ptr == 0) return res;
    bkr_i64 (*f)(bkr_i64) = (bkr_i64 (*)(bkr_i64))(intptr_t)fn_ptr;
    for (bkr_i64 i = 0; i < v->len; i++) {
        vec_push(res, f(v->data[i]));
    }
    return res;
}

static inline bkr_i64 vec_filter(bkr_i64 handle, bkr_i64 fn_ptr) {
    bkr_i64 res = vec_new();
    BkrVec* v = (BkrVec*)(intptr_t)handle;
    if (!v || !v->data || fn_ptr == 0) return res;
    bkr_i64 (*f)(bkr_i64) = (bkr_i64 (*)(bkr_i64))(intptr_t)fn_ptr;
    for (bkr_i64 i = 0; i < v->len; i++) {
        if (f(v->data[i])) {
            vec_push(res, v->data[i]);
        }
    }
    return res;
}

static inline bkr_i64 vec_fold(bkr_i64 handle, bkr_i64 init, bkr_i64 fn_ptr) {
    BkrVec* v = (BkrVec*)(intptr_t)handle;
    if (!v || !v->data || fn_ptr == 0) return init;
    bkr_i64 (*f)(bkr_i64, bkr_i64) = (bkr_i64 (*)(bkr_i64, bkr_i64))(intptr_t)fn_ptr;
    bkr_i64 acc = init;
    for (bkr_i64 i = 0; i < v->len; i++) {
        acc = f(acc, v->data[i]);
    }
    return acc;
}

/* ============================================
 * Byte Buffer
 * ============================================ */

typedef struct {
    uint8_t* data;
    bkr_i64 len;
    bkr_i64 cap;
} BkrBytes;

static inline bkr_i64 bytes_new(bkr_i64 cap) {
    if (cap < 8) cap = 8;
    BkrBytes* b = (BkrBytes*)bkr_arena_alloc(sizeof(BkrBytes), sizeof(void*));
    if (!b) return 0;
    b->cap = cap;
    b->len = 0;
    b->data = (uint8_t*)bkr_arena_alloc((size_t)b->cap, 1);
    return (bkr_i64)(intptr_t)b;
}

static inline bkr_i64 bytes_len(bkr_i64 handle) {
    BkrBytes* b = (BkrBytes*)(intptr_t)handle;
    if (!b) return 0;
    return b->len;
}

static inline bkr_i64 bytes_capacity(bkr_i64 handle) {
    BkrBytes* b = (BkrBytes*)(intptr_t)handle;
    if (!b) return 0;
    return b->cap;
}

static inline bkr_i32 bytes_get(bkr_i64 handle, bkr_i64 index) {
    BkrBytes* b = (BkrBytes*)(intptr_t)handle;
    if (!b || index < 0 || index >= b->len) return 0;
    return (bkr_i32)b->data[index];
}

static inline bkr_bool bytes_set(bkr_i64 handle, bkr_i64 index, bkr_i32 val) {
    BkrBytes* b = (BkrBytes*)(intptr_t)handle;
    if (!b || index < 0 || index >= b->len) return BKR_FALSE;
    b->data[index] = (uint8_t)(val & 0xFF);
    return BKR_TRUE;
}

static inline bkr_bool bytes_push(bkr_i64 handle, bkr_i32 val) {
    BkrBytes* b = (BkrBytes*)(intptr_t)handle;
    if (!b) return BKR_FALSE;
    if (b->len >= b->cap) {
        bkr_i64 new_cap = b->cap * 2;
        uint8_t* new_data = (uint8_t*)bkr_arena_alloc((size_t)new_cap, 1);
        if (!new_data) return BKR_FALSE;
        memcpy(new_data, b->data, (size_t)b->len);
        b->data = new_data;
        b->cap = new_cap;
    }
    b->data[b->len++] = (uint8_t)(val & 0xFF);
    return BKR_TRUE;
}

static inline bkr_i64 bytes_from_str(bkr_str s) {
    if (!s) return bytes_new(8);
    size_t slen = strlen(s);
    bkr_i64 handle = bytes_new((bkr_i64)slen);
    BkrBytes* b = (BkrBytes*)(intptr_t)handle;
    if (!b) return 0;
    memcpy(b->data, s, slen);
    b->len = (bkr_i64)slen;
    return handle;
}

static inline bkr_str bytes_to_str(bkr_i64 handle) {
    BkrBytes* b = (BkrBytes*)(intptr_t)handle;
    if (!b || b->len == 0) {
        bkr_str empty = (bkr_str)bkr_arena_alloc(1, 1);
        if (empty) empty[0] = '\0';
        return empty;
    }
    bkr_str s = (bkr_str)bkr_arena_alloc((size_t)b->len + 1, 1);
    if (!s) return NULL;
    memcpy(s, b->data, (size_t)b->len);
    s[b->len] = '\0';
    return s;
}

/* ============================================
 * Slices (D-008)
 * ============================================ */

typedef struct {
    void* data;
    bkr_i64 len;
    bkr_i64 elem_size;
} BkrSlice;

static inline bkr_i64 slice_new(bkr_i64 data_ptr, bkr_i64 len, bkr_i64 elem_size) {
    BkrSlice* s = (BkrSlice*)bkr_arena_alloc(sizeof(BkrSlice), sizeof(void*));
    if (!s) return 0;
    if (len < 0 || data_ptr == 0) len = 0;
    if (elem_size <= 0) elem_size = 8;
    s->data = (void*)(intptr_t)data_ptr;
    s->len = len;
    s->elem_size = elem_size;
    return (bkr_i64)(intptr_t)s;
}

static inline bkr_i64 slice_len(bkr_i64 handle) {
    BkrSlice* s = (BkrSlice*)(intptr_t)handle;
    if (!s) return 0;
    return s->len;
}

static inline bkr_i64 slice_get(bkr_i64 handle, bkr_i64 index) {
    BkrSlice* s = (BkrSlice*)(intptr_t)handle;
    if (!s || index < 0 || index >= s->len || !s->data) return 0;
    uint8_t* raw = (uint8_t*)s->data;
    if (s->elem_size == 1) return (bkr_i64)raw[index];
    if (s->elem_size == 4) return (bkr_i64)((int32_t*)raw)[index];
    return ((bkr_i64*)raw)[index];
}

static inline bkr_i64 slice_sub(bkr_i64 handle, bkr_i64 start, bkr_i64 sub_len) {
    BkrSlice* s = (BkrSlice*)(intptr_t)handle;
    if (!s || start < 0 || sub_len <= 0 || !s->data || start >= s->len) {
        return slice_new(0, 0, s ? s->elem_size : 8);
    }
    bkr_i64 avail = s->len - start;
    bkr_i64 actual = (sub_len > avail) ? avail : sub_len;
    uint8_t* sub_data = (uint8_t*)s->data + (start * s->elem_size);
    return slice_new((bkr_i64)(intptr_t)sub_data, actual, s->elem_size);
}

static inline bkr_bool slice_contains(bkr_i64 handle, bkr_i64 item) {
    BkrSlice* s = (BkrSlice*)(intptr_t)handle;
    if (!s || !s->data || s->len <= 0) return BKR_FALSE;
    for (bkr_i64 i = 0; i < s->len; i++) {
        if (slice_get(handle, i) == item) return BKR_TRUE;
    }
    return BKR_FALSE;
}

static inline bkr_i64 slice_to_vec(bkr_i64 handle) {
    bkr_i64 v_handle = vec_new();
    BkrSlice* s = (BkrSlice*)(intptr_t)handle;
    if (!s || !s->data || s->len <= 0) return v_handle;
    for (bkr_i64 i = 0; i < s->len; i++) {
        vec_push(v_handle, slice_get(handle, i));
    }
    return v_handle;
}

static inline bkr_i64 vec_as_slice(bkr_i64 vec_handle) {
    BkrVec* v = (BkrVec*)(intptr_t)vec_handle;
    if (!v) return slice_new(0, 0, 8);
    return slice_new((bkr_i64)(intptr_t)v->data, v->len, 8);
}

static inline bkr_i64 vec_slice(bkr_i64 vec_handle, bkr_i64 start, bkr_i64 sub_len) {
    bkr_i64 full = vec_as_slice(vec_handle);
    return slice_sub(full, start, sub_len);
}

static inline bkr_i64 bytes_as_slice(bkr_i64 handle) {
    BkrBytes* b = (BkrBytes*)(intptr_t)handle;
    if (!b) return slice_new(0, 0, 1);
    return slice_new((bkr_i64)(intptr_t)b->data, b->len, 1);
}

static inline bkr_i64 bytes_slice(bkr_i64 handle, bkr_i64 start, bkr_i64 sub_len) {
    bkr_i64 full = bytes_as_slice(handle);
    return slice_sub(full, start, sub_len);
}

/* ============================================
 * String Operations
 * ============================================ */

static inline bkr_i64 bkr_len(bkr_str s) {
    if (s == NULL) return 0;
    if (s == g_bkr_cached_str) return g_bkr_cached_len;
    g_bkr_cached_str = s;
    g_bkr_cached_len = (bkr_i64)strlen(s);
    return g_bkr_cached_len;
}

static inline bkr_i64 char_code(bkr_str s) {
    if (s == NULL) return 0;
    return (bkr_i64)(unsigned char)s[0];
}

static inline bkr_i64 char_code_at(bkr_str s, bkr_i64 index) {
    if (s == NULL || index < 0) {
        return 0;
    }
    bkr_i64 len;
    if (s == g_bkr_cached_str) {
        len = g_bkr_cached_len;
    } else {
        len = (bkr_i64)strlen(s);
        g_bkr_cached_str = s;
        g_bkr_cached_len = len;
    }
    if (index >= len) {
        return 0;
    }
    return (bkr_i64)(unsigned char)s[index];
}

static inline bkr_str from_char_code(bkr_i64 code) {
    bkr_init_ascii_table();
    if (code >= 0 && code < 128) {
        return g_bkr_ascii_table[code];
    }
    char* result = (char*)bkr_arena_alloc(2, 1);
    if (!result) return "";
    result[0] = (char)(unsigned char)code;
    result[1] = '\0';
    return result;
}

static inline bkr_str char_at(bkr_str s, bkr_i64 index) {
    if (s == NULL || index < 0) return "";
    bkr_i64 code = char_code_at(s, index);
    if (code == 0) {
        if (index >= bkr_len(s)) return "";
    }
    return from_char_code(code);
}

static inline bkr_str substring(bkr_str s, bkr_i64 start, bkr_i64 end) {
    if (s == NULL || start < 0 || end < start) return "";
    bkr_i64 len = end - start;
    if (len == 0) return "";
    if (len == 1) {
        return from_char_code(char_code_at(s, start));
    }
    char* result = (char*)bkr_arena_alloc((size_t)len + 1, 1);
    if (!result) return "";
    memcpy(result, s + start, (size_t)len);
    result[len] = '\0';
    return result;
}

static inline bkr_bool contains(bkr_str s, bkr_str needle) {
    if (s == NULL || needle == NULL) return BKR_FALSE;
    return strstr(s, needle) != NULL ? BKR_TRUE : BKR_FALSE;
}

static inline bkr_bool starts_with(bkr_str s, bkr_str prefix) {
    if (s == NULL || prefix == NULL) return BKR_FALSE;
    bkr_i64 prefix_len = (bkr_i64)strlen(prefix);
    return strncmp(s, prefix, (size_t)prefix_len) == 0 ? BKR_TRUE : BKR_FALSE;
}

static inline bkr_bool ends_with(bkr_str s, bkr_str suffix) {
    if (s == NULL || suffix == NULL) return BKR_FALSE;
    bkr_i64 s_len = bkr_len(s);
    bkr_i64 suffix_len = (bkr_i64)strlen(suffix);
    if (suffix_len > s_len) return BKR_FALSE;
    return strcmp(s + s_len - suffix_len, suffix) == 0 ? BKR_TRUE : BKR_FALSE;
}

static inline bkr_bool bkr_is_space(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' ? BKR_TRUE : BKR_FALSE;
}

static inline bkr_str trim(bkr_str s) {
    if (s == NULL) return "";
    bkr_i64 start = 0;
    bkr_i64 end = bkr_len(s);
    while (start < end && bkr_is_space(s[start])) {
        start = start + 1;
    }
    while (end > start && bkr_is_space(s[end - 1])) {
        end = end - 1;
    }
    return substring(s, start, end);
}

static inline bkr_i64 parse_int(bkr_str s) {
    if (s == NULL) return 0;
    return (bkr_i64)strtoll(s, NULL, 10);
}

static inline bkr_str int_to_string(bkr_i64 value) {
    if (value >= 0 && value <= 9) {
        return from_char_code('0' + value);
    }
    char* result = (char*)bkr_arena_alloc(32, 1);
    if (!result) return "";
    snprintf(result, 32, "%lld", (long long)value);
    return result;
}

static inline bkr_str bkr_str_concat(bkr_str a, bkr_str b) {
    if (!a || a[0] == '\0') return b ? b : "";
    if (!b || b[0] == '\0') return a;
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);
    char* result = (char*)bkr_arena_alloc(len_a + len_b + 1, 1);
    if (!result) return "";
    memcpy(result, a, len_a);
    memcpy(result + len_a, b, len_b + 1);
    return result;
}

static inline bkr_str join_lines(bkr_i64 handle) {
    BkrVec* v = (BkrVec*)(intptr_t)handle;
    if (!v || v->len <= 0) return "";

    size_t total = 0;
    for (bkr_i64 i = 0; i < v->len; i++) {
        bkr_str line = (bkr_str)(intptr_t)v->data[i];
        if (line) total += strlen(line);
        total += 1;
    }

    char* result = (char*)bkr_arena_alloc(total + 1, 1);
    if (!result) return "";
    char* cursor = result;
    for (bkr_i64 i = 0; i < v->len; i++) {
        bkr_str line = (bkr_str)(intptr_t)v->data[i];
        if (line) {
            size_t len = strlen(line);
            memcpy(cursor, line, len);
            cursor += len;
        }
        *cursor++ = '\n';
    }
    *cursor = '\0';
    return result;
}

static inline bkr_bool bkr_str_eq(bkr_str a, bkr_str b) {
    return strcmp(a, b) == 0 ? BKR_TRUE : BKR_FALSE;
}

/* ============================================
 * Result
 * ============================================ */

typedef struct {
    bkr_i64 tag;   /* 0 = Ok, 1 = Err */
    bkr_i64 value;
} BkrResult;

static inline bkr_i64 bkr_result_ok(bkr_i64 value) {
    BkrResult* r = (BkrResult*)bkr_arena_alloc(sizeof(BkrResult), sizeof(void*));
    if (!r) return 0;
    r->tag = 0;
    r->value = value;
    return (bkr_i64)(intptr_t)r;
}

static inline bkr_i64 bkr_result_err(bkr_i64 value) {
    BkrResult* r = (BkrResult*)bkr_arena_alloc(sizeof(BkrResult), sizeof(void*));
    if (!r) return 0;
    r->tag = 1;
    r->value = value;
    return (bkr_i64)(intptr_t)r;
}

static inline bkr_bool bkr_result_is_ok(bkr_i64 handle) {
    BkrResult* r = (BkrResult*)(intptr_t)handle;
    return r && r->tag == 0 ? BKR_TRUE : BKR_FALSE;
}

static inline bkr_bool bkr_result_is_err(bkr_i64 handle) {
    BkrResult* r = (BkrResult*)(intptr_t)handle;
    return r && r->tag == 1 ? BKR_TRUE : BKR_FALSE;
}

static inline bkr_i64 bkr_result_unwrap(bkr_i64 handle) {
    BkrResult* r = (BkrResult*)(intptr_t)handle;
    return r ? r->value : 0;
}

static inline bkr_i64 bkr_result_unwrap_err(bkr_i64 handle) {
    BkrResult* r = (BkrResult*)(intptr_t)handle;
    return r ? r->value : 0;
}

static inline bkr_i64 bkr_result_tag(bkr_i64 handle) {
    BkrResult* r = (BkrResult*)(intptr_t)handle;
    return r ? r->tag : 1;
}

static inline bkr_i64 bkr_result_value(bkr_i64 handle) {
    BkrResult* r = (BkrResult*)(intptr_t)handle;
    return r ? r->value : 0;
}

/* ============================================
 * Try Operator (?) Runtime Helpers
 * ============================================ */

static inline bkr_bool bkr_try_is_err(bkr_i64 val) {
    if (val == 0) return BKR_TRUE; /* Option::None */
    if ((val & 1) != 0) return BKR_FALSE; /* Option::Some */
    return bkr_result_is_err(val); /* Result check */
}

static inline bkr_i64 bkr_try_unwrap(bkr_i64 val) {
    if ((val & 1) != 0) return (val >> 1); /* Option::Some payload */
    return bkr_result_unwrap(val); /* Result::Ok payload */
}

/* ============================================
 * Tagged Union / Boxed Enum Payloads
 * ============================================ */

typedef struct {
    bkr_i64 tag;
    bkr_i64 count;
    bkr_i64 p0;
    bkr_i64 p1;
} BkrEnumBox;

static inline bkr_i64 bkr_enum_payload1(bkr_i64 tag, bkr_i64 p0) {
    BkrEnumBox* b = (BkrEnumBox*)bkr_arena_alloc(sizeof(BkrEnumBox), sizeof(void*));
    if (!b) return 0;
    b->tag = tag;
    b->count = 1;
    b->p0 = p0;
    b->p1 = 0;
    return (bkr_i64)(intptr_t)b;
}

static inline bkr_i64 bkr_enum_payload2(bkr_i64 tag, bkr_i64 p0, bkr_i64 p1) {
    BkrEnumBox* b = (BkrEnumBox*)bkr_arena_alloc(sizeof(BkrEnumBox), sizeof(void*));
    if (!b) return 0;
    b->tag = tag;
    b->count = 2;
    b->p0 = p0;
    b->p1 = p1;
    return (bkr_i64)(intptr_t)b;
}

static inline bkr_i64 bkr_enum_tag(bkr_i64 handle) {
    if (handle >= 0 && handle < 256) {
        return handle;
    }
    BkrEnumBox* b = (BkrEnumBox*)(intptr_t)handle;
    return b ? b->tag : 0;
}

static inline bkr_i64 bkr_enum_field(bkr_i64 handle, bkr_i64 index) {
    if (handle == 0) return 0;
    BkrEnumBox* b = (BkrEnumBox*)(intptr_t)handle;
    if (!b) return 0;
    if (index == 0) return b->p0;
    if (index == 1) return b->p1;
    return 0;
}

/* ============================================
 * Tuple Operations
 * ============================================ */

static inline bkr_i64 bkr_tuple2(bkr_i64 a, bkr_i64 b) {
    bkr_i64* t = (bkr_i64*)bkr_arena_alloc(2 * sizeof(bkr_i64), sizeof(void*));
    if (!t) return 0;
    t[0] = a;
    t[1] = b;
    return (bkr_i64)(intptr_t)t;
}

static inline bkr_i64 bkr_tuple3(bkr_i64 a, bkr_i64 b, bkr_i64 c) {
    bkr_i64* t = (bkr_i64*)bkr_arena_alloc(3 * sizeof(bkr_i64), sizeof(void*));
    if (!t) return 0;
    t[0] = a;
    t[1] = b;
    t[2] = c;
    return (bkr_i64)(intptr_t)t;
}

static inline bkr_i64 bkr_tuple_get(bkr_i64 handle, bkr_i64 index) {
    if (!handle) return 0;
    bkr_i64* t = (bkr_i64*)(intptr_t)handle;
    return t[index];
}

/* ============================================
 * I/O Operations
 * ============================================ */

static inline void bkr_print(bkr_str s) {
    printf("%s", s);
}

static inline void bkr_println(bkr_str s) {
    printf("%s\n", s);
}

static inline void bkr_log(bkr_str s) {
    printf("%s\n", s ? s : "");
}

static inline void bkr_print_i64(bkr_i64 n) {
    printf("%lld", (long long)n);
}

/* ============================================
 * Panic and Assert Runtime Policy
 * ============================================ */

static inline void bkr_panic(bkr_str s) {
    fprintf(stderr, "bunker runtime panic: %s\n", s ? s : "<no message>");
    fflush(stderr);
    exit(101);
}

static inline void bkr_assert(bkr_bool cond, bkr_str msg) {
    if (!cond) {
        fprintf(stderr, "bunker runtime assertion failed: %s\n", msg ? msg : "assertion failed");
        fflush(stderr);
        exit(101);
    }
}

static inline void panic(bkr_str s) {
    bkr_panic(s);
}

/* ============================================
 * HashMap (Arena-Backed Implementation)
 * ============================================ */

typedef struct BkrHashEntry {
    bkr_i64 key;
    bkr_i64 value;
    struct BkrHashEntry* next;
} BkrHashEntry;

typedef struct {
    BkrHashEntry** buckets;
    bkr_i64 size;
    bkr_i64 count;
    bkr_i64 key_type; /* 0 = int, 1 = str */
} BkrHashMap;

static inline bkr_i64 bkr_hash(bkr_i64 key) {
    bkr_i64 h = key;
    if (h < 0) h = -h;
    return h;
}

static inline bkr_i64 bkr_hash_str(bkr_str s) {
    if (!s) return 0;
    bkr_i64 h = 5381;
    unsigned char* p = (unsigned char*)s;
    while (*p) {
        h = ((h << 5) + h) + *p;
        p++;
    }
    if (h < 0) h = -h;
    return h;
}

static inline bkr_bool bkr_hashmap_key_eq(bkr_i64 key_type, bkr_i64 k1, bkr_i64 k2) {
    if (key_type == 1) {
        bkr_str s1 = (bkr_str)(intptr_t)k1;
        bkr_str s2 = (bkr_str)(intptr_t)k2;
        if (s1 == s2) return BKR_TRUE;
        if (!s1 || !s2) return BKR_FALSE;
        return strcmp(s1, s2) == 0 ? BKR_TRUE : BKR_FALSE;
    }
    return k1 == k2 ? BKR_TRUE : BKR_FALSE;
}

static inline bkr_i64 bkr_hashmap_key_hash(bkr_i64 key_type, bkr_i64 key) {
    if (key_type == 1) {
        return bkr_hash_str((bkr_str)(intptr_t)key);
    }
    return bkr_hash(key);
}

static inline bkr_i64 hashmap_new_typed(bkr_i64 key_type) {
    BkrHashMap* m = (BkrHashMap*)bkr_arena_alloc(sizeof(BkrHashMap), sizeof(void*));
    if (!m) return 0;
    m->size = 64;
    m->count = 0;
    m->key_type = key_type;
    m->buckets = (BkrHashEntry**)bkr_arena_alloc(sizeof(BkrHashEntry*) * (size_t)m->size, sizeof(void*));
    if (m->buckets) {
        memset(m->buckets, 0, sizeof(BkrHashEntry*) * (size_t)m->size);
    }
    return (bkr_i64)(intptr_t)m;
}

static inline bkr_i64 hashmap_new(void) {
    return hashmap_new_typed(0);
}

static inline bkr_i64 hashmap_new_str(void) {
    return hashmap_new_typed(1);
}

static inline bkr_bool hashmap_insert(bkr_i64 handle, bkr_i64 key, bkr_i64 value) {
    BkrHashMap* m = (BkrHashMap*)(intptr_t)handle;
    if (!m || !m->buckets) return BKR_FALSE;
    bkr_i64 idx = bkr_hashmap_key_hash(m->key_type, key) % m->size;

    BkrHashEntry* existing = m->buckets[idx];
    while (existing) {
        if (bkr_hashmap_key_eq(m->key_type, existing->key, key)) {
            existing->value = value;
            return BKR_TRUE;
        }
        existing = existing->next;
    }

    BkrHashEntry* entry = (BkrHashEntry*)bkr_arena_alloc(sizeof(BkrHashEntry), sizeof(void*));
    if (!entry) return BKR_FALSE;
    entry->key = key;
    entry->value = value;
    entry->next = m->buckets[idx];
    m->buckets[idx] = entry;
    m->count++;
    return BKR_TRUE;
}

static inline bkr_bool hashmap_insert_str(bkr_i64 handle, bkr_i64 key, bkr_i64 value) {
    BkrHashMap* m = (BkrHashMap*)(intptr_t)handle;
    if (m) m->key_type = 1;
    return hashmap_insert(handle, key, value);
}

static inline bkr_i64 hashmap_get(bkr_i64 handle, bkr_i64 key) {
    BkrHashMap* m = (BkrHashMap*)(intptr_t)handle;
    if (!m || !m->buckets) return 0;
    bkr_i64 idx = bkr_hashmap_key_hash(m->key_type, key) % m->size;

    BkrHashEntry* e = m->buckets[idx];
    while (e) {
        if (bkr_hashmap_key_eq(m->key_type, e->key, key)) return e->value;
        e = e->next;
    }
    return 0;
}

static inline bkr_bool hashmap_contains(bkr_i64 handle, bkr_i64 key) {
    BkrHashMap* m = (BkrHashMap*)(intptr_t)handle;
    if (!m || !m->buckets) return BKR_FALSE;
    bkr_i64 idx = bkr_hashmap_key_hash(m->key_type, key) % m->size;

    BkrHashEntry* e = m->buckets[idx];
    while (e) {
        if (bkr_hashmap_key_eq(m->key_type, e->key, key)) return BKR_TRUE;
        e = e->next;
    }
    return BKR_FALSE;
}

static inline bkr_bool hashmap_remove(bkr_i64 handle, bkr_i64 key) {
    BkrHashMap* m = (BkrHashMap*)(intptr_t)handle;
    if (!m || !m->buckets) return BKR_FALSE;
    bkr_i64 idx = bkr_hashmap_key_hash(m->key_type, key) % m->size;

    BkrHashEntry* prev = NULL;
    BkrHashEntry* e = m->buckets[idx];
    while (e) {
        if (bkr_hashmap_key_eq(m->key_type, e->key, key)) {
            if (prev) {
                prev->next = e->next;
            } else {
                m->buckets[idx] = e->next;
            }
            m->count--;
            return BKR_TRUE;
        }
        prev = e;
        e = e->next;
    }
    return BKR_FALSE;
}

static inline bkr_i64 hashmap_keys(bkr_i64 handle) {
    BkrHashMap* m = (BkrHashMap*)(intptr_t)handle;
    bkr_i64 keys = vec_new();
    if (!m || !m->buckets) return keys;

    bkr_i64 i = 0;
    while (i < m->size) {
        BkrHashEntry* e = m->buckets[i];
        while (e) {
            vec_push(keys, e->key);
            e = e->next;
        }
        i++;
    }
    return keys;
}

static inline bkr_bool hashmap_is_empty(bkr_i64 handle) {
    BkrHashMap* m = (BkrHashMap*)(intptr_t)handle;
    return (!m || m->count == 0) ? BKR_TRUE : BKR_FALSE;
}

static inline bkr_i64 hashmap_values(bkr_i64 handle) {
    BkrHashMap* m = (BkrHashMap*)(intptr_t)handle;
    bkr_i64 vals = vec_new();
    if (!m || !m->buckets) return vals;
    for (bkr_i64 i = 0; i < m->size; i++) {
        BkrHashEntry* e = m->buckets[i];
        while (e) {
            vec_push(vals, e->value);
            e = e->next;
        }
    }
    return vals;
}

static inline bkr_i64 hashmap_len(bkr_i64 handle) {
    BkrHashMap* m = (BkrHashMap*)(intptr_t)handle;
    if (!m) return 0;
    return m->count;
}

static inline bkr_i32 hashmap_clear(bkr_i64 handle) {
    BkrHashMap* m = (BkrHashMap*)(intptr_t)handle;
    if (!m || !m->buckets) return 0;
    memset(m->buckets, 0, sizeof(BkrHashEntry*) * (size_t)m->size);
    m->count = 0;
    return 0;
}

/* ============================================
 * File I/O
 * ============================================ */

static inline bkr_str bkr_raw_file_read(bkr_str path) {
    FILE* f = fopen(path, "rb");
    if (!f) return "";
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (size < 0) {
        fclose(f);
        return "";
    }
    char* buf = (char*)bkr_arena_alloc((size_t)size + 1, 1);
    if (!buf) {
        fclose(f);
        return "";
    }
    size_t read_bytes = fread(buf, 1, (size_t)size, f);
    buf[read_bytes] = '\0';
    fclose(f);
    return buf;
}

static inline bkr_bool bkr_raw_file_write(bkr_str path, bkr_str content) {
    FILE* f = fopen(path, "wb");
    if (!f) return BKR_FALSE;
    fputs(content, f);
    fclose(f);
    return BKR_TRUE;
}

static inline bkr_str read_file(bkr_str path) {
    return bkr_raw_file_read(path);
}

static inline bkr_bool write_file(bkr_str path, bkr_str content) {
    return bkr_raw_file_write(path, content);
}

static inline bkr_bool file_exists(bkr_str path) {
    FILE* f = fopen(path, "rb");
    if (!f) return BKR_FALSE;
    fclose(f);
    return BKR_TRUE;
}

static inline bkr_bool path_exists(bkr_str path) {
    if (!path) return BKR_FALSE;
    FILE* f = fopen(path, "rb");
    if (f) { fclose(f); return BKR_TRUE; }
#ifdef _WIN32
    DWORD attr = GetFileAttributesA(path);
    return (attr != INVALID_FILE_ATTRIBUTES) ? BKR_TRUE : BKR_FALSE;
#else
    struct stat st;
    return (stat(path, &st) == 0) ? BKR_TRUE : BKR_FALSE;
#endif
}

static inline bkr_bool path_is_file(bkr_str path) {
    if (!path) return BKR_FALSE;
#ifdef _WIN32
    DWORD attr = GetFileAttributesA(path);
    if (attr == INVALID_FILE_ATTRIBUTES) return BKR_FALSE;
    return (attr & FILE_ATTRIBUTE_DIRECTORY) ? BKR_FALSE : BKR_TRUE;
#else
    struct stat st;
    if (stat(path, &st) != 0) return BKR_FALSE;
    return S_ISREG(st.st_mode) ? BKR_TRUE : BKR_FALSE;
#endif
}

static inline bkr_bool path_is_dir(bkr_str path) {
    if (!path) return BKR_FALSE;
#ifdef _WIN32
    DWORD attr = GetFileAttributesA(path);
    if (attr == INVALID_FILE_ATTRIBUTES) return BKR_FALSE;
    return (attr & FILE_ATTRIBUTE_DIRECTORY) ? BKR_TRUE : BKR_FALSE;
#else
    struct stat st;
    if (stat(path, &st) != 0) return BKR_FALSE;
    return S_ISDIR(st.st_mode) ? BKR_TRUE : BKR_FALSE;
#endif
}

static inline bkr_i64 file_read(bkr_str path) {
    if (!path) return bkr_result_err((bkr_i64)(intptr_t)"null path");
    bkr_str content = bkr_raw_file_read(path);
    if (!content || (*content == '\0' && !path_exists(path))) {
        return bkr_result_err((bkr_i64)(intptr_t)"failed to read file");
    }
    return bkr_result_ok((bkr_i64)(intptr_t)content);
}

static inline bkr_i64 file_write(bkr_str path, bkr_str content) {
    if (!path || !content) return bkr_result_err((bkr_i64)(intptr_t)"null argument");
    bkr_bool ok = bkr_raw_file_write(path, content);
    if (!ok) return bkr_result_err((bkr_i64)(intptr_t)"failed to write file");
    return bkr_result_ok((bkr_i64)strlen(content));
}

static inline bkr_i64 file_size(bkr_str path) {
    if (!path) return bkr_result_err((bkr_i64)(intptr_t)"null path");
    FILE* f = fopen(path, "rb");
    if (!f) return bkr_result_err((bkr_i64)(intptr_t)"file not found");
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    return bkr_result_ok((bkr_i64)size);
}

static inline bkr_i64 file_remove(bkr_str path) {
    if (!path) return bkr_result_err((bkr_i64)(intptr_t)"null path");
    if (remove(path) == 0) return bkr_result_ok(1);
    return bkr_result_err((bkr_i64)(intptr_t)"failed to remove file");
}

static inline bkr_i64 file_read_bytes(bkr_str path) {
    if (!path) return bkr_result_err((bkr_i64)(intptr_t)"null path");
    FILE* f = fopen(path, "rb");
    if (!f) return bkr_result_err((bkr_i64)(intptr_t)"failed to open file");
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    bkr_i64 handle = bytes_new(size > 0 ? (bkr_i64)size : 8);
    BkrBytes* b = (BkrBytes*)(intptr_t)handle;
    if (size > 0 && b && b->data) {
        fread(b->data, 1, (size_t)size, f);
        b->len = (bkr_i64)size;
    }
    fclose(f);
    return bkr_result_ok(handle);
}

static inline bkr_i64 file_write_bytes(bkr_str path, bkr_i64 handle) {
    if (!path) return bkr_result_err((bkr_i64)(intptr_t)"null path");
    BkrBytes* b = (BkrBytes*)(intptr_t)handle;
    if (!b) return bkr_result_err((bkr_i64)(intptr_t)"null bytes");
    FILE* f = fopen(path, "wb");
    if (!f) return bkr_result_err((bkr_i64)(intptr_t)"failed to open file");
    if (b->len > 0 && b->data) {
        fwrite(b->data, 1, (size_t)b->len, f);
    }
    fclose(f);
    return bkr_result_ok(b->len);
}

static inline bkr_i64 dir_create(bkr_str path) {
    if (!path) return bkr_result_err((bkr_i64)(intptr_t)"null path");
#ifdef _WIN32
    if (CreateDirectoryA(path, NULL) || GetLastError() == ERROR_ALREADY_EXISTS) {
        return bkr_result_ok(1);
    }
#else
    if (mkdir(path, 0755) == 0 || errno == EEXIST) {
        return bkr_result_ok(1);
    }
#endif
    return bkr_result_err((bkr_i64)(intptr_t)"failed to create directory");
}

static inline bkr_i64 dir_remove(bkr_str path) {
    if (!path) return bkr_result_err((bkr_i64)(intptr_t)"null path");
#ifdef _WIN32
    if (RemoveDirectoryA(path)) {
        return bkr_result_ok(1);
    }
#else
    if (rmdir(path) == 0) {
        return bkr_result_ok(1);
    }
#endif
    return bkr_result_err((bkr_i64)(intptr_t)"failed to remove directory");
}

/* ============================================
 * Process Arguments
 * ============================================ */

static int bkr_argc = 0;
static char** bkr_argv = NULL;

static inline void bkr_init_args(int argc, char** argv) {
    bkr_argc = argc;
    bkr_argv = argv;
}

static inline bkr_i64 bkr_args_count(void) {
    return (bkr_i64)bkr_argc;
}

static inline bkr_str bkr_arg_at(bkr_i64 index) {
    if (index >= 0 && index < (bkr_i64)bkr_argc && bkr_argv != NULL && bkr_argv[index] != NULL) {
        return bkr_argv[index];
    }
    return "";
}

/* ============================================
 * Recoverable Error Stdlib Builtins (C-007)
 * ============================================ */

static inline bkr_i64 bkr_option_some(bkr_i64 val) {
    return ((val << 1) | 1);
}

static inline bkr_i64 bkr_hashmap_get_opt(bkr_i64 handle, bkr_i64 key) {
    BkrHashMap* m = (BkrHashMap*)(intptr_t)handle;
    if (!m || !m->buckets) return 0;
    bkr_i64 idx = bkr_hashmap_key_hash(m->key_type, key) % m->size;
    BkrHashEntry* e = m->buckets[idx];
    while (e) {
        if (bkr_hashmap_key_eq(m->key_type, e->key, key)) return bkr_option_some(e->value);
        e = e->next;
    }
    return 0;
}

static inline bkr_i64 bkr_vec_get_opt(bkr_i64 handle, bkr_i64 index) {
    BkrVec* v = (BkrVec*)(intptr_t)handle;
    if (!v || index < 0 || index >= v->len) return 0;
    return bkr_option_some(v->data[index]);
}

static inline bkr_i64 bkr_vec_pop_opt(bkr_i64 handle) {
    BkrVec* v = (BkrVec*)(intptr_t)handle;
    if (!v || v->len <= 0) return 0;
    v->len--;
    return bkr_option_some(v->data[v->len]);
}

static inline bkr_i64 vec_find(bkr_i64 handle, bkr_i64 fn_ptr) {
    BkrVec* v = (BkrVec*)(intptr_t)handle;
    if (!v || !v->data || fn_ptr == 0) return 0;
    bkr_i64 (*f)(bkr_i64) = (bkr_i64 (*)(bkr_i64))(intptr_t)fn_ptr;
    for (bkr_i64 i = 0; i < v->len; i++) {
        if (f(v->data[i])) {
            return bkr_option_some(v->data[i]);
        }
    }
    return 0;
}

static inline bkr_i64 bkr_read_file_result(bkr_str path) {
    return file_read(path);
}

static inline bkr_i64 bkr_write_file_result(bkr_str path, bkr_str content) {
    return file_write(path, content);
}

static inline bkr_i64 bkr_parse_int_result(bkr_str s) {
    if (!s || *s == '\0') {
        return bkr_result_err((bkr_i64)(intptr_t)"empty integer string");
    }
    char* endptr = NULL;
    long long val = strtoll(s, &endptr, 10);
    if (endptr == s || *endptr != '\0') {
        return bkr_result_err((bkr_i64)(intptr_t)"invalid integer format");
    }
    return bkr_result_ok((bkr_i64)val);
}

static inline bkr_i64 hashmap_get_opt(bkr_i64 handle, bkr_i64 key) { return bkr_hashmap_get_opt(handle, key); }
static inline bkr_i64 vec_get_opt(bkr_i64 handle, bkr_i64 index) { return bkr_vec_get_opt(handle, index); }
static inline bkr_i64 vec_pop_opt(bkr_i64 handle) { return bkr_vec_pop_opt(handle); }
static inline bkr_i64 bkr_vec_find(bkr_i64 handle, bkr_i64 fn_ptr) { return vec_find(handle, fn_ptr); }
static inline bkr_bool bkr_vec_contains(bkr_i64 handle, bkr_i64 item) { return vec_contains(handle, item); }
static inline bkr_bool bkr_vec_is_empty(bkr_i64 handle) { return vec_is_empty(handle); }
static inline bkr_i64 bkr_vec_clone(bkr_i64 handle) { return vec_clone(handle); }
static inline bkr_bool bkr_vec_reverse(bkr_i64 handle) { return vec_reverse(handle); }
static inline bkr_bool bkr_hashmap_is_empty(bkr_i64 handle) { return hashmap_is_empty(handle); }
static inline bkr_i64 bkr_hashmap_values(bkr_i64 handle) { return hashmap_values(handle); }
static inline bkr_i64 bkr_vec_map(bkr_i64 handle, bkr_i64 fn_ptr) { return vec_map(handle, fn_ptr); }
static inline bkr_i64 bkr_vec_filter(bkr_i64 handle, bkr_i64 fn_ptr) { return vec_filter(handle, fn_ptr); }
static inline bkr_i64 bkr_vec_fold(bkr_i64 handle, bkr_i64 init, bkr_i64 fn_ptr) { return vec_fold(handle, init, fn_ptr); }
static inline bkr_i64 read_file_result(bkr_str path) { return bkr_read_file_result(path); }
static inline bkr_i64 write_file_result(bkr_str path, bkr_str content) { return bkr_write_file_result(path, content); }
static inline bkr_i64 parse_int_result(bkr_str s) { return bkr_parse_int_result(s); }

static inline bkr_i64 bkr_str_index_of(bkr_str s, bkr_str needle) {
    if (!s || !needle) return -1;
    const char* found = strstr(s, needle);
    if (!found) return -1;
    return (bkr_i64)(found - s);
}

static inline bkr_str bkr_str_replace(bkr_str s, bkr_str from, bkr_str to) {
    if (!s) return "";
    if (!from || from[0] == '\0') return s;
    if (!to) to = "";
    size_t from_len = strlen(from);
    size_t to_len = strlen(to);
    size_t count = 0;
    const char* p = s;
    while ((p = strstr(p, from)) != NULL) {
        count++;
        p += from_len;
    }
    if (count == 0) return s;
    size_t s_len = strlen(s);
    size_t new_len = s_len + count * to_len - count * from_len;
    char* result = (char*)bkr_arena_alloc(new_len + 1, 1);
    if (!result) return "";
    char* dst = result;
    p = s;
    while (1) {
        const char* next = strstr(p, from);
        if (!next) {
            strcpy(dst, p);
            break;
        }
        size_t part_len = (size_t)(next - p);
        memcpy(dst, p, part_len);
        dst += part_len;
        memcpy(dst, to, to_len);
        dst += to_len;
        p = next + from_len;
    }
    result[new_len] = '\0';
    return result;
}

static inline bkr_i64 bkr_str_split(bkr_str s, bkr_str delim) {
    bkr_i64 vec = vec_new();
    if (!s) return vec;
    if (!delim || delim[0] == '\0') {
        size_t len = strlen(s);
        for (size_t i = 0; i < len; i++) {
            char* part = (char*)bkr_arena_alloc(2, 1);
            if (part) {
                part[0] = s[i];
                part[1] = '\0';
                vec_push(vec, (bkr_i64)(intptr_t)part);
            }
        }
        return vec;
    }
    size_t delim_len = strlen(delim);
    const char* cur = s;
    const char* next;
    while ((next = strstr(cur, delim)) != NULL) {
        size_t part_len = (size_t)(next - cur);
        char* part = (char*)bkr_arena_alloc(part_len + 1, 1);
        if (part) {
            memcpy(part, cur, part_len);
            part[part_len] = '\0';
            vec_push(vec, (bkr_i64)(intptr_t)part);
        }
        cur = next + delim_len;
    }
    size_t rem_len = strlen(cur);
    char* part = (char*)bkr_arena_alloc(rem_len + 1, 1);
    if (part) {
        memcpy(part, cur, rem_len);
        part[rem_len] = '\0';
        vec_push(vec, (bkr_i64)(intptr_t)part);
    }
    return vec;
}

static inline bkr_str bkr_str_to_upper(bkr_str s) {
    if (!s) return "";
    size_t len = strlen(s);
    char* result = (char*)bkr_arena_alloc(len + 1, 1);
    if (!result) return "";
    for (size_t i = 0; i < len; i++) {
        char c = s[i];
        if (c >= 'a' && c <= 'z') c = (char)(c - ('a' - 'A'));
        result[i] = c;
    }
    result[len] = '\0';
    return result;
}

static inline bkr_str bkr_str_to_lower(bkr_str s) {
    if (!s) return "";
    size_t len = strlen(s);
    char* result = (char*)bkr_arena_alloc(len + 1, 1);
    if (!result) return "";
    for (size_t i = 0; i < len; i++) {
        char c = s[i];
        if (c >= 'A' && c <= 'Z') c = (char)(c + ('a' - 'A'));
        result[i] = c;
    }
    result[len] = '\0';
    return result;
}

static inline bkr_str bkr_str_repeat(bkr_str s, bkr_i64 count) {
    if (!s || count <= 0) return "";
    size_t len = strlen(s);
    if (len == 0) return "";
    size_t total = len * (size_t)count;
    char* result = (char*)bkr_arena_alloc(total + 1, 1);
    if (!result) return "";
    for (bkr_i64 i = 0; i < count; i++) {
        memcpy(result + (size_t)i * len, s, len);
    }
    result[total] = '\0';
    return result;
}

static inline bkr_str bkr_path_join(bkr_str a, bkr_str b) {
    if (!a || a[0] == '\0') return b ? b : "";
    if (!b || b[0] == '\0') return a;
    size_t len_a = strlen(a);
    while (len_a > 0 && (a[len_a - 1] == '/' || a[len_a - 1] == '\\')) {
        len_a--;
    }
    const char* start_b = b;
    while (*start_b == '/' || *start_b == '\\') {
        start_b++;
    }
    size_t len_b = strlen(start_b);
    if (len_a == 0) return (char*)start_b;
    if (len_b == 0) {
        char* res = (char*)bkr_arena_alloc(len_a + 1, 1);
        if (!res) return "";
        memcpy(res, a, len_a);
        res[len_a] = '\0';
        return res;
    }
    char* res = (char*)bkr_arena_alloc(len_a + 1 + len_b + 1, 1);
    if (!res) return "";
    memcpy(res, a, len_a);
    res[len_a] = '/';
    memcpy(res + len_a + 1, start_b, len_b);
    res[len_a + 1 + len_b] = '\0';
    return res;
}

static inline bkr_str bkr_path_dir(bkr_str path) {
    if (!path) return "";
    const char* last_slash = NULL;
    for (const char* p = path; *p; p++) {
        if (*p == '/' || *p == '\\') last_slash = p;
    }
    if (!last_slash) return "";
    size_t len = (size_t)(last_slash - path);
    char* res = (char*)bkr_arena_alloc(len + 1, 1);
    if (!res) return "";
    memcpy(res, path, len);
    res[len] = '\0';
    return res;
}

static inline bkr_str bkr_path_base(bkr_str path) {
    if (!path) return "";
    const char* last_slash = NULL;
    for (const char* p = path; *p; p++) {
        if (*p == '/' || *p == '\\') last_slash = p;
    }
    if (!last_slash) return path;
    return (char*)(last_slash + 1);
}

static inline bkr_str bkr_path_ext(bkr_str path) {
    if (!path) return "";
    bkr_str base = bkr_path_base(path);
    const char* last_dot = strrchr(base, '.');
    if (!last_dot || last_dot == base || *(last_dot + 1) == '\0') return "";
    return (char*)(last_dot + 1);
}

static inline bkr_bool bkr_path_is_abs(bkr_str path) {
    if (!path || path[0] == '\0') return 0;
    if (path[0] == '/' || path[0] == '\\') return 1;
    if (path[1] == ':') return 1;
    return 0;
}

static inline bkr_i64 bkr_env_var(bkr_str key) {
    if (!key) return bkr_result_err((bkr_i64)(intptr_t)"null key");
    const char* val = getenv(key);
    if (!val) {
        return bkr_result_err((bkr_i64)(intptr_t)"environment variable not found");
    }
    return bkr_result_ok((bkr_i64)(intptr_t)val);
}

static inline bkr_i64 bkr_env_get(bkr_str key) {
    if (!key) return 0;
    const char* val = getenv(key);
    if (!val) return 0;
    return bkr_option_some((bkr_i64)(intptr_t)val);
}

static inline bkr_bool bkr_env_set(bkr_str key, bkr_str val) {
    if (!key || !val) return 0;
#if defined(_WIN32)
    return _putenv_s(key, val) == 0 ? 1 : 0;
#else
    return setenv(key, val, 1) == 0 ? 1 : 0;
#endif
}

static inline bkr_bool bkr_env_has(bkr_str key) {
    if (!key) return 0;
    return getenv(key) != NULL ? 1 : 0;
}

static inline bkr_i64 bkr_time_now_ms(void) {
#if defined(_WIN32)
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    ULARGE_INTEGER uli;
    uli.LowPart = ft.dwLowDateTime;
    uli.HighPart = ft.dwHighDateTime;
    return (bkr_i64)((uli.QuadPart - 116444736000000000ULL) / 10000ULL);
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (bkr_i64)tv.tv_sec * 1000 + (bkr_i64)(tv.tv_usec / 1000);
#endif
}

static inline bkr_i64 bkr_time_now_unix(void) {
    return (bkr_i64)time(NULL);
}

static inline bkr_i64 str_index_of(bkr_str s, bkr_str needle) { return bkr_str_index_of(s, needle); }
static inline bkr_str str_replace(bkr_str s, bkr_str from, bkr_str to) { return bkr_str_replace(s, from, to); }
static inline bkr_i64 str_split(bkr_str s, bkr_str delim) { return bkr_str_split(s, delim); }
static inline bkr_str str_to_upper(bkr_str s) { return bkr_str_to_upper(s); }
static inline bkr_str str_to_lower(bkr_str s) { return bkr_str_to_lower(s); }
static inline bkr_str str_repeat(bkr_str s, bkr_i64 count) { return bkr_str_repeat(s, count); }
static inline bkr_str path_join(bkr_str a, bkr_str b) { return bkr_path_join(a, b); }
static inline bkr_str path_dir(bkr_str path) { return bkr_path_dir(path); }
static inline bkr_str path_base(bkr_str path) { return bkr_path_base(path); }
static inline bkr_str path_ext(bkr_str path) { return bkr_path_ext(path); }
static inline bkr_bool path_is_abs(bkr_str path) { return bkr_path_is_abs(path); }
static inline bkr_i64 env_var(bkr_str key) { return bkr_env_var(key); }
static inline bkr_i64 env_get(bkr_str key) { return bkr_env_get(key); }
static inline bkr_bool env_set(bkr_str key, bkr_str val) { return bkr_env_set(key, val); }
static inline bkr_bool env_has(bkr_str key) { return bkr_env_has(key); }
static inline bkr_i64 time_now_ms(void) { return bkr_time_now_ms(); }
static inline bkr_i64 time_now_unix(void) { return bkr_time_now_unix(); }

#endif /* BUNKER_RUNTIME_H */
