#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#define LIMIT 2

uint_least32_t data[8*1024*1024] = {0};

size_t count_gt(uint_least32_t *array, size_t size) {
    size_t counter = 0;

    for (size_t i = 0; i < size; i++) {
        if (array[i] > LIMIT) counter++;
    }

    return counter;
}