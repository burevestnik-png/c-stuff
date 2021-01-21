#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "util.h"

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"

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
    fprintf(stderr,"%s%s%s", YELLOW, msg, RESET);
    print_newline();
}

void print_info(const char *msg) {
    fprintf(stderr,"%s%s%s\n", GREEN, msg, RESET);
}

void print_error(const char *msg) {
    if (!errno) {
        fprintf(stderr,"%s%s%s", RED, msg, RESET);
        print_newline();
    } else {
        perror(msg);
    }
}

void interpret_open_status(enum open_status status) {
    switch (status) {
        case OPEN_OK:
            print_info("File was opened SUCCESSFULLY");
            break;
        case NO_SUCH_FILE:
            print_error("You are entered non-existent file or directory.");
            break;
        default:
            print_error("During opening file an error occurred");
    }
}

void interpret_close_status(enum close_status status) {
    switch (status) {
        case CLOSE_OK:
            print_info("File was closed SUCCESSFULLY");
            break;
        case CLOSE_FAIL:
            print_error("During closing file an error occurred");
        default:
            break;
    }
}

void interpret_read_status(enum read_status status) {
    switch (status) {
        case READ_OK:
            print_info("File was read SUCCESSFULLY");
            break;
        default:
            print_error("During reading file an error occurred");
    }
}

void interpret_write_status(enum write_status status) {
    switch (status) {
        case WRITE_OK:
            print_info("File was saved SUCCESSFULLY");
            break;
        default:
            print_error("During saving file an error occurred");
    }
}

