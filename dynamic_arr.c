#include "dynamic_arr.h"

dyn_arr* dyn_arr_init() {
  dyn_arr* arr = (dyn_arr*)malloc(sizeof(dyn_arr));
  arr->size = 0;
  arr->elements = calloc(5, sizeof(*(arr->elements)));
  arr->cap = 5;
  return arr;
}

void dyn_arr_insert(dyn_arr* arr, image_t* img) {
  if (arr->size >= arr->cap) {
    arr->elements = realloc(arr->elements, (5 + arr->cap) * sizeof(*(arr->elements)));
  }
  arr->elements[arr->size] = img;
  arr->size++;
}

void dyn_arr_display(dyn_arr* arr) {
  for (int i = 0; i < arr->size; ++i) {
    printf("%lf %s\n", arr->elements[i]->contrast, arr->elements[i]->path);
  }
}

void dyn_arr_sort(dyn_arr* arr) {
  int n = arr->size;
  for (int i = 0; i < n; ++i) {
    for (int j = 1; j < n; ++j) {
      if (arr->elements[j - 1]->contrast > arr->elements[j]->contrast) {
        image_t* temp = arr->elements[j - 1];
        arr->elements[j - 1] = arr->elements[j];
        arr->elements[j] = temp;
      }
    }
  }
}