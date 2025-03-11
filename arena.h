#ifndef _ARENA_H
#define _ARENA_H

#include <stddef.h>
#include <stdlib.h>



typedef struct {
    size_t size, cap;
    void **items;
} Arena;

void  arena_init  (Arena *a);
void *arena_alloc (Arena *a, size_t size);
void  arena_free  (Arena *a);


#ifdef ARENA_IMPL

void arena_init(Arena *a) {
    *a = (Arena) {
        .cap   = 5,
        .size  = 0,
        .items = NULL,
    };

    a->items = malloc(a->cap * sizeof(void*));
}

void *arena_alloc(Arena *a, size_t size) {
    void *ptr = malloc(size);

    if (a->size == a->cap) {
        a->cap *= 2;
        a->items = realloc(a->items, a->cap * sizeof(void*));
    }

    a->items[a->size++] = ptr;

    return ptr;
}

void arena_free(Arena *a) {
    for (size_t i=0; i < a->size; ++i)
        free(a->items[i]);

    free(a->items);
    a->items = NULL;
}

#endif // ARENA_IMPL

#endif // _ARENA_H
