#include "image.h"
#include <iostream>

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
  for (int16_t j = maxH; j >= -minH; j--) {
    if (j == 0) { continue; }
    for (int16_t i = -minW; i <= maxW; i++) {
      if (i == 0) { continue; }
      if (clrs[idx].r == 255 && clrs[idx].g == 0 && clrs[idx].b == 255) {
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
    int16_t dix = poi.ws > 0 ? poi.ws - 1 : poi.ws;
    int16_t diy = poi.hs < 0 ? poi.hs + 1 : poi.hs;
    int16_t xpos = cenW + (dix * gap);
    int16_t ypos = cenH - (diy * gap);
    DrawRectangle(xpos, ypos, gap, gap, poi.pixel);
  }
}
