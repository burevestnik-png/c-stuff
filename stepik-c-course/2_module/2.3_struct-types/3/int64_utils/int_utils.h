//
// Created by Yaroslav on 07.01.2021.
//

#ifndef C_STUFF_INT_UTILS_H
#define C_STUFF_INT_UTILS_H

#include <stdint.h>
#include <stdbool.h>

struct maybe_int64 {
    int64_t value;
    bool valid;
};

const static struct maybe_int64 none_int64 = {0};

struct maybe_int64 just_int64(int64_t i);

#endif //C_STUFF_INT_UTILS_H
