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
  puts("---?greyscale?---");
  if(img->greyscale) puts("yey it's greyscale");
  else puts("not greyscale");

  puts("---?color dominant?---");
  if(img->dominant == NONE) printf("no dominant color\n"); 
  if(img->dominant == RED) printf("dominant red\n");
  if(img->dominant == BLUE) printf("dominant blue\n");
  if(img->dominant == GREEN) printf("dominant green\n");



  return 0;
}