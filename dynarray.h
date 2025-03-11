#ifndef _DYNARRAY_H
#define _DYNARRAY_H

#include <stdlib.h>

/* Declaration */

#define DYNARRAY_DECL(Structname, prefix, T)              \
                                                          \
typedef struct {                                          \
    size_t cap, size;                                     \
    T *items;                                             \
} Structname;                                             \
                                                          \
void prefix##_init    (Structname *d, size_t cap);        \
void prefix##_push    (Structname *d, T item);            \
void prefix##_destroy (Structname *d);                    \

/* ----------- */

/* Implementation */

#define DYNARRAY_IMPL(Structname, prefix, T)              \
                                                          \
void prefix##_init(Structname *d, size_t cap) {           \
    *d = (Structname) {                                   \
        .items = NULL,                                    \
        .cap   = cap,                                     \
        .size  = 0,                                       \
    };                                                    \
    d->items = malloc(d->cap * sizeof(T));                \
}                                                         \
                                                          \
void prefix##_push(Structname *d, T item) {               \
    if (d->size == d->cap) {                              \
        d->cap *= 2;                                      \
        d->items = realloc(d->items, d->cap * sizeof(T)); \
    }                                                     \
                                                          \
    d->items[d->size++] = item;                           \
}                                                         \
                                                          \
void prefix##_destroy(Structname *d) {                    \
    free(d->items);                                       \
    d->items = NULL;                                      \
}                                                         \

/* -------------- */

#endif // _DYNARRAY_H
