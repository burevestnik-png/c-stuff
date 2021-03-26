#include <inttypes.h>
#include <stdbool.h>
#include <malloc.h>

#include "bmp.h"
#include "../util/file_manager.h"

#define BMP_BF_TYPE 0x4d42
#define BMP_BI_SIZE 40

#define FOR_BMP_HEADER(FOR_FIELD) \
        FOR_FIELD( uint16_t,bfType) \
        FOR_FIELD( uint32_t,bfileSize) \
        FOR_FIELD( uint32_t,bfReserved) \
        FOR_FIELD( uint32_t,bOffBits) \
        FOR_FIELD( uint32_t,biSize) \
        FOR_FIELD( uint32_t,biWidth) \
        FOR_FIELD( uint32_t,biHeight) \
        FOR_FIELD( uint16_t,biPlanes) \
        FOR_FIELD( uint16_t,biBitCount) \
        FOR_FIELD( uint32_t,biCompression) \
        FOR_FIELD( uint32_t,biSizeImage) \
        FOR_FIELD( uint32_t,biXPelsPerMeter) \
        FOR_FIELD( uint32_t,biYPelsPerMeter) \
        FOR_FIELD( uint32_t,biClrUsed) \
        FOR_FIELD( uint32_t,biClrImportant)

#define DECLARE_FIELD(t, n) t n ;

#pragma pack(push, 1)
struct bmp_header {
    FOR_BMP_HEADER(DECLARE_FIELD)
};
#pragma pack(pop)

const uint8_t trash_byte = 0;

static bool read_header(FILE *f, struct bmp_header *header) {
    return fread(header, sizeof(struct bmp_header), 1, f);
}

static size_t calculate_padding(const uint64_t width) {
    return (4 - width * 3 % 4) % 4;
}

// По мотивам https://cdn.hackaday.io/files/274271173436768/Simplified%20Windows%20BMP%20Bitmap%20File%20Format%20Specification.htm
static struct bmp_header bmp_header_init(const uint64_t width, const uint64_t height) {
    const size_t padding = calculate_padding(width);
    const uint32_t bOffBits = 54;
    return (struct bmp_header) {
            .biWidth = width,
            .biHeight = height,
            .bfileSize = bOffBits + height * (width + padding) * 3 + padding,
            .biSizeImage = width * height * 3,
            .bfType = BMP_BF_TYPE,
            .bfReserved = 0,
            .bOffBits = bOffBits,
            .biSize = BMP_BI_SIZE,
            .biPlanes = 1,
            .biBitCount = 24,
            .biCompression = 0,
            .biXPelsPerMeter = 0,
            .biYPelsPerMeter = 0,
            .biClrUsed = 0,
            .biClrImportant = 0
    };

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
    const size_t padding = calculate_padding(img->width);

    for (size_t i = 0; i < img->height; i++) {
        if (!fread(&(img->data[i * img->width]), sizeof(struct pixel), img->width, file)) {
            image_free(img);
            return detect_read_error(file);
        }
        fseek(file, padding, SEEK_CUR);
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

static size_t skip_padding(const size_t padding, FILE *file) {
    return fwrite(&trash_byte, sizeof(trash_byte), padding, file);
}

enum write_status write_data(FILE *file, const struct image *img) {
    const struct bmp_header header = bmp_header_init(img->width, img->height);
    if (!fwrite(&header, sizeof(struct bmp_header), 1, file)) {
        return WRITE_HEADER_ERROR;
    }

    const size_t padding = calculate_padding(img->width);

    for (size_t i = 0; i < img->height; i++) {
        if (!fwrite(&(img->data[i * img->width]), sizeof(struct pixel), img->width, file)) {
            return WRITE_ERROR;
        }
        skip_padding(padding, file);
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

