#include <assert.h>

#include "dynarray.h"

DYNARRAY_DECL(List, list, int)
DYNARRAY_IMPL(List, list, int)

int main(void) {

    List list = list_new(5);
    list_push(&list, 1);
    list_push(&list, 2);
    list_push(&list, 3);

    assert(list.size == 3);

    assert(list.items[0] == 1);
    assert(list.items[1] == 2);
    assert(list.items[2] == 3);

    return 0;
}
