#pragma once
#include "..\raylib\raylib.h"
#include <cstdint>
#include <vector>

struct sDims
{
	int16_t minw;
	int16_t minh;
	int16_t maxw;
	int16_t maxh;
};

class sImgData 
{
public:
	sImgData(int16_t w, int16_t h);
	Color getPixel(int16_t x, int16_t y) const;
	void setPixel(int16_t x, int16_t y, Color color);
	void setPixel(uint16_t index, Color color);

	Color getPixelLowLeft(int16_t x, int16_t y) const;
	void setPixelLowLeft(int16_t x, int16_t y, Color color);

	void clearAllPixel();

	std::pair<int16_t, int16_t> getImageSize() const;
	sDims getImageDims() const { return dims; }

private:
	int16_t ws;
	int16_t hs;

	sDims dims;

	std::vector<Color> pixels;
};

void DrawCenterRefGrid(uint16_t w, uint16_t h, uint16_t gap);

sImgData LoadImageLinear(const char* fname);
void DrawImageCenter(uint16_t w, uint16_t h, uint16_t gap, const sImgData& img);
void DrawImageCenterAtPos(uint16_t w, uint16_t h, uint16_t gap, const sImgData& img, int16_t pdx, int16_t pdy);

void DrawImageBottomLeft(uint16_t w, uint16_t h, uint16_t gap, const sImgData& img);

sImgData GetCanvasImage(const sImgData& iniImg);
sImgData GetCanvasImageFull(const sImgData& iniImg);

void DrawCenterRefCross(uint16_t w, uint16_t h, uint16_t gap);

void rotateForward(const sImgData& imgIN, sImgData& cnvOUT, float deg);
void rotateBackward(const sImgData& imgIN, sImgData& cnvOUT, float deg);
void rotateRealBresen(const sImgData& imgIN, sImgData& cnvOUT, float deg);

//void moveImage(const sImgData& img, sImgData& out, uint16_t x, uint16_t y);
//void moveImage(sImgData& img, uint16_t x, uint16_t y);


