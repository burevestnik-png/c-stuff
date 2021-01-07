//
// Created by Yaroslav on 03.01.2021.
//

#ifndef C_STUFF_ARRAY_INT_H
#define C_STUFF_ARRAY_INT_H

#include <stdint.h>
#include <stdbool.h>

struct array_int {
    int64_t *data;
    size_t size;
};

struct maybe_array_int {
    struct array_int value;
    bool valid;
};

const static struct maybe_array_int none_array_int = { {NULL, 0}, false };

void array_int_normalize( struct array_int array, int64_t m );

struct maybe_array_int some_array_int(struct array_int array);

#endif //C_STUFF_ARRAY_INT_H
