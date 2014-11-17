TIMG
=================================

Timg is a lighweight image handling library library written in C. 
Its original motivation was the desire to write images from programs 
without the use of a larger image-processing library like OpenCV. 
The goal was to create a simple, intuitive API that could be completely 
learned in the span of a few minutes.
The result was (as of right now) only two data structures and a small
set of functions that operate on them.
The library provides very low-level access to the pixel data while
still abstracting away the complexities of interfacing with format-specific
libraries like libpng.

The data structures that have been defined are:

* pixel_t: a struct consisting of four unsigned character members {r, g, b, a},
which correspond to the RGBA channels of the pixel.
* timg_t: a struct containing a pointer to an array of pixel_t's, an integer
for the image height, and an integer for the image width {pixel_t *pixels, int height, int width}

Creation and destruction of a timg_t object should be done via the timg_create() and timg_destroy()
functions in order to ensure proper memory management (nothing fancy, just malloc and free).

Timg is not optimized for fast performance or being small in memory (images are stored in
uncompressed format).
Rather, it is *optimized for ease of use*. 

Timg interfaces with 3rd party open-source libraries to read and write
images to disk. They require the development packages,and  can be installed
with your system's package manager.
Dependancies: 

* libpng-dev
* libjpeg-dev
* libtiff5-dev