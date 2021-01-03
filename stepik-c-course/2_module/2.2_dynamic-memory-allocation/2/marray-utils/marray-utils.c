//
// Created by Yaroslav on 01.01.2021.
//

#include <malloc.h>
#include "marray-utils.h"

// https://prog-cpp.ru/c-alloc/
int64_t **marray_read(size_t *rows, size_t *sizes[]) {
    *rows = read_size();
    *sizes = malloc(*rows * sizeof(size_t));
    int64_t **free_array = (int64_t **) malloc(*rows * sizeof(int64_t *));

    for (size_t i = 0; i < *rows; i++) {
        size_t array_size = read_size();
        *((*sizes) + i) = array_size;
        if (array_size <= 0) continue;

        free_array[i] = malloc(array_size * sizeof(int64_t));
        for (size_t j = 0; j < array_size; j++) {
            free_array[i][j] = read_int64();
        }
    }

    return free_array;
}


void marray_print(int64_t **marray, size_t *sizes, size_t rows) {
    for (size_t i = 0; i < rows; i++) {
        printf("\n");
        for (size_t j = 0; j < sizes[i]; ++j) {
            print_int64(marray[i][j]);
            // Для степика нужно добавить printf(" ");
        }
    }
}

int64_t *marray_int_min(int64_t **marray, size_t *sizes, size_t rows) {
    int64_t *min = &marray[0][0];
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 1; j < sizes[i]; ++j) {
            if (marray[i][j] < *min) {
                min = &marray[i][j];
            }
        }
    }
    return min;
}

void marray_normalize(int64_t **marray, size_t sizes[], size_t rows, int64_t m) {
    for (size_t i = 0; i < rows; i = i + 1) {
        for (size_t j = 0; j < sizes[i]; j = j + 1) {
            marray[i][j] = marray[i][j] - m;
        }
    }
}

void marray_free(int64_t **marray, size_t rows) {
    for (size_t i = 0; i < rows; i++) {
        if (marray[i]) free(marray[i]);
    }
    free(marray);
}
