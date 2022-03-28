#include "lodepng/lodepng.c"
struct rgba
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} rgba_data[300][300];

void readFromFile(char *fileName) {
    uivector byteData;
    unsigned error = decode(byteData, 300, 300, fileName);
    if (error) {
        printf("PNG decoder error");
        return ;
    }
    unsigned i = 0;
    unsigned x = 0;
    unsigned y = 0;
    for (x = 0; x < 300; x++) {
        for (y = 0; y < 300; y++) {
            rgba_data.r = byteData[i];
            rgba_data.g = byteData[i + 1];
            rgba_data.b = byteData[i + 2];
            rgba_data.a = byteData[i + 3];
            i += 4;
        }
    }
}

