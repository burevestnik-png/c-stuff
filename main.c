#include <stdio.h>
#include <inttypes.h>
#include <malloc.h>
#include <stdbool.h>

int main() {
    int64_t x;
    int res = scanf("%" SCNd64, &x);
    printf("%" PRId64 "\n", x);
    printf("%d", res);
    if (x == 4) {
        printf("EOF");
    }

    return 0;
}
