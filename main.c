#include <stdio.h>
#include <inttypes.h>
#include <malloc.h>
#include <stdbool.h>

int main() {
    int64_t square(int64_t x) { return x * x; }

    int main() {

        int64_t array[] = {1, 2, 3, 4, 5};

        const size_t count = sizeof(array) / sizeof(array[0]);


        // указатель на функцию int64_t -> int64_t

        int64_t (*mapper)(int64_t) = &square;

        for (size_t i = 0; i < count; i = i + 1) {
            array[i] = mapper(array[i]);
        }


        return 0;
    }
}