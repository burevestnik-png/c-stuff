//
// Created by Yaroslav on 03.01.2021.
//

#ifndef C_STUFF_ARRAY_ARRAY_INT_H
#define C_STUFF_ARRAY_ARRAY_INT_H

#include <stdint.h>

struct array_array_int {
    struct array_int *data;
    size_t size;
};

struct array_array_int array_array_int_read();

void array_array_int_print(struct array_array_int array);

void array_array_int_normalize(struct array_array_int array, int64_t m);

struct maybe_int64 array_array_int_min(struct array_array_int array);

void array_array_int_free(struct array_array_int array);

#endif //C_STUFF_ARRAY_ARRAY_INT_H
