#include "timg_instagram.h"


timg_t* timg_grayscale(timg_t *in) {

  timg_t *out = timg_create(in->height, in->width);
  
  unsigned i;
  pixel_t *inpx = in->pixels;
  for(i=0; i<(in->height)*(in->width); ++i) {
    unsigned char val=0;
    val = (unsigned char)(0.2126*inpx[i].r + 0.7152*inpx[i].g + 0.0722*inpx[i].b);
    out->pixels[i].r = val;
    out->pixels[i].g = val;
    out->pixels[i].b = val;
    out->pixels[i].a = inpx[i].a;
  }
  
  return out;
}

timg_t* timg_sepia(timg_t *in) {

  timg_t *out = timg_create(in->height, in->width);
  
  // hand-set global parameter to adjust brightness of output
  double f_global = 0.9;

  unsigned i;
  pixel_t *inpx = in->pixels;
  for(i=0; i<(in->height)*(in->width); ++i) {
    double val = (0.2126*inpx[i].r + 0.7152*inpx[i].g + 0.0722*inpx[i].b);
    double fr = (0.393 + 0.769 + 0.189)*f_global;
    double fg = (0.349 + .686 + .168)*f_global;
    double fb = (0.272 + 0.534 + 0.131)*f_global;
    
    out->pixels[i].r = (unsigned char)((fr*val<255)?fr*val : 255);
    out->pixels[i].g = (unsigned char)((fg*val<255)?fg*val : 255);
    out->pixels[i].b = (unsigned char)((fb*val<255)?fb*val : 255);
    out->pixels[i].a = inpx[i].a;
  }
  
  return out;
}
