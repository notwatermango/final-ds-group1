#ifndef FILTERS_H
#define FILTERS_H
#include "structs.h"
#include "typedefs.h"
#include <stdbool.h>
/* helper :( */
u64 min(u64 a, u64 b);
u64 max(u64 a, u64 b);
/* function declaration goes here */
extern bool check_greyscale(image_t* img);
extern colors_t get_dominant_color(image_t* img);
extern void contoh_function();
#endif