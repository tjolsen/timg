#ifndef _TIMG_DRAWING_H
#define _TIMG_DRAWING_H

#include "timg.h"

#ifdef __cplusplus
extern "C" {
#endif


void timg_drawLine(timg_t *img, int r1, int c1, int r2, int c2, pixel_t p);
void timg_drawRect(timg_t *img, int r1, int c1, int r2, int c2, pixel_t p);
void timg_drawCircle(timg_t *img, int r, int c, int R, pixel_t p);

#ifdef __cplusplus
}
#endif


#endif
