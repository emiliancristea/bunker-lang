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

static inline void vec_push(bkr_i64 handle, bkr_i64 value) {
    BkrVec* v = (BkrVec*)(intptr_t)handle;
    if (v->len >= v->cap) {
        v->cap *= 2;
        v->data = (bkr_i64*)realloc(v->data, sizeof(bkr_i64) * v->cap);
    }
    v->data[v->len++] = value;
}

static inline bkr_i64 vec_get(bkr_i64 handle, bkr_i64 index) {
    BkrVec* v = (BkrVec*)(intptr_t)handle;
    return v->data[index];
}

static inline void vec_set(bkr_i64 handle, bkr_i64 index, bkr_i64 value) {
    BkrVec* v = (BkrVec*)(intptr_t)handle;
    v->data[index] = value;
}

static inline bkr_i64 vec_len(bkr_i64 handle) {
    BkrVec* v = (BkrVec*)(intptr_t)handle;
    return v->len;
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
    bkr_str key;
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

static inline bkr_i64 bkr_hash(bkr_str key) {
    bkr_i64 h = 0;
    while (*key) {
        h = h * 31 + *key++;
    }
    return h;
}

static inline void hashmap_insert(bkr_i64 handle, bkr_str key, bkr_i64 value) {
    BkrHashMap* m = (BkrHashMap*)(intptr_t)handle;
    bkr_i64 idx = bkr_hash(key) % m->size;
    if (idx < 0) idx = -idx;

    BkrHashEntry* entry = (BkrHashEntry*)malloc(sizeof(BkrHashEntry));
    entry->key = key;
    entry->value = value;
    entry->next = m->buckets[idx];
    m->buckets[idx] = entry;
    m->count++;
}

static inline bkr_i64 hashmap_get(bkr_i64 handle, bkr_str key) {
    BkrHashMap* m = (BkrHashMap*)(intptr_t)handle;
    bkr_i64 idx = bkr_hash(key) % m->size;
    if (idx < 0) idx = -idx;

    BkrHashEntry* e = m->buckets[idx];
    while (e) {
        if (strcmp(e->key, key) == 0) return e->value;
        e = e->next;
    }
    return 0;
}

static inline bkr_bool hashmap_contains(bkr_i64 handle, bkr_str key) {
    BkrHashMap* m = (BkrHashMap*)(intptr_t)handle;
    bkr_i64 idx = bkr_hash(key) % m->size;
    if (idx < 0) idx = -idx;

    BkrHashEntry* e = m->buckets[idx];
    while (e) {
        if (strcmp(e->key, key) == 0) return BKR_TRUE;
        e = e->next;
    }
    return BKR_FALSE;
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

#endif /* BUNKER_RUNTIME_H */
