#include "array_utils/array_array_int.h"
#include "int64_utils/int_utils.h"

int main() {
    struct array_array_int array = array_array_int_read();
    struct maybe_int64 m = array_array_int_min(array);
    if (m.valid) {
        array_array_int_normalize(array, m.value);
        array_array_int_print(array);
    }
    array_array_int_free(array);
    return 0;
}