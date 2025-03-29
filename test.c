#include <stdio.h>
#include <assert.h>
#include <string.h>

#define ARENA_IMPL
#include "arena.h"

#include "dynarray.h"
DYNARRAY_DECL(List, list, int)
DYNARRAY_IMPL(List, list, int)

#include "util.h"

#include "test.h"





void test_arena(void) {
    Arena arena = { 0 };
    arena_init(&arena);

    size_t size = 15;

    for (size_t i=0; i < size; ++i) {
        int *x = arena_alloc(&arena, sizeof(int));
        assert(x != NULL);
        assert(arena.items[i] == x);
    }

    test_size_t(arena.size, size);

    int *ptr = arena_alloc(&arena, sizeof(int));
    *ptr = 1;

    ptr = arena_realloc(&arena, ptr, 2 * sizeof(int));
    ptr[1] = 2;

    assert(ptr[0] == 1 && ptr[1] == 2);

    arena_free(&arena);
}

void test_dynarray(void) {
    List list = { 0 };
    list_init(&list, 5);

    size_t size = 15;

    for (size_t i=0; i < size; ++i) {
        list_push(&list, (int) i);
        test_int(list.items[i], (int) i);
    }

    test_size_t(list.size, size);

    list_destroy(&list);
}

void test_read_entire_file(void) {
    char *str = read_entire_file("./test_resources/file.txt");
    test_str(str, "this is a file.\n");
    free(str);
}

void test_get_substring_count(void) {
    test_int(get_substring_count(".", "."), 1);
    test_int(get_substring_count("...", "."), 3);
    test_int(get_substring_count("foo", " "), 0);
    test_int(get_substring_count("foo bar", " "), 1);
    test_int(get_substring_count("foo bar baz qux quux", " "), 4);
}

void test_tokenize_string(void) {
    struct StringArray tokens = tokenize_string("foo,bar,baz", ",");
    test_str(tokens.items[0], "foo");
    test_str(tokens.items[1], "bar");
    test_str(tokens.items[2], "baz");
    free_tokens(&tokens);
}

int main(void) {

    test_get_substring_count();
    test_read_entire_file();
    test_arena();
    test_dynarray();
    test_tokenize_string();

    return 0;
}
