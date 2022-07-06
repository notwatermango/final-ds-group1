/*
  debug @ _debug.h
*/
#include "_debug.h"
#include "file_handling.h"
#include "dynamic_arr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "avl.h"

int main() {
  contoh_function(); /* prints welcome */
  char** fileList = printdir("./images");
  int listFile;
  int size = 0;
  listFile = sizeof(fileList) / sizeof(char);

  dyn_arr* arr = dyn_arr_init();
  avl_node_t* tree = NULL;

  for (int i = 0; i < 24; i++) {
    if (fileList[i] == NULL) break;
    printf("%s\n", fileList[i]);
    char* fileWithPath = concat(fileList[i]);
    image_t* img = open_img(fileWithPath);
    if (img == NULL) {
      puts("bad img");
      // return 0;
      // kalo error, continue aja dulu, tapi kalo udah masuk data fix error++
      continue;
    }
    free(img->data);
    img->data = NULL;
    puts("1");
    dyn_arr_insert(arr, img);
    puts("2");
    tree = avl_insert(tree, img);
    puts("3");
    /* test function here */

    // puts("---?greyscale?---");
    // if (img->greyscale) puts("yey it's greyscale");
    // else puts("not greyscale");

    // puts("---?color dominant?---");
    // if (img->dominant == NONE) printf("no dominant color\n");
    // if (img->dominant == RED) printf("dominant red\n");
    // if (img->dominant == BLUE) printf("dominant blue\n");
    // if (img->dominant == GREEN) printf("dominant green\n");

    // puts("---?contrast?---");
    printf("RMS contrast val: %lf\n", img->contrast);
    size++;
  }
  puts("----------arr---------");
  dyn_arr_sort(arr);
  dyn_arr_display(arr);
  puts("----------tree--------");
  avl_display(tree);
  return 0;
}