#include <math.h>
#include <stdio.h>
#include "timg.h"
#include "timg_drawing.h"


void timg_drawLine(timg_t *img, int r1, int c1, int r2, int c2, pixel_t p) {

  /**
     I don't feel like writing a routine to properly trim the line to fit w/in
     the image, so make sure you're not indexing outside of it.
   */
  
  int r_inc = (r2 >= r1) ? 1 : -1;
  int c_inc = (c2 >= c1) ? 1 : -1;
  
  int r,c;
  if(c1 != c2) {
    double m = ((double)(r2-r1))/((double)(c2-c1));
    for(c=c1; c<c2; c+= c_inc) {
      r = c1 + (int)(m*(c-c1));
      *(timg_pixelat(img,r,c)) = p;
    }
  }

  if(r1 != r2) {
    double m = ((double)(c2-c1))/((double)(r2-r1));
    for(r=r1; r<=r2; r+=r_inc) {
      c = r1 + (int)((r-r1)*m);
      *(timg_pixelat(img,r,c)) = p;
    }
  }
}

void timg_drawRect(timg_t *img, int r1, int c1, int r2, int c2, pixel_t p) {
  
  
  int r,c,rmin,rmax,cmin,cmax;
  rmin = (r1<r2)?r1:r2;
  rmax = (r1<=r2)?r2:r1;
  cmin = (r1<r2)?c1:c2;
  cmax = (c1<=c2)?c2:c1;

  rmin = (rmin<0) ? 0 : rmin;
  rmax = (img->height-1<rmax) ? img->height-1 : rmax;
  cmin = (cmin<0) ? 0 : cmin;
  cmax = (img->width-1<cmax) ? img->width-1 : cmax;

  for(r=rmin; r<=rmax; ++r) {
    for(c=cmin; c<=cmax; ++c) {
      *timg_pixelat(img,r,c) = p;
    }
  }
  
}

void timg_drawCircle(timg_t *img, int ro, int co, int R, pixel_t p) {
  int r,c;
  for(r=ro-R; r<=ro+R; ++r) {
    if(r<0 || r>=img->height)
      continue;

    int dr = ro-r;
    
    double dc = sqrt(((double)(R*R - dr*dr)));
    int idc = (int)(dc + 0.5); //easy way to round to nearest int
    c = co - idc;
    if(c>=0 && c<img->width)
      *timg_pixelat(img,r,c) = p;
    c = co + idc;
    if(c>=0 && c<img->width)
      *timg_pixelat(img,r,c) = p;
  }

  for(c = co-R; c<=co+R; ++c) {
    if(c<0 || c>=img->width)
      continue;
    
    int dc = co-c;
    
    double dr = sqrt(((double)(R*R - dc*dc)));
    int idr = (int)(dr+0.5);
    
    r = ro - idr;
    if(r>=0 && r < img->height)
      *timg_pixelat(img,r,c) = p;

    r = ro + idr;
    if(r>=0 && r < img->height)
      *timg_pixelat(img,r,c) = p;
  }
}

void timg_drawFilledCircle(timg_t *img, int ro, int co, int R, pixel_t p) {
  int r,c;
  for(r=ro-R; r<=ro+R; ++r) {
    if(r<0 || r>=img->height)
      continue;

    int dr = ro-r;
    
    double dc = sqrt(((double)(R*R - dr*dr)));
    int idc = (int)(dc + 0.5); //easy way to round to nearest int
    for(c = co-idc; c<=co+idc; ++c) {
      if(c<0 || c>=img->width)
	continue;

      *timg_pixelat(img,r,c) = p;
    }
  }
  
}
