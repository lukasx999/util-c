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
    int *xs = arena_alloc(&arena, size * sizeof(int));

    for (size_t i=0; i < size; ++i) {
        xs[i] = i;
        printf("i: %d\n", xs[i]);
    }

    arena_free(&arena);
}

void test_dynarray(void) {
    List list = list_new(5);
    list_push(&list, 1);
    list_push(&list, 2);
    list_push(&list, 3);

    assert(list.size == 3);

    assert(list.items[0] == 1);
    assert(list.items[1] == 2);
    assert(list.items[2] == 3);
}

int main(void) {

    test_arena();
    test_dynarray();

    return 0;
}
