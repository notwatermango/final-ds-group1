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
#include <time.h>
#include "avl.h"

int main() {
  welcome_function(); /* prints welcome */
  char** fileList = printdir("./images");
  int size = 0;

  clock_t begin = clock();

  dyn_arr* arr = dyn_arr_init();
  avl_node_t* tree = NULL;

  // Untuk dynamic array
  for (int i = 0; i < 24; i++) {
    if (fileList[i] == NULL) break;
    char* fileWithPath = concat(fileList[i]);
    image_t* img = open_img(fileWithPath);
    if (img == NULL) {
      puts("bad img");
      continue;
    }
    free(img->data);
    img->data = NULL;
    dyn_arr_insert(arr, img);
    size++;
  }

  puts("--------- Dynamic Array (Sorted) ---------");
  dyn_arr_sort(arr);
  dyn_arr_display(arr);
  clock_t end = clock();
  double timeDynArr = (double)(end - begin) / CLOCKS_PER_SEC;

  begin = clock();
  // Untuk AVL Tree
  for (int i = 0; i < 24; i++) {
    if (fileList[i] == NULL) break;
    char* fileWithPath = concat(fileList[i]);
    image_t* img = open_img(fileWithPath);
    if (img == NULL) {
      puts("bad img");
      continue;
    }
    free(img->data);
    img->data = NULL;
    tree = avl_insert(tree, img);
  }
  end = clock();

  puts("\n---------------- AVL Tree -----------------");
  avl_display(tree);
  double timeAVLTree = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("\n%lfs Time for Dynamic Array (Insert, Sorting and Display)", timeDynArr);
  printf("\n%lfs Time for AVL Tree (Insert and Display)", timeAVLTree);
  return 0;
}