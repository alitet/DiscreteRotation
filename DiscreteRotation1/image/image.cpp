#include "image.h"
#include <iostream>
#include <cmath>

sImgData::sImgData(int16_t w, int16_t h)
{
  ws = w; hs = h;
  minw = static_cast<int16_t>(w / 2);
  minh = static_cast<int16_t>(h / 2);
  pixels.reserve(w * h);
}

Color sImgData::getPixel(int16_t x, int16_t y) const
{
  int16_t nx = x + minw;
  int16_t ny = -y + minh;
  return pixels[ny * hs + nx];
}

void sImgData::setPixel(int16_t x, int16_t y, Color color)
{
  int16_t nx = x + minw;
  int16_t ny = -y + minh;
  pixels[ny * hs + nx] = color;
}

void sImgData::pushPixel(Color color)
{
  pixels.push_back(color);
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

sImgData LoadImageCenterGap(const char* fname)
{
  Image image = LoadImage(fname);
  std::cout << "[" << image.width << "," << image.height << "]" << std::endl;
  Color* clrs = LoadImageColors(image);

  sImgData retvec(image.width, image.height);
  for (int16_t i = 0; i < image.width*image.height; i++) {
    retvec.pushPixel(clrs[i]);
  }

  //int16_t minW = static_cast<int16_t>(image.width / 2);
  //int16_t maxW = image.width - minW;
  //int16_t minH = static_cast<int16_t>(image.height / 2);
  //int16_t maxH = image.height - minH;

  //uint16_t idx = 0;
  //for (int16_t j = maxH-1; j >= -minH; j--) {
  //  for (int16_t i = -minW; i < maxW; i++) {
  //    //if (isKeyColor(clrs[idx])) {
  //    //  idx++;
  //    //  continue;
  //    //}
  //    //sPixelData dtaa{ i, j, clrs[idx] };
  //    retvec.setPixel(i+5,j)
  //    retvec.pixels.push_back(dtaa);
  //    idx++;
  //  }
  //}
  UnloadImage(image);
  //retvec.ws = image.width;
  //retvec.hs = image.height;
  return retvec;
}

void DrawImageCenter(uint16_t w, uint16_t h, uint16_t gap, const sImgData& img)
{
  int16_t cenW = static_cast<int16_t>(w / 2);
  int16_t cenH = static_cast<int16_t>(h / 2);

  auto imgsz = img.getImageSize();

  int16_t minW = static_cast<int16_t>(imgsz.first / 2);
  int16_t maxW = imgsz.first - minW;
  int16_t minH = static_cast<int16_t>(imgsz.second / 2);
  int16_t maxH = imgsz.second - minH;

  for (int16_t j = maxH-1; j >= -minH; j--) {
    for (int16_t i = -minW; i < maxW; i++) {
      int16_t xpos = cenW + (i * gap);
      int16_t ypos = cenH - (j * gap);
      Color clr = img.getPixel(i, j);
      if (isKeyColor(clr)) { continue; }
      DrawRectangle(xpos, ypos - gap, gap, gap, clr);
    }
  }
  //for (const sPixelData& poi : img.pixels) {
  //  int16_t xpos = cenW + (poi.xs * gap);
  //  int16_t ypos = cenH - (poi.ys * gap);
  //  DrawRectangle(xpos, ypos - gap, gap, gap, poi.pixel);
  //}
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
  //imgOUT.pixels.clear();
  //imgOUT.pixels.resize(imgIN.pixels.size());
  //deg *= DEG2RAD;
  //float cosdg = cosf(deg);
  //float sindg = sinf(deg);
  //size_t insz = imgIN.pixels.size();
  //for (uint16_t i = 0; i < insz; i++)
  //{
  //  const sPixelData &poi = imgIN.pixels[i];
  //  float fx = (poi.xs * cosdg) - (poi.ys * sindg);
  //  float fy = (poi.xs * sindg) + (poi.ys * cosdg);

  //  int16_t cx = static_cast<int16_t>(roundf(fx));
  //  int16_t cy = static_cast<int16_t>(roundf(fy));

  //  //if (cx < -5 || cx > 5 || cy < -5 || cy > 5) {
  //  //  int y = 0;
  //  //}

  //  imgOUT.pixels[i].xs = cx;  imgOUT.pixels[i].ys = cy;
  //  imgOUT.pixels[i].pixel = poi.pixel;
  //}  
}

//bool getImgCoordColor(const std::vector<sPixelData>& pixels, int16_t x, int16_t y, Color &color)
//{
//  for (const sPixelData& pxd : pixels) {
//    if (pxd.xs == x && pxd.ys == y) {
//      color = pxd.pixel;
//      return true;
//    }
//  }
//  return false;
//}

void rotateBackward(const sImgData& imgIN, sImgData& imgOUT, float deg)
{
  //imgOUT.pixels.clear();

  //int16_t minW = static_cast<int16_t>(imgIN.ws / 2);
  //int16_t maxW = imgIN.ws - minW;
  //int16_t minH = static_cast<int16_t>(imgIN.hs / 2);
  //int16_t maxH = imgIN.hs - minH;

  //float hip = sqrtf(maxW * maxW + maxH * maxH);
  //int16_t maxHf = static_cast<int16_t>(roundf(hip));//maxW > maxH ? maxW : maxH;
  //imgOUT.pixels.resize(static_cast<size_t>(PI * maxHf * maxHf));

  //deg *= DEG2RAD;
  //float cosdg = cosf(deg);
  //float sindg = sinf(deg);

  //uint16_t idx = 0;
  //for (int16_t j = -maxHf; j < maxHf; j++) {
  //  for (int16_t i = -maxHf; i < maxHf; i++) {
  //    float fx = (i * cosdg) + (j * sindg);
  //    float fy = (i * -sindg) + (j * cosdg);
  //    int16_t cx = static_cast<int16_t>(roundf(fx));
  //    int16_t cy = static_cast<int16_t>(roundf(fy));

  //    //const sPixelData& poi = imgIN.pixels[i];
  //    if (cx >= -minW && cx < maxW && cy >= -minH && cy < maxH) {
  //      Color lcolor;
  //      if (getImgCoordColor(imgIN.pixels, cx, cy, lcolor)) {
  //        imgOUT.pixels[idx].xs = i;  imgOUT.pixels[idx].ys = j;
  //        imgOUT.pixels[idx].pixel = lcolor;
  //        idx++;
  //      }
  //    }
  //  }
  //}
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


