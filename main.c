#include <stdio.h>
#include <inttypes.h>
#include <malloc.h>

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

void array_int_print(const int64_t *array, size_t size) {
    for (size_t i = 0; i < size; i = i + 1) {
        printf("%" PRId64 " ", array[i]);
    }
}

int main() {
    return 0;
}
