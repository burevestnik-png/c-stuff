void array_reverse(int *array, int size) {
    int reversed_array[size];
    for (int i = 0; i < size; i = i + 1) {
        reversed_array[i] = array[size - 1 - i];
    }

    for (int i = 0; i < size; i = i + 1) {
        array[i] = reversed_array[i];
    }
}

void array_reverse_ptr(int* array, int* limit) {
    int reversed_array[limit - array];
    for (int* current = array; current < limit; current = current + 1) {
        reversed_array[current - array] = array[limit - current - 1];
    }

    for (int i = 0; i < limit - array; i = i + 1) {
        array[i] = reversed_array[i];
    }
}