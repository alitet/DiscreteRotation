#include "vixel.h"
#include <iostream>
#include <cmath>

sPixelImage::sPixelImage(const char* fname)
{
  Image image = LoadImage(fname);
  std::cout << "[" << image.width << "," << image.height << "]" << std::endl;
  Color* clrs = LoadImageColors(image);
  ws = image.width;
  hs = image.height;
  //pixeles.resize(ws * hs);

  dims.minw = static_cast<int16_t>(ws / 2);
  dims.minh = static_cast<int16_t>(hs / 2);
  dims.maxw = ws - dims.minw;
  dims.maxh = hs - dims.minh;

  for (int16_t i = 0; i < image.width * image.height; i++) {
    pixeles.push_back(clrs[i]);
  }
  UnloadImage(image);
}
