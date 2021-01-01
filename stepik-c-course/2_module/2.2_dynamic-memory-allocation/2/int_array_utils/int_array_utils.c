//
// Created by Yaroslav on 01.01.2021.
//

#include "int_array_utils.h"
#include "../io/io_wrapper.h"

void array_int_fill(int64_t *array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        array[i] = read_int64();
    }
}

int64_t *array_int_read(size_t *size) {
    *size = read_size();

    if (*size) {
        int64_t *array = malloc(*size * sizeof(uint64_t));
        array_int_fill(array, *size);
        return array;
    }

    return NULL;
}


int64_t *array_int_min(int64_t *array, size_t size) {
    if (size <= 0) return NULL;

    int64_t *min = array;
    for (size_t i = 1; i < size; i++) {
        if (array[i] < *min) min = array + i;
    }

    return min;
}

void array_int_print(const int64_t *array, size_t size) {
    for (size_t i = 0; i < size; i = i + 1) {
        printf("%" PRId64 " ", array[i]);
    }
}

void array_size_print(const size_t *array, size_t size) {
    for (size_t i = 0; i < size; i = i + 1) {
        printf("%zu", array[i]);
    }
}
