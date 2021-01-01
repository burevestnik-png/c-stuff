//
// Created by Yaroslav on 01.01.2021.
//

#include <malloc.h>
#include "marray-utils.h"

int64_t** marray_read(size_t* rows, size_t* sizes) {
    size_t array_quantity = read_size();
    sizes = malloc(array_quantity * sizeof(size_t));

    for (size_t i = 0; i < array_quantity; i++) {
        size_t array_size = read_size();
        sizes[i] = array_size;
    }
}
