#include "file_manager.h"


const char* open_modes[] = {
        [READ_BINARY] = "rb",
        [WRITE_BINARY] = "wb"
};

static struct open_result form_res_successful(enum open_status status, FILE* f) {
    return (struct open_result) {
        .status = status,
        .file = f
    };
}

static struct open_result form_res_fail(enum open_status status) {
    return (struct open_result) {
        .status = status,
        .file = NULL
    };
}

struct open_result open_file(const char* path, enum open_mode mode) {
    if (!path) {
        return form_res_fail(NO_SUCH_FILE);
    }

    FILE *file = fopen(path, open_modes[mode]);

    if (file) {
        return form_res_successful(OPEN_OK, file);
    } else {
        return form_res_fail(OPEN_FAIL);
    }
}

enum close_status close_file(FILE *file) {
    int result = fclose(file);

    if (!result) {
        return CLOSE_OK;
    } else {
        return CLOSE_FAIL;
    }
}
