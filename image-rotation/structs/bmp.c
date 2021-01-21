#include <inttypes.h>
#include <stdbool.h>
#include <malloc.h>

#include "bmp.h"
#include "../util/file_manager.h"

#define PRI_SPECIFIER(e) (_Generic( (e), uint16_t : "%" PRIu16, uint32_t: "%" PRIu32, default: "NOT IMPLEMENTED" ))

#define PRINT_FIELD(t, name) \
    fprintf( f, "%-17s: ",  # name ); \
    fprintf( f, PRI_SPECIFIER( header->name ) , header-> name );\
    fprintf( f, "\n");

// Выделил структуру, так как подразумеваю что padding может
// быть от 0 до 3 включая и хотел бы это контролировать
typedef struct {
    size_t value;
} padding;

const uint8_t trash_byte = 0;

void bmp_header_print(struct bmp_header const *header, FILE *f) {
    FOR_BMP_HEADER(PRINT_FIELD)
}

static bool read_header(FILE *f, struct bmp_header *header) {
    return fread(header, sizeof(struct bmp_header), 1, f);
}

static padding calculate_padding(const uint64_t width) {
    return (padding) {.value = (4 - width * 3 % 4) % 4};
}

// По мотивам https://cdn.hackaday.io/files/274271173436768/Simplified%20Windows%20BMP%20Bitmap%20File%20Format%20Specification.htm
static struct bmp_header bmp_header_init(const uint64_t width, const uint64_t height) {
    const padding p = calculate_padding(width);
    const uint32_t bOffBits = 54;
    return (struct bmp_header) {
            .biWidth = width,
            .biHeight = height,
            .bfileSize = bOffBits + height * (width + p.value) * 3 + p.value,
            .biSizeImage = width * height * 3,
            .bfType = 0x4d42,
            .bfReserved = 0,
            .bOffBits = bOffBits,
            .biSize = 40,
            .biPlanes = 1,
            .biBitCount = 24,
            .biCompression = 0,
            .biXPelsPerMeter = 0,
            .biYPelsPerMeter = 0,
            .biClrUsed = 0,
            .biClrImportant = 0
    };

}

bool read_header_from_file(const char *filename, struct bmp_header *header) {
    struct open_result result = open_file(filename, READ_BINARY);
    interpret_open_status(result.status);
    if (result.status != OPEN_OK) {
        return false;
    }

    if (read_header(result.file, header)) {
        enum close_status status = close_file(result.file);
        interpret_close_status(status);
        if (status != CLOSE_OK) {
            return false;
        }
        return true;
    }

    close_file(result.file);
    return false;
}

static enum read_status detect_read_error(FILE *file) {
    if (feof(file)) {
        return READ_SUDDEN_EOF;
    } else {
        return READ_FAIL;
    }
}

enum read_status read_data(FILE *file, struct image *img) {
    struct bmp_header header = {0};
    if (!read_header(file, &header)) {
        return detect_read_error(file);
    }

    image_init(img, header.biHeight, header.biWidth);
    const padding p = calculate_padding(img->width);

    for (size_t i = 0; i < img->height; i++) {
        if (!fread(&(img->data[i * img->width]), sizeof(struct pixel), img->width, file)) {
            image_free(img);
            return detect_read_error(file);
        }
        fseek(file, p.value, SEEK_CUR);
    }

    return READ_OK;
}

bool read_data_from_file(const char *filename, struct image *img) {
    print_warning("Started reading file");

    const struct open_result open_result = open_file(filename, READ_BINARY);
    interpret_open_status(open_result.status);
    if (open_result.status != OPEN_OK) {
        return false;
    }

    const enum read_status read_status = read_data(open_result.file, img);
    interpret_read_status(read_status);
    if (read_status != READ_OK) {
        close_file(open_result.file);
        return false;
    }

    const enum close_status close_status = close_file(open_result.file);
    interpret_close_status(close_status);
    if (close_status != CLOSE_OK) {
        return false;
    }

    return true;
}

static size_t skip_padding(const padding p, FILE *file) {
    return fwrite(&trash_byte, sizeof(trash_byte), p.value, file);
}

enum write_status write_data(FILE *file, const struct image *img) {
    const struct bmp_header header = bmp_header_init(img->width, img->height);
    if (!fwrite(&header, sizeof(struct bmp_header), 1, file)) {
        return WRITE_HEADER_ERROR;
    }

    const padding p = calculate_padding(img->width);

    for (size_t i = 0; i < img->height; i++) {
        if (!fwrite(&(img->data[i * img->width]), sizeof(struct pixel), img->width, file)) {
            return WRITE_ERROR;
        }
        skip_padding(p, file);
    }

    return WRITE_OK;
}

bool write_data_to_file(const char *filename, struct image const *img) {
    print_warning("Started saving file");

    const struct open_result open_result = open_file(filename, WRITE_BINARY);
    interpret_open_status(open_result.status);
    if (open_result.status != OPEN_OK) {
        return false;
    }

    const enum write_status write_status = write_data(open_result.file, img);
    interpret_write_status(write_status);
    if (write_status != WRITE_OK) {
        return false;
    }

    const enum close_status close_status = close_file(open_result.file);
    interpret_close_status(close_status);
    if (close_status != CLOSE_OK) {
        return false;
    }

    return true;
}

