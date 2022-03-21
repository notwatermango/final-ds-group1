#ifndef STRUCTS_H
#define STRUCTS_H
#include "typedefs.h"
#include<stdint.h>
#include<stdbool.h>
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
#endif