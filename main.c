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
  char** fileList = printdir("./images");
  int listFile;
  listFile = sizeof(fileList) / sizeof(char);
  for (int i = 0; i < listFile; i++) {
    char* fileWithPath = concat(fileList[i]);
    image_t* img = open_img(fileWithPath);
    if (img == NULL) { puts("bad img");return 0; }

    /* test function here */
    puts("---?greyscale?---");
    if (img->greyscale) puts("yey it's greyscale");
    else puts("not greyscale");

    puts("---?color dominant?---");
    if (img->dominant == NONE) printf("no dominant color\n");
    if (img->dominant == RED) printf("dominant red\n");
    if (img->dominant == BLUE) printf("dominant blue\n");
    if (img->dominant == GREEN) printf("dominant green\n");

    puts("---?contrast?---");
    printf("RMS contrast val: %lf\n", img->contrast);
    free(fileWithPath);
  }
  return 0;
}