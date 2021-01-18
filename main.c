#include <stdio.h>
#include <inttypes.h>
#include <malloc.h>
#include <stdbool.h>

int main() {
    uint64_t x = 292;

    uint8_t *begin = (uint8_t *) &x;
    printf("%s", &x);
    printf("%s", begin);
}