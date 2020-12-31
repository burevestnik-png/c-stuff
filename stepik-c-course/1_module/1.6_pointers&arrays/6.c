int predicate(int elem) {
    if (elem > 0) {
        return 0;
    } else {
        return 1;
    }
}

int array_contains(int* array, int* limit, int** position) {
    if (array >= limit) return 0;

    for (int *current = array; current < limit; current = current + 1) {
        if (predicate(*current)) {
            *position = current;
            return 1;
        }
    }

    return 0;
}

