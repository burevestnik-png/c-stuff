//
// Created by Yaroslav on 01.01.2021.
//

#include "io_wrapper.h"

size_t read_size() {
    size_t value;
    scanf("%zu", &value);
    return value;
}

void print_size(const size_t value) {
    printf("%zu\n", value);
}

int64_t read_int64() {
    int64_t value;
    scanf("%" SCNd64, &value);
    return value;
}

void print_int64(const int64_t value) {
    printf("%" PRId64, value);
}

