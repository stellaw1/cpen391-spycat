#include "lodepng/lodepng.c"
struct rgba
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} rgba_data[300][300];

void readFromFile(const char* filename) {
  unsigned error;
  unsigned char* image;
  unsigned w, h, x, y;
  size_t jump = 1;
  w = 300;
  h = 300;
  /*load the PNG in one function call*/
  error = lodepng_decode32_file(&image, &w, &h, filename);
  /*stop if there is an error*/
  if(error) {
    printf("decoder error %u: %s\n", error, lodepng_error_text(error));
    return ;
  }
  /*plot the pixels of the PNG file*/
  for(y = 0; y + jump - 1 < h; y += jump)
  for(x = 0; x + jump - 1 < w; x += jump) {
    /*get RGBA components*/
    rgba_data[x][y].r = image[4 * y * w + 4 * x + 0]; /*red*/
    rgba_data[x][y].g = image[4 * y * w + 4 * x + 1]; /*green*/
    rgba_data[x][y].b = image[4 * y * w + 4 * x + 2]; /*blue*/
    rgba_data[x][y].a = image[4 * y * w + 4 * x + 3]; /*alpha*/
  }
}

void drawPNGonScreen(char *filename, int topleft_x, int topleft_y, int Colour) {
    readFromFile(filename);
    unsigned x = 0;
    unsigned y = 0;
    for (x = 0; x < 300; x++) {
        for (y = 0; y < 300; y++){
            if (rgba_data[x][y].a != 0) {
                printf("print1pixel");
                //WriteAPixel (x + topleft_x, y + topleft_y, Colour);
            }
        }
    }
}