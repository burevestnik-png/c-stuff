#include <stdio.h>

int divides(int a, int b) { return a % b == 0; }

void print_newline() { printf("\n"); }

void divisors(int limit) {
    for (int val = 1; val < limit + 1; val += 1) {
        printf("%d: ", val);

        if (val == 1) {
            print_newline();
            continue;
        }

        for (int i = 1; i < val + 1; i += 1) {
            if (i != 1 && divides(val, i)) {
                printf("%d ", i);

                if (i == val) {
                    print_newline();
                }
            }
        }
    }
}


int _main() {
    divisors(100);
    return 0;
}

