#include "marray-utils/marray-utils.h"
#include "int_array_utils/int_array_utils.h"

int main() {
    size_t rows;
    size_t *sizes;
    int64_t **marray = marray_read(&rows, &sizes);
    int64_t *min = marray_int_min(marray, sizes, rows);
    if (min) {
        marray_normalize(marray, sizes, rows, *min);
        marray_print(marray, sizes, rows);
    }
    marray_free(marray, rows);
    free(sizes);
    return 0;
}