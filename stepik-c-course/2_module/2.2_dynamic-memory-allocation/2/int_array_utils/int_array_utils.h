//
// Created by Yaroslav on 01.01.2021.
//

#ifndef C_STUFF_INT_ARRAY_UTILS_H
#define C_STUFF_INT_ARRAY_UTILS_H

#include <stdio.h>
#include <inttypes.h>
#include <malloc.h>

void array_int_fill(int64_t *array, size_t size);

int64_t *array_int_read(size_t *size);

int64_t *array_int_min(int64_t *array, size_t size);

void array_int_print(const int64_t *array, size_t size);

void array_size_print(const size_t *array, size_t size);

#endif //C_STUFF_INT_ARRAY_UTILS_H
