#include "timg.h"
#include "timg_instagram.h"
#include <stdio.h>

int main(int argc, char **argv) {
  
  if(argc < 3) {
    printf("Supply rgb image name and grayscale image name\n");
    return 1;
  }

  timg_t *img = timg_read(argv[1]);
  if(img == NULL) {
    printf("Bad image read\n");
    return 1;
  }
  
  timg_t *gray = timg_grayscale(img);
  
  timg_write(argv[2],gray);
  timg_destroy(img);
  timg_destroy(gray);
  return 0;
}
