#include "image.h"
#include <iostream>
#include <cmath>
//#include "vixel.h"

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

void DrawImageBottomLeft(uint16_t w, uint16_t h, uint16_t gap, const sImgData& img)
{
  int16_t cenW = static_cast<int16_t>(w / 2);
  int16_t cenH = static_cast<int16_t>(h / 2);
  auto [ws, hs] = img.getImageSize();

  for (int16_t j = hs - 1; j >= 0; j--) {
    for (int16_t i = 0; i < ws; i++) {
      int16_t xpos = cenW + (i * gap);
      int16_t ypos = cenH - (j * gap);
      Color clr = img.getPixelLowLeft(i, j);
      if (isKeyColor(clr)) { continue; }
      DrawRectangle(xpos, ypos - gap, gap, gap, clr);
    }
  }
}

void DrawImageCenterAtPos(uint16_t w, uint16_t h, uint16_t gap, const sImgData& img, int16_t pdx, int16_t pdy)
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
  maxdm = 2 * (static_cast<int16_t>(1.4142135624f * maxdm) + 1);
  sImgData imgRet(maxdm, maxdm);
  imgRet.clearAllPixel();

  return imgRet;
}

sImgData GetCanvasImageFull(const sImgData& iniImg)
{
  auto [ws, hs] = iniImg.getImageSize();
  float esq = static_cast<float>(ws * ws + hs * hs);
  int16_t maxdm = 2 * (static_cast<int16_t>(sqrtf(esq)) + 1);
  sImgData imgRet(maxdm, maxdm);
  imgRet.clearAllPixel();

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

bool validatePixel(const sImgData& imgIN, int16_t x, int16_t y, Color &lcolor)
{
  sDims dmsIN = imgIN.getImageDims();
  lcolor = BLACK;
  if (x >= -dmsIN.minw && x < dmsIN.maxw &&
    y >= -dmsIN.minh && y < dmsIN.maxh)
  {
    Color clrr = imgIN.getPixel(x, y);
    if (isKeyColor(clrr)) { return false; }
		lcolor = clrr;
  }
	return true;
}

bool isMergePixel(const sImgData& imgIN, float x, float y) 
{
  float decx = x - floorf(x);
  if (decx > 0.2f && decx < 0.8f) { return true; }
  float decy = y - floorf(y);
  if (decy > 0.2f && decy < 0.8f) { return true; }
	return false;
}

bool getSinglePixel(const sImgData& imgIN, float x, float y, Color& color)
{
  Color lclr = BLACK;
  int16_t cx = static_cast<int16_t>(roundf(x));
  int16_t cy = static_cast<int16_t>(roundf(y));
  if (validatePixel(imgIN, cx, cy, lclr)) {
    color = lclr;
    return true;
  }
  return false;
}

std::vector<Color> getMergePixels(const sImgData& imgIN, float x, float y)
{
  std::vector<Color> retvec;
  int16_t florx = static_cast<int16_t>(floorf(x));
  int16_t ceilx = static_cast<int16_t>(ceilf(x));

  int16_t flory = static_cast<int16_t>(floorf(y));
  int16_t ceily = static_cast<int16_t>(ceilf(y));

	Color florclr, ceilclr;
	bool fpi = validatePixel(imgIN, florx, flory, florclr);
	bool cpi = validatePixel(imgIN, ceilx, flory, ceilclr);
  if (fpi && cpi) {
    retvec.push_back(florclr);
    retvec.push_back(ceilclr);
  }
  else {
    if (getSinglePixel(imgIN, x, y, florclr)) {
      retvec.push_back(florclr);
    }
  }
	return retvec;
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

      if (isMergePixel(imgIN, fx, fy)) {
				auto cvec = getMergePixels(imgIN, fx, fy);
        if (cvec.size() > 0) {

        }
      }
      else {
        Color sinclr;
        if (getSinglePixel(imgIN, fx, fy, sinclr)) {

        }
      }

   //   int16_t cx = static_cast<int16_t>(roundf(fx));
   //   int16_t cy = static_cast<int16_t>(roundf(fy));
			//int16_t lx = cx; int16_t ly = cy;
			//bool merge = false;

			//float decx = fx - floorf(fx);
   //   if (decx > 0.2f && decx < 0.8f) {
   //     lx = static_cast<int16_t>(floorf(fx));
   //     cx = static_cast<int16_t>(ceilf(fx));
   //     merge = true;
   //   }

   //   float decy = fy - floorf(fy);
   //   if (decy > 0.2f && decy < 0.8f) {
   //     ly = static_cast<int16_t>(floorf(fy));
   //     cy = static_cast<int16_t>(ceilf(fy));
   //     merge = true;
   //   }

   //   if (merge) {

   //   }

   //   if (cx >= -dmsIN.minw && cx < dmsIN.maxw && 
   //       cy >= -dmsIN.minh && cy < dmsIN.maxh)
   //   {
   //     Color lcolor = imgIN.getPixel(cx, cy);
   //     cnvOUT.setPixel(i, j, lcolor);
   //   }
    }
  }
}

void rotateRealBresen(const sImgData& imgIN, sImgData& cnvOUT, float deg)
{
  cnvOUT.clearAllPixel();

  auto [ws, hs] = imgIN.getImageSize();
  auto [wx, hx] = cnvOUT.getImageSize();

  deg *= DEG2RAD;
  float cosdg = cosf(deg);
  float sindg = sinf(deg);
  float ex = 0; float ey = 0;
  for (uint16_t j = 0; j < hx - 1; j++)
  {
    float lx = j * sindg, ly = j * cosdg;
    int16_t m = static_cast<int16_t>(lx);
    int16_t n = static_cast<int16_t>(ly);
    ex = lx - m; ey = ly - n;
    for (uint16_t i = 0; i < wx - 1; i++)
    {
      int16_t x1 = m; int16_t y1 = n;
      if (ex > 0.5f) {
        m = m + 1; 
        ex = ex - 1;
      }
      if (ey < -0.5f) {
        n = n - 1;
        ey = ey + 1;
      }
      float tmpex = ex;
      ex = tmpex + cosdg;
      ey = tmpex - sindg;
      if (x1 < 0 || x1 > ws - 1 || y1 < 0 || y1 > hs - 1) {
        continue;
      }
      else {
        Color clr = imgIN.getPixelLowLeft(x1, y1);
        cnvOUT.setPixelLowLeft(i, j, clr);
      }

    }
  }
}

//void moveImage(const sImgData& img, sImgData& out, uint16_t x, uint16_t y)
//{
//  out.pixels.clear();
//  out.pixels.resize(img.pixels.size());
//  for (uint16_t i = 0; i < img.pixels.size(); i++) {
//    sPixelData pdt = img.pixels[i];
//    out.pixels[i].xs = pdt.xs + x;
//    out.pixels[i].ys = pdt.ys + y;
//    out.pixels[i].pixel = pdt.pixel;
//  }
//  out.ws = img.ws;
//  out.hs = img.hs;
//}


