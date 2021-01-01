#include "marray-utils/marray-utils.h"
#include "int_array_utils/int_array_utils.h"

int main() {
    size_t rows;
    size_t* sizes;
    int64_t** marray = marray_read(&rows, sizes);
    array_size_print(sizes, rows);
    return 0;
}