#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "util.h"

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"

#define DEFAULT_OPEN_ERROR_MSG "During opening file an error occurred"
#define DEFAULT_CLOSE_ERROR_MSG "During closing file an error occurred"
#define DEFAULT_READ_ERROR_MSG "During reading file an error occurred"
#define DEFAULT_WRITE_ERROR_MSG "During saving file an error occurred"

const char* open_status_msgs[] = {
        [OPEN_OK] = "File was opened SUCCESSFULLY",
        [NO_SUCH_FILE] = "You are entered non-existent file or directory",
        [OPEN_FAIL] = DEFAULT_OPEN_ERROR_MSG,
};

const char* close_status_msgs[] = {
        [CLOSE_OK] = "File was closed SUCCESSFULLY",
        [CLOSE_FAIL] = DEFAULT_CLOSE_ERROR_MSG,
};

const char* read_status_msgs[] = {
        [READ_OK] = "File was read SUCCESSFULLY",
        [READ_INVALID_SIGNATURE] = DEFAULT_READ_ERROR_MSG,
        [READ_INVALID_BITS] = DEFAULT_READ_ERROR_MSG,
        [READ_INVALID_HEADER] = DEFAULT_READ_ERROR_MSG,
        [READ_FAIL] = DEFAULT_READ_ERROR_MSG,
        [READ_SUDDEN_EOF] = DEFAULT_READ_ERROR_MSG,
};

const char* write_status_msgs[] = {
        [WRITE_OK] = "File was saved SUCCESSFULLY",
        [WRITE_ERROR] = DEFAULT_WRITE_ERROR_MSG,
        [WRITE_HEADER_ERROR] = DEFAULT_WRITE_ERROR_MSG,
};

static void print_newline() {
    fprintf(stderr, "\n");
}

_Noreturn void err(const char *msg, ...) {
    va_list args;
    va_start(args, msg);

    fprintf(stderr, RED);
    vfprintf(stderr, msg, args);
    fprintf(stderr, RESET);
    print_newline();

    va_end(args);
    exit(1);
}

void print_warning(const char *msg) {
    fprintf(stderr, YELLOW "%s" RESET, msg);
    print_newline();
}

void print_info(const char *msg) {
    fprintf(stderr, GREEN "%s" RESET "\n", msg);
}

void print_error(const char *msg) {
    if (!errno) {
        fprintf(stderr, RED "%s" RESET, msg);
        print_newline();
    } else {
        perror(msg);
    }
}

void interpret_open_status(enum open_status status) {
    if (status == OPEN_OK) {
        print_info(open_status_msgs[status]);
    } else {
        print_error(open_status_msgs[status]);
    }
}

void interpret_close_status(enum close_status status) {
    if (status == CLOSE_OK) {
        print_info(close_status_msgs[status]);
    } else {
        print_error(close_status_msgs[status]);
    }
}

void interpret_read_status(enum read_status status) {
    if (status == READ_OK) {
        print_info(read_status_msgs[status]);
    } else {
        print_error(read_status_msgs[status]);
    }
}

void interpret_write_status(enum write_status status) {
    if (status == WRITE_OK) {
        print_info(write_status_msgs[status]);
    } else {
        print_error(write_status_msgs[status]);
    }
}

