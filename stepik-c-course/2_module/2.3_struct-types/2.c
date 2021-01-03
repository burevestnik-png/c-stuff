#include <stdio.h>
#include <inttypes.h>
#include <malloc.h>
#include <stdbool.h>

struct maybe_int64 {
    int64_t value;
    bool valid;
};

const struct maybe_int64 none_int64 = {0};

struct array_int {
    int64_t *data;
    size_t size;
};

struct maybe_int64 array_int_get(struct array_int a, size_t i) {
    if (i < 0 || i > a.size || a.size == 0) return none_int64;
    return (struct maybe_int64) {.valid = true, .value = a.data[i]};
}

bool array_int_set(struct array_int a, size_t i, int64_t value) {
    if (i < 0 || i > a.size || a.size == 0) return false;
    a.data[i] = value;
    return true;
}

struct maybe_int64 array_int_min(struct array_int array) {
    if (array.size == 0) return none_int64;

    int64_t *min = &array.data[0];
    for (size_t i = 0; i < array.size; i++) {
        if (array.data[i] < *min) min = &array.data[i];
    }

    return (struct maybe_int64) {.value = *min, .valid = true};
}