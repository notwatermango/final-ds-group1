#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include <string.h>
#include "file_handling.h"
#include "filters.h"

#ifndef AVL_H
#define AVL_H
extern void test_function_avl();
extern AVL* insert(AVL* current, image_t* img);
extern AVL* avl_init();
#endif