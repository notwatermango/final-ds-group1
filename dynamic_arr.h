#include "structs.h"
#include <stdlib.h>
#include <stdio.h>
#ifndef DYNAMIC_ARR
#define DYNAMIC_ARR
dyn_arr *dyn_arr_init();
void dyn_arr_insert(dyn_arr *arr, image_t *img);
void dyn_arr_display(dyn_arr *arr);
#endif