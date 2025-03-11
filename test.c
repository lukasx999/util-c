#include <stdio.h>
#include <assert.h>

#define ARENA_IMPL
#include "arena.h"

#include "dynarray.h"
DYNARRAY_DECL(List, list, int)
DYNARRAY_IMPL(List, list, int)



void test_arena(void) {
    Arena arena = { 0 };
    arena_init(&arena);

    size_t size = 15;

    for (size_t i=0; i < size; ++i) {
        int *x = arena_alloc(&arena, sizeof(int));
        assert(x != NULL);
        assert(arena.items[i] == x);
    }

    assert(arena.size == size);

    arena_free(&arena);
}

void test_dynarray(void) {
    List list = { 0 };
    list_init(&list, 5);

    size_t size = 15;

    for (size_t i=0; i < size; ++i) {
        list_push(&list, (int) i);
        assert(list.items[i] == (int) i);
    }

    assert(list.size == size);

    list_destroy(&list);
}

int main(void) {

    test_arena();
    test_dynarray();

    return 0;
}
