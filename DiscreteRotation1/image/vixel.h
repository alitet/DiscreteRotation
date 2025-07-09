#pragma once
#include "..\raylib\raylib.h"
#include <cstdint>
#include <vector>

struct sDimx
{
	int16_t minw;
	int16_t minh;
	int16_t maxw;
	int16_t maxh;
};

//struct sPix 
//{
//	int16_t xo;
//	int16_t yo;
//	uint16_t percent;
//};

struct sPix
{
	Color acol;
	Color bcol;
	uint8_t aper;
	uint8_t bper;
};

//struct sVixel
//{
//	std::vector<sPix> vAportes;
//};

class sPixelImage
{
public:
	sPixelImage(const char* fname);
	sPixelImage(uint16_t w, uint16_t h);

	~sPixelImage() = default;

	sPix getPixel(int16_t x, int16_t y) const;
	Color getPixelMerge(int16_t x, int16_t y) const;

	//void setPixel(int16_t x, int16_t y, Color pix);
	void setPixelMerge(int16_t x, int16_t y, sPix pix);

	sDimx getImageDims() const { return dims; }

	bool isKeyColor(const Color& clr) const;
	void clearAllPixel();

	//void setPixel(uint16_t index, Color color);

	//Color getPixelLowLeft(int16_t x, int16_t y) const;
	//void setPixelLowLeft(int16_t x, int16_t y, Color color);

	//void clearAllPixel();

	//std::pair<int16_t, int16_t> getImageSize() const;
	//sDims getImageDims() const { return dims; }

private:
	Color mixColorPixs(sPix piz) const;

private:

	std::vector<sPix> pixels;
	int16_t ws;
	int16_t hs;

	sDimx dims;

	//std::vector<Color> pixels;
};

//void DrawCenterRefGrid(uint16_t w, uint16_t h, uint16_t gap);
//
//sImgData LoadImageLinear(const char* fname);
//void DrawImageCenter(uint16_t w, uint16_t h, uint16_t gap, const sImgData& img);
//void DrawImageCenterAtPos(uint16_t w, uint16_t h, uint16_t gap, const sImgData& img, int16_t pdx, int16_t pdy);
//
//void DrawImageBottomLeft(uint16_t w, uint16_t h, uint16_t gap, const sImgData& img);
//
//sImgData GetCanvasImage(const sImgData& iniImg);
//sImgData GetCanvasImageFull(const sImgData& iniImg);
//
//void DrawCenterRefCross(uint16_t w, uint16_t h, uint16_t gap);
//
//void rotateForward(const sImgData& imgIN, sImgData& cnvOUT, float deg);
//void rotateBackward(const sImgData& imgIN, sImgData& cnvOUT, float deg);
//void rotateRealBresen(const sImgData& imgIN, sImgData& cnvOUT, float deg);


