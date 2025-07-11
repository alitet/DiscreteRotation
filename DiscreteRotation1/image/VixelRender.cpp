#include "VixelRender.h"


VixelRender::VixelRender(uint16_t screnW, uint16_t screnH, uint16_t screnGap)
  : screnw(screnW), screnh(screnH), mGap(screnGap)
{
}

void VixelRender::DrawImageCenter(const sPixelImage& img)
{
  int16_t cenW = static_cast<int16_t>(screnw / 2);
  int16_t cenH = static_cast<int16_t>(screnh / 2);
  sDimx dims = img.getImageDims();

  for (int16_t j = dims.maxh - 1; j >= -dims.minh; j--) {
    for (int16_t i = -dims.minw; i < dims.maxw; i++) {
      int16_t xpos = cenW + (i * mGap);
      int16_t ypos = cenH - (j * mGap);
      Color clr = img.getPixelMerge(i, j);
      if (img.isKeyColor(clr)) { continue; }
      DrawRectangle(xpos, ypos - mGap, mGap, mGap, clr);
    }
  }
}

sPixelImage VixelRender::GetCanvasImage(const sPixelImage& iniImg)
{
  auto dims = iniImg.getImageDims();
  int16_t maxdm = dims.maxh > dims.maxw ? dims.maxh : dims.maxw;
  maxdm = 2 * (static_cast<int16_t>(1.4142135624f * maxdm) + 1);
  sPixelImage imgRet(maxdm, maxdm);
  imgRet.clearAllPixel();

  return imgRet;
}

void rotateForward(const sPixelImage& imgIN, sPixelImage& cnvOUT, float deg)
{
  cnvOUT.clearAllPixel();

  deg *= DEG2RAD;
  float cosdg = cosf(deg);
  float sindg = sinf(deg);

  sDimx dims = imgIN.getImageDims();

  for (int16_t j = dims.maxh - 1; j >= -dims.minh; j--) {
    for (int16_t i = -dims.minw; i < dims.maxw; i++) {
      float fx = (i * cosdg) - (j * sindg);
      float fy = (i * sindg) + (j * cosdg);

      int16_t cx = static_cast<int16_t>(roundf(fx));
      int16_t cy = static_cast<int16_t>(roundf(fy));
      sPix clr = imgIN.getPixel(i, j);

      //cnvOUT.setPixel(cx, cy, clr);
    }
  }
}
