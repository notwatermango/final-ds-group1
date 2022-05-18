#include "file_handling.h"
#include <stdio.h>
#include <stdlib.h>
image_t* open_img(char *filename) {
  printf("try %s\n", filename);
  FILE* fp = fopen(filename, "r");
  if(fp == NULL) {
    msg("fail fp");
    return NULL; 
  }
  msg("fp ok");
  image_t* img = (image_t*) malloc(sizeof(image_t));
  if(fread(&(img->header), sizeof(header_t), 1, fp) != 1) {fclose(fp);free(img);return NULL;} 
  msg("header ok");
  img->width_px = (img->header).width_px;
  img->height_px = (img->header).height_px;
  img->bytes_perpx = (img->header).bits_perpx/8;
  img->data_size = (img->header).size_bytes - sizeof(header_t);

  if(img->header.bits_perpx != 24) {printf("bpp: %d\nbpp/bit depth should be 24\n", img->header.bits_perpx);fclose(fp);free(img);return NULL;}
  msg("bpp ok");

  if((img->header).compression_type) puts("bruh compressed");
  if((img->header).planes > 1 || (img->header).planes < 1) puts("bruh multiplane");
  img->data = malloc(sizeof(u8) * (img->data_size));
  if(fread(img->data, sizeof(u8), img->data_size, fp) != img->data_size) {fclose(fp);free(img);return NULL;} 
  msg("datasize ok");

  img->dominant = get_dominant_color(img);
  img->greyscale = check_greyscale(img);
  img->contrast = get_rms_contrast(img);

  fclose(fp);
  return img;
}