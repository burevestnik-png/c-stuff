#include <stdio.h>
#include <inttypes.h>

#include "maybe_int.h"

struct maybe_int64 some_int64(int64_t i) { return (struct maybe_int64) {i, true}; }

void maybe_int64_print( struct maybe_int64 i ) {
    if (i.valid) {
        printf("Some %" PRId64, i.value);
    } else {
        printf("None");
    }
}