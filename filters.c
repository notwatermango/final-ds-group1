#include "filters.h"
#include <stdio.h>

inline u64 min(u64 a, u64 b) {return (a>b?b:a);}
inline u64 max(u64 a, u64 b) {return (a>b?a:b);}

bool check_greyscale(image_t* img) {
  for (int i = 0; i < (img->data_size); i+=3)
  {
    u8 r = img->data[i+2], g = img->data[i+1], b = img->data[i];
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

colors_t get_dominant_color(image_t* img) {
  u64 rsum, gsum, bsum; rsum = gsum = bsum = 0;
  for (int i = 0; i < (img->data_size); i+=3)
  {
    u64 r = img->data[i+2], g = img->data[i+1], b = img->data[i];
    u64 lmin = min(r, min(g, b));
    rsum += r-lmin; gsum += g-lmin; bsum += b-lmin;
  }
  u64 max_sum = max(rsum, max(gsum, bsum)), min_sum = min(rsum, min(gsum, bsum));
  #ifdef DEBUG
  printf("R: %d | G: %d | B: %d | %d %d\n", rsum, gsum, bsum, max_sum, min_sum);
  #endif
  /* dominant : is max && avg value > 21 from others  (? oke ga ? masih ngide)*/
  if(max_sum == rsum && rsum > gsum+(7*(img->data_size)) && rsum > bsum+(7*(img->data_size))) return RED;
  if(max_sum == gsum && gsum > rsum+(7*(img->data_size)) && gsum > bsum+(7*(img->data_size))) return GREEN;
  if(max_sum == bsum && bsum > rsum+(7*(img->data_size)) && bsum > gsum+(7*(img->data_size))) return BLUE;
  return NONE;
}

void contoh_function() {
  puts("Welcome");
}