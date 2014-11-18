#include "timg.h"
#include "timg_drawing.h"

int main() {
  
  pixel_t white = {.r=255, .g=255, .b=255, .a=255};
  pixel_t black = {.r=0, .g=0, .b=0, .a=255};
  timg_t *img = timg_createfromval(500, 500, white);
  
  timg_drawLine(img, 100, 100, 100, 200, black);
  timg_drawLine(img, 100, 100, 200, 200, black);
  timg_drawLine(img, 100, 100, 200, 100, black);

  timg_drawRect(img, 200,200,300,300, black);
  timg_drawCircle(img, 350,350, 100, black);

  timg_writepng("linepng.png", img);
  
  timg_destroy(img);
  return 0;
}
