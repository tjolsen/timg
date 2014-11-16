#include "timg.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  
  pixel_t white = {.r=255, .g=255, .b=255, .a=255};
  
  timg_t *img = timg_createfromval(500,500, white);
  
  int r,c;
  for(r=0; r<img->height; ++r) {
    for(c=0; c<img->width; ++c) {
      timg_pixelat(img, r, c)->r = (r%256);
    }
  }
  
  timg_writetiff("mytiff.tif",img);
  timg_writepng("mytiff.png",img);
  
  timg_destroy(img);
  return 0;
}
