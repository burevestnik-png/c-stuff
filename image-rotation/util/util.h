#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdint.h>

#include "file_manager.h"

enum read_status {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER,
    READ_FAIL,
    READ_SUDDEN_EOF,
};

enum write_status {
    WRITE_OK = 0,
    WRITE_ERROR,
    WRITE_HEADER_ERROR,
    /* коды других ошибок  */
};

_Noreturn void err(const char *msg, ...);

void print_warning(const char *msg);

void print_error(const char *msg);

void print_info(const char *msg);

void interpret_open_status(enum open_status status);

void interpret_close_status(enum close_status status);

void interpret_read_status(enum read_status status);

void interpret_write_status(enum write_status status);

#endif
