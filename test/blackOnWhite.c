#include "timg.h"
#include <stdio.h>

int main(int argc, char **argv) {
  
  if(argc < 2) {
    printf("Usage: ./blackOnWhite <outputFileName.png>\n");
    return 1;
  }
  //define some colors
  pixel_t black = {.r=0, .g=0, .b=0, .a=255 };
  pixel_t white  = {.r=255, .g=255, .b=255, .a=255 };


  //define image dimensions
  int height = 500;
  int width = 750;
  int box_h = 200;
  int box_w = 300;
  int box_r = 100;
  int box_c = 175;

  timg_t *img = timg_createfromval(height, width, white);

  int r,c;
  for(r=box_r; r<box_r+box_h; ++r) {
    for(c=box_c; c<box_c+box_w; ++c) {
      *(timg_pixelat(img, r, c)) = black;
    }
  }

  timg_writepng(argv[1], img);
  timg_destroy(img);

  return 0;
}
