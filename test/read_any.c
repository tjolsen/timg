#include "timg.h"
#include <stdio.h>

int main(int argc, char **argv) {
  
  if(argc < 3) {
    printf("usage: inputFilename outputfileName");
    return 1;
  }
  
  printf("fname: %s\n", argv[1]);
  
  timg_t *img = timg_read(argv[1]);
  if(img == NULL) {
    printf("Bad read\n");
    return 1;
  }
  
  timg_write(argv[2],img);

  timg_destroy(img);
  
  return 0;
}
