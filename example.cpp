#include <iostream>
#include "bmprinter.h"

using namespace bmprinter;

int main(int argc, char** argv)
{
    BMPImage image(512, 512);

    float red, green, blue;
    for (int r = 1; r <= 512; r++) {
        for (int c = 1; c <= 512; c++) {
            red = (c/512.0);
            green = (r/512.0);
            blue =  (r/512.0);
            image.put(red, green, blue, r, c);
        }
    }

    //image.printInfo();
    //image.print();

    image.save("example_output.bmp");
    return 0;
}