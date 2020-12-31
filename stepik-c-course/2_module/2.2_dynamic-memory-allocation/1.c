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


void array_int_fill(int64_t *array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        array[i] = read_int64();
    }
}

int64_t *array_int_read(size_t *size) {
    *size = read_size();

    if (*size) {
        int64_t *array = malloc(*size * sizeof(uint64_t));
        array_int_fill(array, *size);
        return array;
    }

    return NULL;
}


int64_t *array_int_min(int64_t *array, size_t size) {
    if (size <= 0) return NULL;

    int64_t *min = array;
    for (size_t i = 1; i < size; i++) {
        if (array[i] < *min) min = array + i;
    }

    return min;
}

void perform() {
    size_t size;
    int64_t *array = array_int_read(&size);

    if (size <= 0) {
        return;
    }

    print_int64(*array_int_min(array, size));
    free(array);
}

void test_array_int_min() {
    int64_t array[4] = {6, 4, 24, 77};
    size_t size = 4;

    int64_t *min = array_int_min(array, size);
    print_int64(*min);
}

void test_array_int_read() {
    size_t size = (size_t) NULL;
    int64_t *array = array_int_read(&size);

    print_size(size);
    array_int_print(array, size);
}

void test_array_int_fill() {
    int64_t array[2] = {0};
    size_t size = 2;
    array_int_fill(array, size);

    array_int_print(array, size);
}
