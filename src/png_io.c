#include <png.h>
#include <stdlib.h>
#include <stdio.h>

#include "timg.h"

timg_t *timg_readpng(const char *fname) {
  
  FILE *fp = fopen(fname, "rb");

  if(fp == NULL) {
    perror("Could not open PNG for reading");
    exit(1);
  }

  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(!png) {
    perror("png_create_read_struct error");
    exit(1);
  }

  png_infop info = png_create_info_struct(png);
  if(!info) {
    perror("png_create_info_struct error");
    exit(1);
  }

  if(setjmp(png_jmpbuf(png))) {
    perror("setjmp error");
    exit(1);
  }
  
  png_init_io(png, fp);
  png_read_info(png, info);

  int w = png_get_image_width(png, info);
  int h = png_get_image_height(png, info);
  png_byte color_type = png_get_color_type(png, info);
  png_byte bit_depth = png_get_bit_depth(png, info);
  
  if(bit_depth == 16)
    png_set_palette_to_rgb(png);

  if(color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_palette_to_rgb(png);

  if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
    png_set_expand_gray_1_2_4_to_8(png);

  if(png_get_valid(png, info, PNG_INFO_tRNS))
    png_set_tRNS_to_alpha(png);

  if(color_type == PNG_COLOR_TYPE_RGB ||
     color_type == PNG_COLOR_TYPE_GRAY ||
     color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
  
  if(color_type == PNG_COLOR_TYPE_GRAY ||
     color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png);

  png_read_update_info(png, info);
  
  png_bytep *row_pointers = (png_bytep*)malloc(sizeof(png_bytep)*h);
  int i;
  for(i=0; i<h; ++i) {
    row_pointers[i] = (png_byte*)malloc(png_get_rowbytes(png,info));
  }

  png_read_image(png, row_pointers);

  png_read_end(png, NULL);
  png_destroy_read_struct(&png, &info, NULL);

  fclose(fp);

  // convert PNG structure to timg_t
  timg_t *img = timg_create(h,w);
  
  int x,y;
  for(y=0; y<h; ++y) {
    png_bytep row = row_pointers[y];
    for(x=0; x<w; ++x) {
      png_bytep px = &(row[x*4]);
      timg_pixelat(img, y, x)->r = px[0];
      timg_pixelat(img, y, x)->g = px[1];
      timg_pixelat(img, y, x)->b = px[2];
      timg_pixelat(img, y, x)->a = px[3];
    }
    free(row);
  }
  free(row_pointers);

  return img;
}


void timg_writepng(const char *fname, timg_t *img) {
  
  int x,y;
  int BIT_DEPTH = 8;
  FILE *fp = fopen(fname, "wb");
  if(fp == NULL) {
    perror("timg_pngwrite: error opening file for writing");
    exit(1);
  }
  
  png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL);
  if(png==NULL) {
    perror("png_create_write_struct error");
    exit(1);
  }

  png_infop info = png_create_info_struct(png);
  if(info == NULL) {
    perror("png_create_info_struct error");
    exit(1);
  }
  
  if(setjmp(png_jmpbuf(png))) abort();
  
  png_init_io(png, fp);

  png_set_IHDR(png, info, img->width, img->height, BIT_DEPTH,
	       PNG_COLOR_TYPE_RGBA,
	       PNG_INTERLACE_NONE,
	       PNG_COMPRESSION_TYPE_DEFAULT,
	       PNG_FILTER_TYPE_DEFAULT);
  
  png_write_info(png, info);
  
  //allocate row pointers

  int BYTES_PER_ROW = 4*img->width;
  
  png_bytep *row_pointers = (png_bytep*)malloc(sizeof(png_bytep)*img->height);
  for(y=0; y<img->height; ++y) {
    row_pointers[y] = (png_byte*)malloc(BYTES_PER_ROW);
    for(x=0; x<img->width; ++x) {
      png_byte *px = &(row_pointers[y][4*x]);
      px[0] = timg_pixelat(img, y, x)->r;
      px[1] = timg_pixelat(img, y, x)->g;
      px[2] = timg_pixelat(img, y, x)->b;
      px[3] = timg_pixelat(img, y, x)->a;
    }
  }

  png_write_image(png, row_pointers);
  png_write_end(png, NULL);
  png_destroy_write_struct(&png, &info);
  fclose(fp);

  for(y=0; y<img->height; ++y) {
    free(row_pointers[y]);
  }
  free(row_pointers);
  
  return;
}
