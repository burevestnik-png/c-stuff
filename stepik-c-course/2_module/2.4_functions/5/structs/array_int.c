#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../io/io.h"
#include "maybe_int.h"
#include "array_int.h"

struct array_int array_int_create(size_t sz) {
    return (struct array_int) {.size = sz, .data = malloc(sz * sizeof(int64_t))};
}

struct maybe_int64 array_int_get(struct array_int a, size_t i) {
    if (i < 0 || i > a.size || a.size == 0) return none_int64;
    return (struct maybe_int64) {.valid = true, .value = a.data[i]};
}

bool array_int_set(struct array_int a, size_t i, int64_t value) {
    if (i < 0 || i > a.size || a.size == 0) return false;
    a.data[i] = value;
    return true;
}

void array_int_print( struct array_int array ) {
    for (size_t i = 0; i < array.size; i = i + 1) {
        printf("%" PRId64 " " , array_int_get( array, i).value);
    }
}

void array_int_free(struct array_int *a) {
    if (a->size > 0) {
        free(a->data);
        a->size = 0;
    }
}