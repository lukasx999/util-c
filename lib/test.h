#ifndef _TEST_H
#define _TEST_H



#define test(value, expected, cond, fmt) do {                         \
    if (!(cond))                                                      \
        fprintf(                                                      \
            stderr,                                                   \
            "-> test `" #value " == " fmt "` failed, got " fmt " \n", \
            expected,                                                 \
            value                                                     \
        );                                                            \
} while (0)

#define test_eq(value, expected, fmt) \
    test(value, expected, (value) == (expected), fmt)

#define test_ptr(value, expected) \
    test_eq(value, expected, "%p")

#define test_size_t(value, expected) \
    test_eq(value, expected, "%lu")

#define test_int(value, expected) \
    test_eq(value, expected, "%d")

#define test_str(value, expected) \
    test(value, expected, !strcmp((value), (expected)), "%s")



#endif // _TEST_H
