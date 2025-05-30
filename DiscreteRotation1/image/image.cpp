#include "image.h"
#include <iostream>
#include <cmath>

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

sImgData LoadImageCenterGap(const char* fname)
{
  sImgData retvec;

  Image image = LoadImage(fname);
  std::cout << "[" << image.width << "," << image.height << "]" << std::endl;
  Color* clrs = LoadImageColors(image);

  int16_t minW = static_cast<int16_t>(image.width / 2);
  int16_t maxW = image.width - minW;
  int16_t minH = static_cast<int16_t>(image.height / 2);
  int16_t maxH = image.height - minH;

  uint16_t idx = 0;
  for (int16_t j = maxH; j > -minH; j--) {
    //if (j == 0) { continue; }
    for (int16_t i = -minW; i < maxW; i++) {
      //if (i == 0) { continue; }
      if (isKeyColor(clrs[idx])) {
        idx++;
        continue;
      }
      sPixelData dtaa{ i, j, clrs[idx] };
      retvec.pixels.push_back(dtaa);
      idx++;
    }
  }
  UnloadImage(image);
  retvec.ws = image.width;
  retvec.hs = image.height;
  return retvec;
}

void DrawImageCenter(uint16_t w, uint16_t h, uint16_t gap, const sImgData& img)
{
  int16_t cenW = static_cast<int16_t>(w / 2);
  int16_t cenH = static_cast<int16_t>(h / 2);
  for (const sPixelData& poi : img.pixels) {
    int16_t xpos = cenW + (poi.xs * gap);
    int16_t ypos = cenH - (poi.ys * gap);
    DrawRectangle(xpos, ypos, gap, gap, poi.pixel);
  }
}

void DrawCenterRefCross(uint16_t w, uint16_t h, uint16_t gap)
{
  int16_t cenW = static_cast<int16_t>(w / 2);
  int16_t cenH = static_cast<int16_t>(h / 2);
  DrawLine(cenW, cenH - gap, cenW, cenH + gap, RED);
  DrawLine(cenW - gap, cenH, cenW + gap, cenH, RED);
}

void rotateForward(const sImgData& imgIN, sImgData& imgOUT, float deg)
{  
  deg *= DEG2RAD;
  float cosdg = cosf(deg);
  float sindg = sinf(deg);
  size_t insz = imgIN.pixels.size();
  for (uint16_t i = 0; i < insz; i++)
  {
    const sPixelData &poi = imgIN.pixels[i];
    float fx = (poi.xs * cosdg) - (poi.ys * sindg);
    float fy = (poi.xs * sindg) + (poi.ys * cosdg);

    int16_t cx = static_cast<int16_t>(roundf(fx));
    int16_t cy = static_cast<int16_t>(roundf(fy));

    imgOUT.pixels[i].xs = cx;  imgOUT.pixels[i].ys = cy;
    imgOUT.pixels[i].pixel = poi.pixel;
  }  
}

void rotateBackward(const sImgData& imgIN, sImgData& imgOUT, float deg)
{
  //int16_t maxv = 0;
  //if (imgIN.ws > imgIN.hs) {

  //}
  int16_t maxSide = imgIN.ws > imgIN.hs ? imgIN.ws : imgIN.hs;
  int16_t minHf = static_cast<int16_t>(maxSide / 2);
  int16_t maxHf = maxSide - minHf;
  float cosdg = cosf(deg);
  float sindg = sinf(deg);

  for (uint16_t j = -maxHf; j < maxHf; j++) {
    for (uint16_t i = -maxHf; i < maxHf; i++) {
      const sPixelData& poi = imgIN.pixels[i];
      float fx = (poi.xs * cosdg) + (poi.ys * sindg);
      float fy = (poi.xs * -sindg) + (poi.ys * cosdg);
      int16_t cx = static_cast<int16_t>(roundf(fx));
      int16_t cy = static_cast<int16_t>(roundf(fy));
      // if the point is in the image take the color from there
    }
  }
}
