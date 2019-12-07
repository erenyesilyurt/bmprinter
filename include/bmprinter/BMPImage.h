#ifndef BMPPRINTER_BMPIMAGE_H_
#define BMPPRINTER_BMPIMAGE_H_

#include "bmpdefs.h"
#include "stdio.h"

class BMPImage {
public:
    BMPImage(const int width, const int height) 
        : _width{width}, _height{height}, _size{width * height * (_bits_per_pixel/8)}
    {
        int row_width = (_bits_per_pixel/8) * _width;
        _row_padding = 4 - (row_width % 4);
        if (_row_padding == 4)
            _row_padding = 0;
        pixels = new Pixel[width * height] (); // clear alloc
    }

    ~BMPImage()
    {
        delete[] pixels;
    }

    // Put pixel with given RGB values into the specified row and column of the image. Indexes start from (1,1) top left.
    void put(BYTE red, BYTE green, BYTE blue, int row, int col)
    {
        if ((row > 0 && row <= _width) && (col > 0 && col <= _height)) {
            int pos = (row-1)*_width + (col-1);
            pixels[pos] = {red, green, blue};
        }
    }

    // prints ASCII representation of image to stdout
    void print()
    {
        for (int r = 0; r < _width; r++) {
            printf("\n| ");
            for (int c = 0; c < _height; c++) {
                Pixel p = pixels[r*_width + c];
                printf("%3d %3d %3d | ", p.red, p.green, p.blue);
            }
        }
        printf("\n\n");
    }

    // print some information about the image
    void printDebug()
    {
        printf("width: %i, height: %i\n", _width, _height);
        printf("size(bytes, no padding): %i\n", _size);
        printf("row padding(bytes): %i\n", _row_padding);
    }

    // create a .bmp file with given name and save it
    void save(const char *filename)
    {
        FILE *file;
        file = fopen(filename, "wb");

        if (!file)
        {
            fprintf(stderr, "Error writing to %s.", filename);
            return;
        }

        // BMPFileHeader: 14 bytes
        BITMAPFILEHEADER file_header {};
        file_header.bfSize = 14 + 40 + (_size + _row_padding * _height);
        file_header.bfType = ('M' << 8) + 'B';
        file_header.bfOffBits = 54;

        // BMPInfoHeader: 40 bytes
        BITMAPINFOHEADER info_header {};
        info_header.biSize = 40; 
        info_header.biWidth = _width;
        info_header.biHeight = -_height;
        info_header.biPlanes = 1;
        info_header.biBitCount = _bits_per_pixel;

        fwrite(&file_header, sizeof(BITMAPFILEHEADER), 1, file);
        fwrite(&info_header, sizeof(BITMAPINFOHEADER), 1, file);

        BYTE padding = 0x00;
        for (int r = 0; r < _height; r++) {
            for (int c = 0; c < _height; c++) {
                Pixel p = pixels[r*_width + c];
                fwrite(&(p.blue), 1, 1, file);
                fwrite(&(p.green), 1, 1, file);
                fwrite(&(p.red), 1, 1, file);
            }
            for (int i = _row_padding; i > 0; i--) {
                fwrite(&padding, 1, 1, file);
            }
        }

        fclose(file);
    }
private:
    const int _bits_per_pixel = 24;
    const int _width, _height;
    const int _size;
    int _row_padding;
    Pixel *pixels;
};

#endif