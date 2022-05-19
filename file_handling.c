#include "file_handling.h"
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

const char* path = "./images/";
image_t* open_img(char* filename) {
  printf("try %s\n", filename);
  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    msg("fail fp");
    return NULL;
  }
  msg("fp ok");
  image_t* img = (image_t*)malloc(sizeof(image_t));
  if (fread(&(img->header), sizeof(header_t), 1, fp) != 1) { fclose(fp);free(img);return NULL; }
  msg("header ok");
  img->width_px = (img->header).width_px;
  img->height_px = (img->header).height_px;
  img->bytes_perpx = (img->header).bits_perpx / 8;
  img->data_size = (img->header).size_bytes - sizeof(header_t);

  if (img->header.bits_perpx != 24) { printf("bpp: %d\nbpp/bit depth should be 24\n", img->header.bits_perpx);fclose(fp);free(img);return NULL; }
  msg("bpp ok");

  if ((img->header).compression_type) puts("bruh compressed");
  if ((img->header).planes > 1 || (img->header).planes < 1) puts("bruh multiplane");
  img->data = malloc(sizeof(u8) * (img->data_size));
  if (fread(img->data, sizeof(u8), img->data_size, fp) != img->data_size) { fclose(fp);free(img);return NULL; }
  msg("datasize ok");

  img->dominant = get_dominant_color(img);
  img->greyscale = check_greyscale(img);
  img->contrast = get_rms_contrast(img);

  fclose(fp);
  return img;
}

char** printdir(char* dir) {
  DIR* dp;
  struct dirent* entry;
  struct stat statbuf;
  // ini dikali sama banyaknya file, kalo mau otomatis kayanya bisa tinggal while bawah(?) tapi gak efisien
  // masih bingunk
  char** fileList = malloc(sizeof(char*) * 6);
  if ((dp = opendir(dir)) == NULL) {
    fprintf(stderr, "cannot open directory: %s\n", dir);
  }
  else {
    chdir(dir);
    // ada .. sama ., kita skip.
    int i = 0;
    while ((entry = readdir(dp)) != NULL) {
      if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) {
        continue;
      }
      fileList[i] = malloc(sizeof(char*) * strlen(entry->d_name));
      strcpy(fileList[i], entry->d_name);
      i++;
    }
    chdir("..");
    closedir(dp);
    return fileList;
  }
}

char* concat(const char* nameFile) {
  char* result = malloc(strlen(path) + strlen(nameFile) + 1);
  strcpy(result, path);
  strcat(result, nameFile);
  return result;
}