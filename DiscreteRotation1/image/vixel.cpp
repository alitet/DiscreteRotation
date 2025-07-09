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

  dims.minw = static_cast<int16_t>(ws / 2);
  dims.minh = static_cast<int16_t>(hs / 2);
  dims.maxw = ws - dims.minw;
  dims.maxh = hs - dims.minh;

  for (int16_t i = 0; i < image.width * image.height; i++) {
    pixels.push_back(sPix{ clrs[i], BLACK, 100, 0 });
  }
  UnloadImage(image);
}

sPixelImage::sPixelImage(uint16_t w, uint16_t h)
{
  ws = w;
  hs = h;

  dims.minw = static_cast<int16_t>(ws / 2);
  dims.minh = static_cast<int16_t>(hs / 2);
  dims.maxw = ws - dims.minw;
  dims.maxh = hs - dims.minh;

  Color noclr{ 255, 0, 255, 255 };
  for (int16_t i = 0; i < w * h; i++) {
    pixels.push_back(sPix{ noclr, BLACK, 100, 0 });
  }
}

sPix sPixelImage::getPixel(int16_t x, int16_t y) const
{
  int16_t nx = x + dims.minw;
  int16_t ny = -y + dims.maxh - 1;
  return pixels[ny * ws + nx];
}

Color sPixelImage::getPixelMerge(int16_t x, int16_t y) const
{
  int16_t nx = x + dims.minw;
  int16_t ny = -y + dims.maxh - 1;
  sPix px = pixels[ny * ws + nx];

  return mixColorPixs(px);
}

void sPixelImage::setPixelMerge(int16_t x, int16_t y, sPix pix)
{
  int16_t nx = x + dims.minw;
  int16_t ny = -y + dims.maxh - 1;
  pixels[ny * ws + nx] = pix;
}

bool sPixelImage::isKeyColor(const Color& clr) const
{
  return clr.r == 255 && clr.g == 0 && clr.b == 255;
}

void sPixelImage::clearAllPixel()
{
  for (sPix& clr : pixels) {
    Color noclr{ 255, 0, 255, 255 };
    clr = sPix{ noclr, BLACK, 100, 0 };
  }
}

Color sPixelImage::mixColorPixs(sPix piz) const
{
  int8_t chkpr = piz.aper + piz.bper;
  if (chkpr > 100 || chkpr < 100) {
    return BLACK;
  }
  uint8_t cmp1[3]{ piz.acol.r, piz.acol.g, piz.acol.b };
  uint8_t cmp2[3]{ piz.bcol.r, piz.bcol.g, piz.bcol.b };
  float per1 = piz.aper / 100.f;
  float per2 = piz.bper / 100.f;

  uint8_t cmerg[3];
  for (uint8_t i = 0; i < 3; i++) {
    float cmvl = cmp1[i] * per1 + cmp2[i] * per2;
    uint8_t mgvl = static_cast<uint8_t>(roundf(cmvl));
    cmerg[i] = mgvl > 255 ? 255 : mgvl;
  }
  return Color{ cmerg[0], cmerg[1], cmerg[2] };
}




