#ifndef _UTIL_H
#define _UTIL_H

#include <assert.h>
#include <stdio.h>



// TODO: make this act like an expression
#define PANIC(msg) do {                                                          \
    fprintf(stderr, "Panicked at (%s: %s: %d)\n", __FILE__, __func__, __LINE__); \
    fprintf(stderr, "%s\n", msg);                                                \
    abort();                                                                     \
} while (0)

#define ARRAY_LEN(xs) (sizeof(xs) / sizeof *(xs))
#define NON_NULL(ptr) assert((ptr) != NULL)
#define UNREACHABLE PANIC("unreachable")
#define TODO(msg) PANIC("TODO: " msg)
#define UNUSED __attribute__((unused))
#define DISCARD(value) (void) (value); assert(0)

#define PRINT(x) do {               \
    const char *fmt = _Generic((x), \
        char:   "%c",               \
        int:    "%d",               \
        float:  "%f",               \
        size_t: "%lu",              \
        char*:  "%s",               \
        void*:  "%p"                \
    );                              \
    printf(fmt, x);                 \
    printf("\n");                   \
} while (0)



#endif // _UTIL_H
