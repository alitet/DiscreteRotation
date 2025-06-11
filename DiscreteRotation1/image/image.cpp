#include "image.h"
#include <iostream>
#include <cmath>

sImgData::sImgData(int16_t w, int16_t h)
{
  ws = w; hs = h;
  dims.minw = static_cast<int16_t>(w / 2);
  dims.minh = static_cast<int16_t>(h / 2);
  dims.maxw = w - dims.minw;
  dims.maxh = h - dims.minh;
  pixels.resize(w * h);
}

Color sImgData::getPixel(int16_t x, int16_t y) const
{
  int16_t nx = x + dims.minw;
  int16_t ny = -y + dims.maxh - 1;
  return pixels[ny * ws + nx];
}

void sImgData::setPixel(int16_t x, int16_t y, Color color)
{
  int16_t nx = x + dims.minw;
  int16_t ny = -y + dims.maxh - 1;
  pixels[ny * ws + nx] = color;
}

void sImgData::setPixel(uint16_t index, Color color)
{
  pixels[index] = color;
}

Color sImgData::getPixelLowLeft(int16_t x, int16_t y) const
{
  if (x < 0 || y < 0) { return pixels[0]; }
  int16_t ny = hs - 1 - y;
  return pixels[ny * ws + x];
}

void sImgData::setPixelLowLeft(int16_t x, int16_t y, Color color)
{
  if (x < 0 || y < 0) { return; }
  int16_t ny = hs - 1 - y;
  pixels[ny * ws + x] = color;
}

void sImgData::clearAllPixel()
{
  for (Color& clr : pixels) {
    clr = Color{ 255, 0, 255, 255 };
  }
}

std::pair<int16_t, int16_t> sImgData::getImageSize() const
{
  return std::pair<int16_t, int16_t>(ws, hs);
}

void DrawCenterRefGrid(uint16_t w, uint16_t h, uint16_t gap)
{
  uint16_t hfw = static_cast<uint16_t>(w / 2);
  uint16_t hfh = static_cast<uint16_t>(h / 2);
  for (int i = 0; hfw + (i * gap) < w; i++) {
    DrawLine(hfw + (i * gap), 0, hfw + (i * gap), h, GRAY);
    DrawLine(hfw - (i * gap), 0, hfw - (i * gap), h, GRAY);
  }  
  for (int j = 0; hfh + (j * gap) < h; j++) {
    DrawLine(0, hfh + (j * gap), w, hfh + (j * gap), GRAY);
    DrawLine(0, hfh - (j * gap), w, hfh - (j * gap), GRAY);
  }
}

bool isKeyColor(const Color& clr)
{
  return clr.r == 255 && clr.g == 0 && clr.b == 255;
}

sImgData LoadImageLinear(const char* fname)
{
  Image image = LoadImage(fname);
  std::cout << "[" << image.width << "," << image.height << "]" << std::endl;
  Color* clrs = LoadImageColors(image);

  sImgData retvec(image.width, image.height);
  for (int16_t i = 0; i < image.width * image.height; i++) {
    retvec.setPixel(i, clrs[i]);
  }
  UnloadImage(image);

  return retvec;
}

void DrawImageCenter(uint16_t w, uint16_t h, uint16_t gap, const sImgData& img)
{
  int16_t cenW = static_cast<int16_t>(w / 2);
  int16_t cenH = static_cast<int16_t>(h / 2);
  sDims dims = img.getImageDims();

  for (int16_t j = dims.maxh-1; j >= -dims.minh; j--) {
    for (int16_t i = -dims.minw; i < dims.maxw; i++) {
      int16_t xpos = cenW + (i * gap);
      int16_t ypos = cenH - (j * gap);
      Color clr = img.getPixel(i, j);
      if (isKeyColor(clr)) { continue; }
      DrawRectangle(xpos, ypos - gap, gap, gap, clr);
    }
  }
}

void DrawImageAtPos(uint16_t w, uint16_t h, uint16_t gap, const sImgData& img, int16_t pdx, int16_t pdy)
{
  int16_t cenW = static_cast<int16_t>(w / 2);
  int16_t cenH = static_cast<int16_t>(h / 2);
  sDims dims = img.getImageDims();
  int16_t xgp = pdx * gap;
  int16_t ygp = pdy * gap;

  for (int16_t j = dims.maxh - 1; j >= -dims.minh; j--) {
    for (int16_t i = -dims.minw; i < dims.maxw; i++) {
      int16_t xpos = cenW + (i * gap);
      int16_t ypos = cenH - (j * gap);
      Color clr = img.getPixel(i, j);
      if (isKeyColor(clr)) { continue; }
      DrawRectangle(xpos + xgp, ypos - ygp - gap, gap, gap, clr);
    }
  }
}

