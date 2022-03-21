#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#undef notwatermango
#define msg(x)
#ifdef notwatermango
#undef msg
#define msg(x) puts(x)
#endif

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int32_t i32;
typedef int64_t i64;

/* pack struct dalam byte; bmp header 54 bytes */
#pragma pack(push, 1) 
typedef struct header_s {
  u16 type;          
  u32 size_bytes;
  u16 reserved1;
  u16 reserved2;
  u32 offset; 
  u32 header_size_bytes;
  u32 width_px;
  u32 height_px;        
  u16 planes;            
  u16 bits_perpx;
  u32 compression_type;
  u32 imagesize_bytes;
  u32 xresolution_pxperm;
  u32 yresolution_pxperm;
  u32 numofcolors;            
  u32 importantcolors;
} header_t;
/* pack default */
#pragma pack(pop)

/* metadata */
typedef struct image_s {
  header_t header;
  u32 data_size;
  u32 bytes_perpx;
  u32 width_px;
  u32 height_px;
  u8* data;
  bool greyscale;
} image_t;


bool check_grayscale(image_t* img) {
  for (int i = 0; i < (img->data_size); i+=3)
  {
    u8 r = img->data[i+2];
    u8 g = img->data[i+1];
    u8 b = img->data[i];
    if(r != g || g != b) {
      printf("%d ", r);
      printf("%d ", g);
      printf("%d\n", b);
      return false;
    }
  }
  return true;
}

image_t* open_img(char *filename) {
  printf("try %s\n", filename);
  FILE* fp = fopen(filename, "r");
  if(fp == NULL) return NULL; 
  msg("fp ok");
  image_t* img = (image_t*) malloc(sizeof(image_t));
  if(fread(&(img->header), sizeof(header_t), 1, fp) != 1) {fclose(fp);free(img);return NULL;} 
  msg("header ok");
  img->data_size = (img->header).size_bytes - sizeof(header_t);
  img->width_px = (img->header).width_px;
  img->height_px = (img->header).height_px;
  img->bytes_perpx = (img->header).bits_perpx/8;
  if(img->header.bits_perpx != 24) {printf("bpp: %d\nbpp/bit depth should be 24\n", img->header.bits_perpx);fclose(fp);free(img);return NULL;}
  img->data = malloc(sizeof(u8) * (img->data_size));
  if(fread(img->data, sizeof(u8), img->data_size, fp) != img->data_size) {fclose(fp);free(img);return NULL;} 
  msg("datasize ok");

  img->greyscale = check_grayscale(img);
  fclose(fp);
  return img;
}

int main() {
  image_t* img = open_img("./images/tes_bnw_24.bmp");
  if(img == NULL) {puts("bad img");return 0;}
  if(img->greyscale) puts("yey it's greyscale");
  else puts("not greyscale");
  return 0;
}