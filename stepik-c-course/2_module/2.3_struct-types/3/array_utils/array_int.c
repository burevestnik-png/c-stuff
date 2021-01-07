//
// Created by Yaroslav on 03.01.2021.
//

#include "array_int.h"

void array_int_normalize( struct array_int array, int64_t m ) {
    for (size_t i = 0; i < array.size; i = i + 1) {
        array.data[i] = array.data[i] - m;
    }
}

struct maybe_array_int some_array_int(struct array_int array) {
    return (struct maybe_array_int) { array, true };
}
