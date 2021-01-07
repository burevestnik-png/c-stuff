//
// Created by Yaroslav on 03.01.2021.
//

#include <malloc.h>
#include "array_array_int.h"
#include "../io/io.h"
#include "array_int.h"
#include "../int64_utils/int_utils.h"

// https://prog-cpp.ru/c-struct/
struct array_array_int array_array_int_read() {
    size_t size = read_size();
    struct array_int *array_array = malloc(size * sizeof(struct array_int));

    for (size_t i = 0; i < size; i++) {
        size_t array_size = read_size();
        int64_t *array = malloc(array_size * sizeof(int64_t));

        for (size_t j = 0; j < array_size; j++) {
            array[j] = read_int64();
        }

        array_array[i] = (struct array_int) {.size = array_size, .data = array};
    }

    return (struct array_array_int) {.size = size, .data = array_array};
}

void array_array_int_print(struct array_array_int array) {
    for (size_t i = 0; i < array.size; i++) {
        for (size_t j = 0; j < array.data[i].size; j++) {
            print_int64(array.data[i].data[j]);
            printf(" ");
        }
        printf("\n");
    }
}

struct maybe_array_int array_array_int_get_row(struct array_array_int a, size_t i) {
    if (0 <= i && i < a.size) { return some_array_int(a.data[i]); }
    else { return none_array_int; }
}

void array_array_int_normalize(struct array_array_int array, int64_t m) {
    for (size_t i = 0; i < array.size; i = i + 1) {
        const struct maybe_array_int cur_row = array_array_int_get_row(array, i);
        if (cur_row.valid) {
            array_int_normalize(cur_row.value, m);
        }
    }
}

struct maybe_int64 array_array_int_get(struct array_array_int a, size_t i, size_t j) {
    if ((i < 0 || i >= a.size) || (j < 0 || j >= a.data[i].size))
        return none_int64;
    return just_int64(a.data[i].data[j]);
}

bool array_array_int_set(struct array_array_int a, size_t i, size_t j, int64_t value) {
    if ((i < 0 || i >= a.size) || (j < 0 || j >= a.data[i].size))
        return false;

    a.data[i].data[j] = value;
    return true;
}

struct maybe_int64 array_array_int_min(struct array_array_int array) {
    int64_t min = array.data[0].data[0];
    for (size_t i = 0; i < array.size; i++) {
        for (size_t j = 1; j < array.data[i].size; j++) {
            if (array.data[i].data[j] < min) {
                min = array.data[i].data[j];
            }
        }
    }
    return just_int64(min);
}

void array_array_int_free(struct array_array_int array) {
    for (size_t i = 0; i < array.size; i++) {
        free(array.data[i].data);
    }
    free(array.data);
}
