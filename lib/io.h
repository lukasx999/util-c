#ifndef _IO_H
#define _IO_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <alloca.h>

#include <sys/types.h>
#include <sys/stat.h>

#include "util.h"



// returns the size of the file specified by `path` in bytes
// returns -1 in case of failure
static inline
ssize_t get_file_size(const char *path) {

    NON_NULL(path);

    struct stat statbuf = { 0 };
    int err = stat(path, &statbuf);
    if (err == -1) return -1;

    return statbuf.st_size;
}

// reads the file from `path` into a nul-terminated buffer on the heap.
// the returned pointer must be free'd.
static inline
char *read_entire_file(const char *path) {

    NON_NULL(path);

    ssize_t size = get_file_size(path);
    if (size == -1) return NULL;

    FILE *file = fopen(path, "r");
    if (file == NULL) return NULL;

    // Allocate one extra byte for nul-termination
    char *buf = malloc((size + 1) * sizeof(char));
    if (buf == NULL) return NULL;
    memset(buf, '\0', (size + 1) * sizeof(char));

    size_t bytes_read = fread(buf, sizeof(char), size, file);
    if (bytes_read < (size_t) size) {
        if (ferror(file) < 0) return NULL;
        if (feof(file) < 0) UNREACHABLE;
    }

    if (fclose(file) == EOF) return NULL;
    return buf;
}

static inline
int get_substring_count(const char *str, const char *query) {

    int count = 0;
    while ((str = strstr(str, query)) != NULL) {
        count++;
        str++;
    }

    return count;
}

struct StringArray {
    char **strings;
    size_t bufsize; // the size of each string buffer
    size_t count; // the count of strings in the array
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
        .strings   = tokens,
        .count   = count,
        .bufsize = bufsize,
    };
}

static inline
void free_stringarray(struct StringArray *tokens) {

    NON_NULL(tokens);

    for (size_t i=0; i < 3; ++i)
        free(tokens->strings[i]);
    free(tokens->strings);
}

static inline
struct StringArray read_entire_file_lines(const char *path) {

    NON_NULL(path);

    return tokenize_string(path, "\n");
}


#endif // _IO_H
