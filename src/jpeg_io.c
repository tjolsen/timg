#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <jpeglib.h>
#include "timg.h"

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


