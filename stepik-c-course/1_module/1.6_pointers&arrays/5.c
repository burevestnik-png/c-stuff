void array_fib(int* array, int* limit) {
    if (array == limit) return;

    for (int *current = array; current < limit; current++) {
        if (current == array || current == array + 1) {
            *current = 1;
            continue;
        }

        *current = *(current - 1) + *(current - 2);
    }
}


int main() {
    int array[4] = {0};
    int array_size = sizeof(array) / 4;

    print_array(array, array_size);
    array_fib(array, array + array_size);
    print_array(array, array_size);
    return 0;
}