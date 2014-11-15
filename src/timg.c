#include "timg.h"
#include <stdlib.h>
#include <stdio.h>

timg_t *timg_createfromval(int h, int w, pixel_t val) {
  
  if(h<=0 || w<=0) {
    perror("Invalid timg_create dimensions");
    exit(1);
  }
  
  int npixels = h*w;
  
  timg_t *img = (timg_t*)malloc(sizeof(timg_t));
  img->pixels = (pixel_t*)malloc(npixels*sizeof(pixel_t));
  
  int i;
  for(i=0; i<npixels; ++i) {
    img->pixels[i] = val;
  }

  img->height = h;
  img->width = w;

  return img;
}

timg_t *timg_create(int h, int w) {
  
  pixel_t val;
  val.r=0; val.g=0; val.b=0; val.a=255;

  return timg_createfromval(h,w,val);
}

timg_t *timg_clone(timg_t *img) {
  
  timg_t *clone = timg_create(img->height, img->width);
  
  int i, j;
  for(i=0; i<img->height; ++i) {
    for(j=0; j<img->width; ++j) {
      timg_pixelat(clone, i, j)->r = timg_pixelat(img, i, j)->r;
      timg_pixelat(clone, i, j)->g = timg_pixelat(img, i, j)->g;
      timg_pixelat(clone, i, j)->b = timg_pixelat(img, i, j)->b;
      timg_pixelat(clone, i, j)->a = timg_pixelat(img, i, j)->a;
    }
  }
  
  return clone;
}

void timg_destroy(timg_t *img) {
  free(img->pixels);
  free(img);
  return;
}

pixel_t *timg_pixelat(timg_t *img, int row, int col) {

  if(row >= img->height || col >= img->width || row<0 || col<0) {
    perror("Error: timg_pixelat: attempted to index outside image");
    exit(1);
  }

  int index = row*(img->width) + col;

  return &(img->pixels[index]);
}

