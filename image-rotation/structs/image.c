#include <malloc.h>
#include "image.h"

static struct image image_rotated_of(const struct image* img) {
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

struct image image_rotate(const struct image source) {
    struct image rotated_image = image_rotated_of(&source);

    for (size_t i = 0; i < source.height; i++) {
        for (size_t j = 0; j < source.width; j++) {
            rotated_image.data[source.height - i - 1 + j * source.height] =
                    source.data[i * source.width + j];
        }
    }

    return rotated_image;
}

void image_free(struct image* img) {
    free(img->data);
}