#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <jpeglib.h>
#include "timg.h"

timg_t *timg_readjpeg(const char *fname) {
  
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);
  
  FILE *infile;
  if((infile = fopen(fname, "r")) == NULL) {
    fprintf(stderr, "Could not open %s\n", fname);
    exit(1);
  }

  jpeg_stdio_src(&cinfo, infile);
  
  jpeg_read_header(&cinfo, TRUE);
  
  jpeg_start_decompress(&cinfo);

  int w = cinfo.output_width;
  int h = cinfo.output_height;
  int nComps = cinfo.output_components;
  
  //initialize timg object
  timg_t *img = timg_create(h,w);
  
  uint8_t *buf = (uint8_t*)malloc(w*nComps);
  JSAMPROW row_ptr[1];
  while(cinfo.output_scanline < cinfo.image_height) {
    row_ptr[0] = buf;
    int r = cinfo.output_scanline;
    jpeg_read_scanlines(&cinfo, row_ptr, 1);

    int c;
    for(c=0; c<w; ++c) {
      if(nComps == 1) { //grayscale
	timg_pixelat(img, r, c)->r = buf[c];
	timg_pixelat(img, r, c)->g = buf[c];
	timg_pixelat(img, r, c)->b = buf[c];
	timg_pixelat(img, cinfo.output_scanline, c)->a = 255;
      }
      else if(nComps == 3) { //RGB
	timg_pixelat(img, r, c)->r = buf[nComps*c + 0];
	timg_pixelat(img, r, c)->g = buf[nComps*c + 1];
	timg_pixelat(img, r, c)->b = buf[nComps*c + 2];
	timg_pixelat(img, r, c)->a = 255;
      }
      else {
	fprintf(stderr, "timg_readjpeg: Neither 1 nor three color components. Something wrong.\n");
	exit(1);
      }
    }
  }

  jpeg_finish_decompress(&cinfo);
  fclose(infile);
  jpeg_destroy_decompress(&cinfo);

  return img;
}

void timg_writejpeg(const char *fname, timg_t *img) {

  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);

  FILE *outfile;
  if((outfile=fopen(fname,"w")) == NULL ) {
    fprintf(stderr, "Could not open %s\n", fname);
    exit(1);
  }

  jpeg_stdio_dest(&cinfo, outfile);
  
  cinfo.image_width = img->width;
  cinfo.image_height = img->height;
  cinfo.input_components = 3;
  cinfo.in_color_space = JCS_RGB;
  jpeg_set_defaults(&cinfo);

  //begin compression
  jpeg_start_compress(&cinfo, TRUE);

  JSAMPROW row_ptr[1];
  uint8_t *row = (uint8_t*)malloc(3*(img->width)*sizeof(uint8_t));
  while(cinfo.next_scanline < cinfo.image_height) {
    //copy next scanline into "row", stripping alpha channel in the process
    int c;
    for(c=0; c<(img->width); ++c) {
      row[3*c + 0] = timg_pixelat(img, cinfo.next_scanline, c)->r;
      row[3*c + 1] = timg_pixelat(img, cinfo.next_scanline, c)->g;
      row[3*c + 2] = timg_pixelat(img, cinfo.next_scanline, c)->b;
    }
    
    row_ptr[0] = row;
    jpeg_write_scanlines(&cinfo,row_ptr,1);
  }


  jpeg_finish_compress(&cinfo);
  fclose(outfile);

  //clean up
  free(row);
  jpeg_destroy_compress(&cinfo);

  return;
}


