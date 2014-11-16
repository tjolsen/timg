#include <tiffio.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "timg.h"


timg_t *timg_readtiff(const char *fname) {
  
  TIFF *tif = TIFFOpen(fname, "r");
  
  uint32_t width=0, height=0;
  TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);
  TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height);
  
  uint32_t *raster = (uint32_t*)_TIFFmalloc(width*height*sizeof(uint32_t));
  
  if(TIFFReadRGBAImage(tif, width, height, raster, 0) == 0) {
    fprintf(stderr, "An error occurred reading the TIFF file.\n");
    exit(1);
  }
  
  timg_t *img = timg_create(height, width);
  
  int i;
  for(i=0; i<height*width; ++i) {
    img->pixels[i].r = (uint8_t)TIFFGetR(raster[i]);
    img->pixels[i].g = (uint8_t)TIFFGetG(raster[i]);
    img->pixels[i].b = (uint8_t)TIFFGetB(raster[i]);
    img->pixels[i].a = (uint8_t)TIFFGetA(raster[i]);
  }

  _TIFFfree(raster);
  TIFFClose(tif);
  
  return img;
}


void timg_writetiff(const char *fname, timg_t *img) {
  
  
  
}
