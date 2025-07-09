#include "VixelRender.h"


VixelRender::VixelRender(uint16_t screnW, uint16_t screnH, uint16_t screnGap)
  : screnw(screnW), screnh(screnH), gap(screnGap)
{
}

void VixelRender::DrawImageCenter(const sPixelImage& img)
{
  int16_t cenW = static_cast<int16_t>(screnw / 2);
  int16_t cenH = static_cast<int16_t>(screnh / 2);
  sDimx dims = img.getImageDims();

  for (int16_t j = dims.maxh - 1; j >= -dims.minh; j--) {
    for (int16_t i = -dims.minw; i < dims.maxw; i++) {
      int16_t xpos = cenW + (i * gap);
      int16_t ypos = cenH - (j * gap);
      Color clr = img.getPixelMerge(i, j);
      if (img.isKeyColor(clr)) { continue; }
      DrawRectangle(xpos, ypos - gap, gap, gap, clr);
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

//void rotateBackward(const sImgData& imgIN, sImgData& cnvOUT, float deg)
//{
//  cnvOUT.clearAllPixel();
//
//  deg *= DEG2RAD;
//  float cosdg = cosf(deg);
//  float sindg = sinf(deg);
//  sDims dmsOUT = cnvOUT.getImageDims();
//  sDims dmsIN = imgIN.getImageDims();
//
//  for (int16_t j = dmsOUT.maxh - 1; j >= -dmsOUT.minh; j--) {
//    for (int16_t i = -dmsOUT.minw; i < dmsOUT.maxw; i++) {
//      float fx = (i * cosdg) + (j * sindg);
//      float fy = (i * -sindg) + (j * cosdg);
//      int16_t cx = static_cast<int16_t>(roundf(fx));
//      int16_t cy = static_cast<int16_t>(roundf(fy));
//
//      if (cx >= -dmsIN.minw && cx < dmsIN.maxw &&
//        cy >= -dmsIN.minh && cy < dmsIN.maxh)
//      {
//        Color lcolor = imgIN.getPixel(cx, cy);
//        cnvOUT.setPixel(i, j, lcolor);
//      }
//    }
//  }
//}