sImgData GetCanvasImage(const sImgData& iniImg)
{
  auto dims = iniImg.getImageDims();
  int16_t maxdm = dims.maxh > dims.maxw ? dims.maxh : dims.maxw;
  maxdm = 2 * static_cast<int16_t>(1.4142135624f * maxdm) + 1;
  sImgData imgRet(maxdm, maxdm);
  imgRet.clearAllPixel();

  //for (int16_t j = dims.maxh - 1; j >= -dims.minh; j--) {
  //  for (int16_t i = -dims.minw; i < dims.maxw; i++) {
  //    Color clr = iniImg.getPixel(i, j);
  //    imgRet.setPixel(i, j, clr);
  //  }
  //}
  return imgRet;
}

void DrawCenterRefCross(uint16_t w, uint16_t h, uint16_t gap)
{
  int16_t cenW = static_cast<int16_t>(w / 2);
  int16_t cenH = static_cast<int16_t>(h / 2);
  DrawLine(cenW, cenH - gap, cenW, cenH + gap, RED);
  DrawLine(cenW - gap, cenH, cenW + gap, cenH, RED);
}

void rotateForward(const sImgData& imgIN, sImgData& cnvOUT, float deg)
{
  cnvOUT.clearAllPixel();

  deg *= DEG2RAD;
  float cosdg = cosf(deg);
  float sindg = sinf(deg);

  sDims dims = imgIN.getImageDims();

  for (int16_t j = dims.maxh - 1; j >= -dims.minh; j--) {
    for (int16_t i = -dims.minw; i < dims.maxw; i++) {
      float fx = (i * cosdg) - (j * sindg);
      float fy = (i * sindg) + (j * cosdg);

      int16_t cx = static_cast<int16_t>(roundf(fx));
      int16_t cy = static_cast<int16_t>(roundf(fy));
      Color clr = imgIN.getPixel(i, j);

      cnvOUT.setPixel(cx, cy, clr);
    }
  }
}

void rotateBackward(const sImgData& imgIN, sImgData& cnvOUT, float deg)
{
  cnvOUT.clearAllPixel();

  deg *= DEG2RAD;
  float cosdg = cosf(deg);
  float sindg = sinf(deg);
  sDims dmsOUT = cnvOUT.getImageDims();
  sDims dmsIN = imgIN.getImageDims();

  for (int16_t j = dmsOUT.maxh - 1; j >= -dmsOUT.minh; j--) {
    for (int16_t i = -dmsOUT.minw; i < dmsOUT.maxw; i++) {
      float fx = (i * cosdg) + (j * sindg);
      float fy = (i * -sindg) + (j * cosdg);
      int16_t cx = static_cast<int16_t>(roundf(fx));
      int16_t cy = static_cast<int16_t>(roundf(fy));

      if (cx >= -dmsIN.minw && cx < dmsIN.maxw && 
          cy >= -dmsIN.minh && cy < dmsIN.maxh)
      {
        Color lcolor = imgIN.getPixel(cx, cy);
        cnvOUT.setPixel(i, j, lcolor);
      }
    }
  }
}

void rotateFastBresen(const sImgData& imgIN, sImgData& imgOUT, float deg)
{
  //imgOUT.pixels.clear();
  //imgOUT.pixels.resize(imgIN.pixels.size());

  ////int16_t minW = static_cast<int16_t>(imgIN.ws / 2);
  ////int16_t maxW = imgIN.ws - minW;
  ////int16_t minH = static_cast<int16_t>(imgIN.hs / 2);
  ////int16_t maxH = imgIN.hs - minH;
  //int16_t hx = 2 * imgIN.hs;
  //int16_t wx = 2 * imgIN.ws;


  //deg *= DEG2RAD;
  //float cosdg = cosf(deg);
  //float sindg = sinf(deg);
  //float ex = 0; float ey = 0;
  //for (uint16_t j = 0; j < hx - 1; j++)
  //{
  //  float lx = j * sindg, ly = j * cosdg;
  //  int16_t m = static_cast<int16_t>(lx);
  //  int16_t n = static_cast<int16_t>(ly);
  //  ex = lx - m; ey = ly - n;
  //  for (uint16_t i = 0; i < wx - 1; i++)
  //  {
  //    int16_t x1 = m; int16_t y1 = n;
  //    if (ex > 0.5f) {
  //      m = m + 1; 
  //      ex = ex - 1;
  //    }
  //    if (ey < -0.5f) {
  //      n = n - 1;
  //      ey = ey + 1;
  //    }
  //    ex = ex + cosdg;
  //    ey = ex - sindg;
  //    if (x1 < 0 || x1> imgIN.ws - 1 || y1<0 || y1 > imgIN.hs - 1) {
  //      continue;
  //    }
  //    else {
  //      //imgOUT
  //    }

  //  }
  //}

}

void moveImage(const sImgData& img, sImgData& out, uint16_t x, uint16_t y)
{
  //out.pixels.clear();
  //out.pixels.resize(img.pixels.size());
  //for (uint16_t i = 0; i < img.pixels.size(); i++) {
  //  sPixelData pdt = img.pixels[i];
  //  out.pixels[i].xs = pdt.xs + x;
  //  out.pixels[i].ys = pdt.ys + y;
  //  out.pixels[i].pixel = pdt.pixel;
  //}
  //out.ws = img.ws;
  //out.hs = img.hs;
}


