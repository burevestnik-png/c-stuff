#ifndef FILE_MANAGER
#define FILE_MANAGER

#include <stdio.h>

enum open_status {
    OPEN_OK = 0,
    NO_SUCH_FILE,
    OPEN_FAIL,
};

struct open_result {
    enum open_status status;
    FILE *file;
};

enum open_mode {
    READ_BINARY = 0,
    WRITE_BINARY
};

enum close_status {
    CLOSE_OK = 0,
    CLOSE_FAIL
};

struct open_result open_file(const char *path, enum open_mode mode);

enum close_status close_file(FILE *file);

#endif