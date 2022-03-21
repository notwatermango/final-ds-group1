#include "filters.h"
#include <stdio.h>

bool check_greyscale(image_t* img) {
  for (int i = 0; i < (img->data_size); i+=3)
  {
    u8 r = img->data[i+2];
    u8 g = img->data[i+1];
    u8 b = img->data[i];
    if(r != g || g != b) {
      #ifdef DEBUG
      printf("%d ", r);
      printf("%d ", g);
      printf("%d\n", b);
      #endif
      return false;
    }
  }
  return true;
}

void contoh_function() {
  puts("Welcome");
}