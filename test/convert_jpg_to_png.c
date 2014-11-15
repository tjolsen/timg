#include <stdio.h>
#include <stdlib.h>
#include "timg.h"

int main(int argc, char **argv) {

  if(argc < 3) {
    printf("Supply input and output file names.\n");
    return 1;
  }
  
  timg_t *img = timg_readjpeg(argv[1]);
  timg_writepng(argv[2], img);
  
  timg_destroy(img);

  return 0;
}
