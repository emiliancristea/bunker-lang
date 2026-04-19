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
 * Vector (Dynamic Array)
 * ============================================ */

typedef struct {
    bkr_i64* data;
    bkr_i64 len;
    bkr_i64 cap;
} BkrVec;

static inline bkr_i64 vec_new(void) {
    BkrVec* v = (BkrVec*)malloc(sizeof(BkrVec));
    v->data = (bkr_i64*)malloc(sizeof(bkr_i64) * 8);
    v->len = 0;
    v->cap = 8;
    return (bkr_i64)(intptr_t)v;
}

static inline bkr_bool vec_push(bkr_i64 handle, bkr_i64 value) {
    BkrVec* v = (BkrVec*)(intptr_t)handle;
    if (!v) return BKR_FALSE;
    if (v->len >= v->cap) {
        v->cap *= 2;
        v->data = (bkr_i64*)realloc(v->data, sizeof(bkr_i64) * v->cap);
        if (!v->data) return BKR_FALSE;
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
    BkrVec* v = (BkrVec*)(intptr_t)handle;
    free(v->data);
    free(v);
}

/* ============================================
 * String Operations
 * ============================================ */

static inline bkr_i64 bkr_len(bkr_str s) {
    return (bkr_i64)strlen(s);
}

static inline bkr_str char_at(bkr_str s, bkr_i64 index) {
    static char buf[2];
    buf[0] = s[index];
    buf[1] = '\0';
    return buf;
}

static inline bkr_i64 char_code(bkr_str s) {
    return (bkr_i64)(unsigned char)s[0];
}

static inline bkr_i64 char_code_at(bkr_str s, bkr_i64 index) {
    if (s == NULL || index < 0) {
        return 0;
    }
    bkr_i64 len = (bkr_i64)strlen(s);
    if (index >= len) {
        return 0;
    }
    return (bkr_i64)(unsigned char)s[index];
}

static inline bkr_str substring(bkr_str s, bkr_i64 start, bkr_i64 end) {
    bkr_i64 len = end - start;
    char* result = (char*)malloc(len + 1);
    memcpy(result, s + start, len);
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
    bkr_i64 s_len = (bkr_i64)strlen(s);
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
    bkr_i64 end = (bkr_i64)strlen(s);
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
    char* result = (char*)malloc(32);
    if (!result) return "";
    snprintf(result, 32, "%lld", (long long)value);
    return result;
}

static inline bkr_str from_char_code(bkr_i64 code) {
    char* result = (char*)malloc(2);
    if (!result) return "";
    result[0] = (char)(unsigned char)code;
    result[1] = '\0';
    return result;
}

static inline bkr_str bkr_str_concat(bkr_str a, bkr_str b) {
    bkr_i64 len_a = strlen(a);
    bkr_i64 len_b = strlen(b);
    char* result = (char*)malloc(len_a + len_b + 1);
    memcpy(result, a, len_a);
    memcpy(result + len_a, b, len_b + 1);
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
    BkrResult* r = (BkrResult*)malloc(sizeof(BkrResult));
    r->tag = 0;
    r->value = value;
    return (bkr_i64)(intptr_t)r;
}

static inline bkr_i64 bkr_result_err(bkr_i64 value) {
    BkrResult* r = (BkrResult*)malloc(sizeof(BkrResult));
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
 * I/O Operations
 * ============================================ */

static inline void bkr_print(bkr_str s) {
    printf("%s", s);
}

static inline void bkr_println(bkr_str s) {
    printf("%s\n", s);
}

static inline void bkr_print_i64(bkr_i64 n) {
    printf("%lld", (long long)n);
}

/* ============================================
 * HashMap (Simple Implementation)
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

static inline bkr_i64 hashmap_new(void) {
    BkrHashMap* m = (BkrHashMap*)malloc(sizeof(BkrHashMap));
    m->size = 64;
    m->count = 0;
    m->buckets = (BkrHashEntry**)calloc(m->size, sizeof(BkrHashEntry*));
    return (bkr_i64)(intptr_t)m;
}

static inline bkr_i64 bkr_hash(bkr_i64 key) {
    bkr_i64 h = key;
    if (h < 0) h = -h;
    return h;
}

static inline bkr_bool hashmap_insert(bkr_i64 handle, bkr_i64 key, bkr_i64 value) {
    BkrHashMap* m = (BkrHashMap*)(intptr_t)handle;
    if (!m) return BKR_FALSE;
    bkr_i64 idx = bkr_hash(key) % m->size;

    BkrHashEntry* existing = m->buckets[idx];
    while (existing) {
        if (existing->key == key) {
            existing->value = value;
            return BKR_TRUE;
        }
        existing = existing->next;
    }

    BkrHashEntry* entry = (BkrHashEntry*)malloc(sizeof(BkrHashEntry));
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
    if (!m) return 0;
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
    if (!m) return BKR_FALSE;
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
    if (!m) return BKR_FALSE;
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
            free(e);
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
    if (!m) return keys;

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
    char* buf = (char*)malloc(size + 1);
    fread(buf, 1, size, f);
    buf[size] = '\0';
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

#endif /* BUNKER_RUNTIME_H */
