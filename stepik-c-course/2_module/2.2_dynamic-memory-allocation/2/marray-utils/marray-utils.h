//
// Created by Yaroslav on 01.01.2021.
//

#ifndef C_STUFF_MARRAY_UTILS_H
#define C_STUFF_MARRAY_UTILS_H

#include <stdint.h>
#include "../io/io_wrapper.h"

int64_t **marray_read(size_t *rows, size_t *sizes[]);

void marray_print(int64_t **marray, size_t *sizes, size_t rows);

int64_t *marray_int_min(int64_t **marray, size_t *sizes, size_t rows);

void marray_normalize(int64_t **marray, size_t sizes[], size_t rows, int64_t m);

void marray_free(int64_t **marray, size_t rows);

#endif //C_STUFF_MARRAY_UTILS_H
