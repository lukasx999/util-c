#ifndef _UTIL_H
#define _UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <sys/stat.h>



#define NONNULL(ptr) assert((ptr) != NULL)
#define UNREACHABLE assert(!"unreachable");
#define TODO(msg) assert(!"TODO: " msg);
#define UNUSED __attribute__((unused))
#define DISCARD(x) (void) (x); assert(0)



// reads the file from `path` into a nul-terminated buffer on the heap.
// the returned pointer must be free'd.
static inline char *read_entire_file(const char *path) {
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




UNUSED static inline char **read_entire_file_lines(UNUSED const char *path) {
    TODO()
}

UNUSED static inline char *tokenize_string(UNUSED char *str, UNUSED const char *delim) {
    TODO()
}


#endif // _UTIL_H
