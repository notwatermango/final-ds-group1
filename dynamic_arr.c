#include "dynamic_arr.h"

dyn_arr *dyn_arr_init() {
  dyn_arr *arr = (dyn_arr*) malloc(sizeof(dyn_arr));
  arr->size = 0;
  arr->elements = calloc(5, sizeof(*(arr->elements)));
  arr->cap = 5;
  return arr;
}

void dyn_arr_insert(dyn_arr *arr, image_t *img) {
  if (arr->size >= arr->cap) {
    arr->elements = realloc(arr->elements, (5 + arr->cap) * sizeof(*(arr->elements)));
  } 
  arr->elements[arr->size] = img;
  arr->size++;
}

void dyn_arr_display(dyn_arr *arr) {
  for (int i = 0; i < arr->size; ++i) {
    printf("%lf\n", arr->elements[i]->contrast);
  }
}

// void sort_