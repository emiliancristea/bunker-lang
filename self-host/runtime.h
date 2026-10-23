/* Bunker Runtime Library for C Backend
 * This provides the runtime support for Bunker programs compiled to C
 */

#ifndef BUNKER_RUNTIME_H
#define BUNKER_RUNTIME_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
} BkrHashMap;

static inline bkr_i64 bkr_hash(bkr_i64 key) {
    bkr_i64 h = key;
    if (h < 0) h = -h;
    return h;
}

static inline bkr_i64 hashmap_new(void) {
    BkrHashMap* m = (BkrHashMap*)bkr_arena_alloc(sizeof(BkrHashMap), sizeof(void*));
    if (!m) return 0;
    m->size = 64;
    m->count = 0;
    m->buckets = (BkrHashEntry**)bkr_arena_alloc(sizeof(BkrHashEntry*) * (size_t)m->size, sizeof(void*));
    if (m->buckets) {
        memset(m->buckets, 0, sizeof(BkrHashEntry*) * (size_t)m->size);
    }
    return (bkr_i64)(intptr_t)m;
}

static inline bkr_bool hashmap_insert(bkr_i64 handle, bkr_i64 key, bkr_i64 value) {
    BkrHashMap* m = (BkrHashMap*)(intptr_t)handle;
    if (!m || !m->buckets) return BKR_FALSE;
    bkr_i64 idx = bkr_hash(key) % m->size;

    BkrHashEntry* existing = m->buckets[idx];
    while (existing) {
        if (existing->key == key) {
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

static inline bkr_i64 hashmap_get(bkr_i64 handle, bkr_i64 key) {
    BkrHashMap* m = (BkrHashMap*)(intptr_t)handle;
    if (!m || !m->buckets) return 0;
    bkr_i64 idx = bkr_hash(key) % m->size;

    BkrHashEntry* e = m->buckets[idx];
    while (e) {
        if (e->key == key) return e->value;
        e = e->next;
    }
    return 0;
}

static inline bkr_bool hashmap_contains(bkr_i64 handle, bkr_i64 key) {
    BkrHashMap* m = (BkrHashMap*)(intptr_t)handle;
    if (!m || !m->buckets) return BKR_FALSE;
    bkr_i64 idx = bkr_hash(key) % m->size;

    BkrHashEntry* e = m->buckets[idx];
    while (e) {
        if (e->key == key) return BKR_TRUE;
        e = e->next;
    }
    return BKR_FALSE;
}

static inline bkr_bool hashmap_remove(bkr_i64 handle, bkr_i64 key) {
    BkrHashMap* m = (BkrHashMap*)(intptr_t)handle;
    if (!m || !m->buckets) return BKR_FALSE;
    bkr_i64 idx = bkr_hash(key) % m->size;

    BkrHashEntry* prev = NULL;
    BkrHashEntry* e = m->buckets[idx];
    while (e) {
        if (e->key == key) {
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

/* ============================================
 * File I/O
 * ============================================ */

static inline bkr_str file_read(bkr_str path) {
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

static inline bkr_bool file_write(bkr_str path, bkr_str content) {
    FILE* f = fopen(path, "wb");
    if (!f) return BKR_FALSE;
    fputs(content, f);
    fclose(f);
    return BKR_TRUE;
}

static inline bkr_str read_file(bkr_str path) {
    return file_read(path);
}

static inline bkr_bool write_file(bkr_str path, bkr_str content) {
    return file_write(path, content);
}

static inline bkr_bool file_exists(bkr_str path) {
    FILE* f = fopen(path, "rb");
    if (!f) return BKR_FALSE;
    fclose(f);
    return BKR_TRUE;
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
    bkr_i64 idx = bkr_hash(key) % m->size;
    BkrHashEntry* e = m->buckets[idx];
    while (e) {
        if (e->key == key) return bkr_option_some(e->value);
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

static inline bkr_i64 bkr_read_file_result(bkr_str path) {
    bkr_str content = bkr_read_file(path);
    if (!content) {
        return bkr_result_err((bkr_i64)(intptr_t)"failed to read file");
    }
    return bkr_result_ok((bkr_i64)(intptr_t)content);
}

static inline bkr_i64 bkr_write_file_result(bkr_str path, bkr_str content) {
    bkr_bool ok = bkr_write_file(path, content);
    if (!ok) {
        return bkr_result_err((bkr_i64)(intptr_t)"failed to write file");
    }
    return bkr_result_ok(1);
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
static inline bkr_i64 read_file_result(bkr_str path) { return bkr_read_file_result(path); }
static inline bkr_i64 write_file_result(bkr_str path, bkr_str content) { return bkr_write_file_result(path, content); }
static inline bkr_i64 parse_int_result(bkr_str s) { return bkr_parse_int_result(s); }

#endif /* BUNKER_RUNTIME_H */
