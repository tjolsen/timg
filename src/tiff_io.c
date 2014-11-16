#include <tiffio.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
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
  
  TIFF *tif = TIFFOpen(fname, "w");
  
  if(tif == 0) {
    fprintf(stderr, "timg_writetiff: Failed to open %s\n", fname);
    exit(1);
  }

  int w = img->width;
  int h = img->height;
  
  TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, w);
  TIFFSetField(tif, TIFFTAG_IMAGELENGTH, h);
  TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 4);
  TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
  TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
  TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
  TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
  
  int linebytes = 4*w;
  
  unsigned char *buf = NULL;
  
  if(TIFFScanlineSize(tif) == linebytes) {
    buf = (unsigned char*)_TIFFmalloc(linebytes);
  } else {
    buf = (unsigned char*)_TIFFmalloc(TIFFScanlineSize(tif));
  }

  if(buf == NULL) {
    fprintf(stderr, "timg_writetiff: failed to allocate buf");
    exit(1);
  }

  TIFFSetField(tif,TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize(tif, w*4));

  int row=0;
  for(row=0; row<h; ++row) {
    //memcpy(buf, timg_pixelat(img, row, 0), linebytes);
    if(TIFFWriteScanline(tif, &(img->pixels[row*img->width]), row, 0) < 0)
      break;
  }

  if(buf)
    _TIFFfree(buf);

  TIFFClose(tif);
}
