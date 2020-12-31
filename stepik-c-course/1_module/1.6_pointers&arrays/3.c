int is_prime(int value) {
    if (value>1) {
        for (int i = 2; i < value / 2; i++) {
            if (value % i) return 0;
        }

        return 1;
    } else {
        return 0;
    }
}

void factorize(int n, int *a, int *b) {
    if (n == 1 || is_prime(n)) {
        *a = 1;
        *b = n;
        return;
    }

    if (n % 2 == 0) {
        *a = 2;
        *b = n / 2;
        return;
    }

    for (int i = 3; i < n / 2; i += 2) {
        if (n % i == 0) {
            *a = i;
            *b = n / i;
            return;
        }
    }
}