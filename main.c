/*
  debug @ _debug.h
*/
#include "_debug.h"
#include "file_handling.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

int main() {
  contoh_function(); /* prints welcome */
  image_t* img = open_img("./images/tes_red_24.bmp");
  if(img == NULL) {puts("bad img");return 0;}

  /* test function here */
  if(img->greyscale) puts("yey it's greyscale");
  else puts("not greyscale");


  return 0;
}