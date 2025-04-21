#define _GNU_SOURCE
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <pthread.h>

#define ARENA_IMPL
#include "arena.h"

#include "dynarray.h"
DYNARRAY_DECL(List, list, int)
DYNARRAY_IMPL(List, list, int)

#include "util.h"
#include "strio.h"
#include "test.h"


void test_clamp(void) {
    test_int(CLAMP(50, 0, 25), 25);
    test_int(CLAMP(-50, 0, 25), 0);
    test_int(CLAMP(50, 0, 100), 50);
    test_int(CLAMP(0, 0, 0), 0);
    test_int(CLAMP(10, 0, 0), 0);
    test_int(CLAMP(2, 1, 2), 2);
    test_int(CLAMP(2, 2, 2), 2);
}

void test_arena(void) {
    Arena arena = { 0 };
    arena_init(&arena);

    size_t size = 15;

    for (size_t i=0; i < size; ++i) {
        int *x = arena_alloc(&arena, sizeof(int));
        NON_NULL(x);
        test_ptr(arena.items[i], (void*) x);
    }

    test_size_t(arena.size, size);

    int *ptr = arena_alloc(&arena, sizeof(int));
    *ptr = 1;

    ptr = arena_realloc(&arena, ptr, 2 * sizeof(int));
    ptr[1] = 2;

    test_int(ptr[0], 1);
    test_int(ptr[1], 2);

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
    test_size_t(get_substring_count("abc", ""), 4);
    test_size_t(get_substring_count("", "fjksfjds"), 0);
    test_size_t(get_substring_count("fjklsdjfkldsf", ""), 14);
    test_size_t(get_substring_count("", "."), 0);
    test_size_t(get_substring_count(".", "."), 1);
    test_size_t(get_substring_count("...", "."), 3);
    test_size_t(get_substring_count("foo", " "), 0);
    test_size_t(get_substring_count("foo bar", " "), 1);
    test_size_t(get_substring_count("foo bar baz qux quux", " "), 4);
}

void test_tokenize_string(void) {
    struct StringArray tokens = { 0 };


    tokens = tokenize_string("foo", ",");
    test_size_t(tokens.count, 1);
    test_str(tokens.strings[0], "foo");
    free_stringarray(&tokens);

    // TODO:
    // tokens = tokenize_string("foo,", ",");
    // test_size_t(tokens.count, 2);
    // test_str(tokens.strings[0], "foo");
    // test_str(tokens.strings[1], "");
    // free_stringarray(&tokens);

    tokens = tokenize_string("foo,bar,baz", ",");
    test_size_t(tokens.count, 3);
    test_str(tokens.strings[0], "foo");
    test_str(tokens.strings[1], "bar");
    test_str(tokens.strings[2], "baz");
    free_stringarray(&tokens);

    tokens = tokenize_string("aYYYbYYYc", "YYY");
    test_size_t(tokens.count, 3);
    test_str(tokens.strings[0], "a");
    test_str(tokens.strings[1], "b");
    test_str(tokens.strings[2], "c");
    free_stringarray(&tokens);

    // TODO:
    // tokens = tokenize_string("", "YYY");
    // test_size_t(tokens.count, 1);
    // free_stringarray(&tokens);

    // // TODO:
    // tokens = tokenize_string("a,b,", ",");
    // test_size_t(tokens.count, 3);
    // test_str(tokens.strings[0], "a");
    // test_str(tokens.strings[1], "b");
    // // test_str(tokens.strings[2], "");
    // free_stringarray(&tokens);

}

void test_read_file_lines(void) {
    struct StringArray
        lines = read_entire_file_lines("./test_resources/file_with_lines.txt");

    test_size_t(lines.count, 3);
    test_str(lines.strings[0], "line one");
    test_str(lines.strings[1], "line two");
    test_str(lines.strings[2], "line three");

    free_stringarray(&lines);
}

void test_get_file_size(void) {
    ssize_t size = get_file_size("./test_resources/file.txt");
    assert(size != -1);
    test_size_t(size, 16);
}

void test_string_expand_query(void) {

    char *s = NULL;

    s = string_expand_query("a", "a", "b");
    NON_NULL(s);
    test_str(s, "b");
    free(s);

    s = string_expand_query("", ",", "ZZZ");
    NON_NULL(s);
    test_str(s, "");
    free(s);

    s = string_expand_query("abc", "", "ZZZ");
    NON_NULL(s);
    test_str(s, "ZZZaZZZbZZZcZZZ");
    free(s);

    s = string_expand_query("a,b,c", ",", "ZZZ");
    NON_NULL(s);
    test_str(s, "aZZZbZZZc");
    free(s);

    s = string_expand_query("a,b,c", ",", ".");
    NON_NULL(s);
    test_str(s, "a.b.c");
    free(s);

    s = string_expand_query("a---b---c", "---", ".");
    NON_NULL(s);
    test_str(s, "a.b.c");
    free(s);

}

int main(void) {

    test_clamp();
    test_string_expand_query();
    test_arena();
    test_dynarray();
    test_get_file_size();
    test_get_substring_count();
    test_tokenize_string();
    test_read_entire_file();
    test_read_file_lines();

    return 0;
}
