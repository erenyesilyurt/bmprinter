#include <iostream>
#include "bmprinter.h"

int main(int argc, char** argv)
{
    BMPImage image(512, 512);

    unsigned char red = 0, green = 0, blue = 0;
    for (int r = 1; r <= 512; r++) {
        for (int c = 1; c <= 512; c++) {
            red = (c/512.0) * 255;
            green = (r/512.0) * 255;
            blue =  (r/512.0) * 255;
            image.put(red, green, blue, r, c);
        }
    }
    image.printDebug();
    image.print();

    image.save("example_output.bmp");
    return 0;
}