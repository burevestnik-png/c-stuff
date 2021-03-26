#include <malloc.h>
#include "image.h"

static struct image image_empty_rotated_of(const struct image* img) {
    return (struct image) {
        .width = img->height,
        .height = img->width,
        .data = malloc(img->height * img->width * sizeof(struct pixel))
    };
}

void image_init(struct image* img, const uint64_t height, const uint64_t width) {
    img->height = height;
    img->width = width;
    img->data = malloc(sizeof(struct pixel) * height * width);
}

static uint64_t calc_rotated_pixel_address(const struct image* source, uint64_t i, uint64_t j) {
    return source->height - i - 1 + j * source->height;
}

struct image image_rotate(const struct image source) {
    struct image rotated_image = image_empty_rotated_of(&source);

    for (uint64_t i = 0; i < source.height; i++) {
        for (uint64_t j = 0; j < source.width; j++) {
            rotated_image.data[calc_rotated_pixel_address(&source, i, j)] =
                    source.data[i * source.width + j];
        }
    }

    return rotated_image;
}

void image_free(struct image* img) {
    free(img->data);
}