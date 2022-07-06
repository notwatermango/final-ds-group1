#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include <string.h>
#include "file_handling.h"
#include "filters.h"

#ifndef AVL_H
#define AVL_H
extern avl_node_t *avl_init();
extern void avl_display(avl_node_t* node);
avl_node_t *avl_insert(avl_node_t *node, image_t *img);
#endif