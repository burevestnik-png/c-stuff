#include "./data-structs/list.h"
#include <stdio.h>
#include "./data-structs/map.h"

int main() {
    struct map m = map_create();

    map_add(m, "Hello", "World");
    map_add(m, "Hello!", "World!");
    map_add(m, "Hello!!", "World!!");

    map_foreach_kvp(m, entry_print);

    print_newline();
    printf("%s", map_get(m, "Hello"));
    print_newline();
    map_destroy(m);
    return 1;
}