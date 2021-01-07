//
// Created by Yaroslav on 07.01.2021.
//

#include "int_utils.h"

struct maybe_int64 just_int64( int64_t i ) {
    return (struct maybe_int64) { i, true };
}

