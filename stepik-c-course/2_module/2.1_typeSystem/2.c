#include <stdint.h>

size_t count_zeroes(const void *data, size_t sz) {
    size_t counter = 0;
    for (size_t i = 0; i < sz; i++) {
        if (((uint8_t*) data)[i] == 0) {
            counter++;
        }
    }
    return counter;
}


int main() {
    uint32_t array[2] = {1, 3};
    count_zeroes(array, 8);
    return 0;
}