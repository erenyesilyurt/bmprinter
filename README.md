# BMPrinter

This is a header only C++ library that allows you to create an image, change individual pixels in this image and save it into an uncompressed RGB .bmp file.

## Usage

Create an image with given width and height:

```c++
BMPImage image(512, 512);
```

Change the pixel in 4th row 3rd column to red:

```c++
image.put(1.0, 0, 0, 4, 3);
```

Save the image into a file:

```c++
image.save("redpixel.bmp");
```

See example.cpp for an example.