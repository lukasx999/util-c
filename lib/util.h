#ifndef _UTIL_H
#define _UTIL_H

#include <assert.h>



#define ARRAY_LEN(xs) (sizeof(xs) / sizeof *(xs))
#define NON_NULL(ptr) assert((ptr) != NULL)
#define UNREACHABLE assert(!"unreachable");
#define TODO(msg) assert(!"TODO: " msg);
#define UNUSED __attribute__((unused))
#define DISCARD(x) (void) (x); assert(0)



#endif // _UTIL_H
