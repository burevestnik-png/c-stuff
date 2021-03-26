#ifndef _BMP_H_
#define _BMP_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "image.h"
#include "../util/util.h"

bool read_data_from_file(const char *filename, struct image *img);

bool write_data_to_file(const char *filename, const struct image *img);

#endif
