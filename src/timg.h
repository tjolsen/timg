#ifndef _TIMG_H
#define _TIMG_H

#include <inttypes.h>

typedef struct {
  uint8_t r,g,b,a;
} pixel_t;

typedef struct {
  pixel_t *pixels;
  int height, width;
} timg_t;

//create an image
timg_t *timg_createfromval(int h, int w, pixel_t val);
timg_t *timg_create(int h, int w);

timg_t *timg_clone(timg_t *img);

//destroy image
void timg_destroy(timg_t *img);

//pixel manipulation
pixel_t *timg_pixelat(timg_t *img, int row, int col);

//png i/o
timg_t *timg_readpng(const char *fname);
void timg_writepng(const char *fname, timg_t *img);

//jpeg i/o
timg_t *timg_readjpeg(const char *fname);
void timg_writejpeg(const char *fname, timg_t *img);

//tiff i/o
timg_t *timg_readtiff(const char *fname);
void timg_writetiff(const char *fname, timg_t *img);

#endif
