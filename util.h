#ifndef _UTIL_H
#define _UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <alloca.h>

#include <sys/stat.h>



#define ARRAY_LEN(xs) (sizeof(xs) / sizeof *(xs))
#define NON_NULL(ptr) assert((ptr) != NULL)
#define UNREACHABLE assert(!"unreachable");
#define TODO(msg) assert(!"TODO: " msg);
#define UNUSED __attribute__((unused))
#define DISCARD(x) (void) (x); assert(0)



// reads the file from `path` into a nul-terminated buffer on the heap.
// the returned pointer must be free'd.
static inline char *read_entire_file(const char *path) {

    NON_NULL(path);

    FILE *file = fopen(path, "r");
    if (file == NULL) return NULL;

    struct stat statbuf = { 0 };
    int err = stat(path, &statbuf);
    if (err == -1) return NULL;

    size_t size = statbuf.st_size;

    // Allocate one extra byte for nul-termination
    char *buf = malloc((size + 1) * sizeof(char));
    if (buf == NULL) return NULL;
    memset(buf, '\0', (size + 1) * sizeof(char));

    size_t bytes_read = fread(buf, sizeof(char), size, file);
    if (bytes_read < size) {
        if (ferror(file) < 0) return NULL;
        if (feof(file) < 0) UNREACHABLE;
    }

    if (fclose(file) == EOF) return NULL;
    return buf;
}

static inline int get_substring_count(const char *str, const char *query) {

    int count = 0;
    while ((str = strstr(str, query)) != NULL) {
        count++;
        str++;
    }

    return count;
}

struct StringArray {
    char **items;
    size_t bufsize;
    size_t count;
};

static inline
struct StringArray tokenize_string(const char *str, const char *delim) {

    NON_NULL(str);
    NON_NULL(delim);

    // eg: "foo bar": 1 delim -> 2 tokens
    int count = get_substring_count(str, delim) + 1;

    char **tokens = malloc(count * sizeof(char*));
    NON_NULL(tokens);
    size_t i = 0;

    size_t bufsize = strlen(str) + 1; // TODO: get size of largest token

    for (size_t i=0; i < (size_t) count; ++i) {
        tokens[i] = malloc(bufsize * sizeof(char));
        NON_NULL(tokens[i]);
    }

    char *buf = alloca((strlen(str) + 1) * sizeof(char));
    NON_NULL(buf);
    strncpy(buf, str, strlen(str) + 1);

    char *tok = strtok(buf, delim);
    strncpy(tokens[i++], tok, bufsize);

    while ((tok = strtok(NULL, delim)) != NULL) {
        strncpy(tokens[i++], tok, bufsize);
    }

    return (struct StringArray) {
        .items   = tokens,
        .count   = count,
        .bufsize = bufsize,
    };
}

static inline void free_tokens(struct StringArray *tokens) {

    NON_NULL(tokens);

    for (size_t i=0; i < 3; ++i)
        free(tokens->items[i]);
    free(tokens->items);
}

static inline
struct StringArray read_entire_file_lines(const char *path) {

    NON_NULL(path);

    return tokenize_string(path, "\n");
}



#endif // _UTIL_H
