int is_prime(int value) {
    if (value <= 1) {
        return 0;
    }

    for (int i = 2; i < value; i++) {
        if (value == 2) {
            return 1;
        }

        if (value % i == 0) {
            return 0;
        }
    }

    return 1;
}
