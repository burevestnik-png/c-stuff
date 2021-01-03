#include <stdio.h>
#include <inttypes.h>
#include <malloc.h>
#include <stdbool.h>

struct maybe_int64 {
    int64_t value;
    bool valid;
};

struct maybe_int64 just_int64(int64_t i) {
    return (struct maybe_int64) {i, true};
}


const struct maybe_int64 none_int64 = {0};

void maybe_int64_print(struct maybe_int64 i) {
    if (i.valid) {
        printf("Some %" PRId64, i.value);
    } else {
        printf("None");
    }
}


// много if-ов, подумаю как их убрать как-нибудь потом)
struct maybe_int64 maybe_int64_min(struct maybe_int64 a, struct maybe_int64 b) {
    if (!a.valid && !b.valid) return none_int64;

    if (!a.valid)
        return b;

    if (!b.valid)
        return a;

    if ( a.value > b.value) {
        return b;
    } else return a;
}