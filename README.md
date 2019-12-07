# BMPrinter

This is a header only C++ library that allows you to create an in memory image, change individual pixels in this image and save it into an uncompressed BMP file.

## Usage

Create an image with given width and height:

```c++
BMPImage image(512, 512);
```

Change the pixel in 4th row 3rd column to red:

```c++
image.put(255, 0, 0, 4, 3);
```

Save the image into a file:

```c++
image.save("red.bmp");
```

See example.cpp for an example.