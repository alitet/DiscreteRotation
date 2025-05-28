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

std::vector<sImgData> LoadImageCenterGap(const char* fname)
{
  std::vector<sImgData> retvec;

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
      sImgData dtaa{ i, j, clrs[idx] };
      retvec.push_back(dtaa);
      idx++;
    }
  }

  UnloadImage(image);
  return retvec;
}

void DrawImageCenter(uint16_t w, uint16_t h, uint16_t gap, const std::vector<sImgData>& img)
{
  int16_t cenW = static_cast<int16_t>(w / 2);
  int16_t cenH = static_cast<int16_t>(h / 2);
  for (const sImgData& poi : img) {
    //int16_t dix = poi.ws > 0 ? poi.ws - 1 : poi.ws;
    //int16_t diy = poi.hs < 0 ? poi.hs + 1 : poi.hs;
    int16_t xpos = cenW + (poi.ws * gap);
    int16_t ypos = cenH - (poi.hs * gap);
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

const std::vector<sImgData> rotateForward(const std::vector<sImgData>& img, float deg)
{
  std::vector<sImgData> retvec;
  deg *= DEG2RAD;

  for (const sImgData& poi : img) {
    int16_t crx = poi.ws > 0 ? poi.ws - 1 : poi.ws;
    int16_t cry = poi.hs > 0 ? poi.hs - 1 : poi.hs;
    float fx = (crx * cosf(deg)) - (cry * sinf(deg));
    float fy = (crx * sinf(deg)) + (cry * cosf(deg));

    int16_t cx = static_cast<int16_t>(roundf(fx));
    int16_t cy = static_cast<int16_t>(roundf(fy));

    int16_t stx = cx >= 0 ? cx + 1 : cx;
    int16_t sty = cy >= 0 ? cy + 1 : cy;
    retvec.push_back({ stx, sty, poi.pixel });
  }
  return retvec;
}
