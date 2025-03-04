#ifndef _DYNARRAY_H
#define _DYNARRAY_H

#include <stdlib.h>

/* Declaration */

#define DYNARRAY_DECL(structname, prefix, T)           \
                                                       \
typedef struct {                                       \
    size_t cap, size;                                  \
    T *items;                                          \
} structname;                                          \
                                                       \
void       prefix##_init (structname *d, size_t cap);  \
structname prefix##_new  (size_t cap);                 \
void       prefix##_push (structname *d, T item);      \

/* ----------- */




/* Implementation */

#define DYNARRAY_IMPL(structname, prefix, T)              \
                                                          \
void prefix##_init(structname *d, size_t cap) {           \
    *d = (structname) {                                   \
        .items = NULL,                                    \
        .cap   = cap,                                     \
        .size  = 0,                                       \
    };                                                    \
    d->items = malloc(d->cap * sizeof(T));                \
}                                                         \
                                                          \
structname prefix##_new(size_t cap) {                     \
    structname dynarray = { 0 };                          \
    prefix##_init(&dynarray, cap);                        \
    return dynarray;                                      \
}                                                         \
                                                          \
void prefix##_push(structname *d, T item) {               \
    if (d->size == d->cap) {                              \
        d->cap *= 2;                                      \
        d->items = realloc(d->items, d->cap * sizeof(T)); \
    }                                                     \
                                                          \
    d->items[d->size++] = item;                           \
}                                                                                           \

/* -------------- */

#endif // _DYNARRAY_H
