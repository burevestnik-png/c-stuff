#ifndef IMAGE_H
#define IMAGE_H

#include <inttypes.h>

struct pixel {
    uint8_t b, g, r;
};

struct image {
    uint64_t width, height;
    struct pixel *data;
};

struct image image_rotate(const struct image source);

void image_init(struct image* img, uint64_t height, uint64_t width);

void image_free(struct image* img);

#endif