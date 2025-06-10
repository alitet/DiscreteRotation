#pragma once

#include "..\raylib\raylib.h"
#include <cstdint>
#include <vector>



//struct sPixelData {
//	int16_t xs;
//	int16_t ys;
//	Color pixel;
//};

class sImgData 
{
public:
	sImgData(int16_t w, int16_t h);
	Color getPixel(int16_t x, int16_t y) const;
	void setPixel(int16_t x, int16_t y, Color color);
	void pushPixel(Color color);
	std::pair<int16_t, int16_t> getImageSize() const;

private:
	int16_t ws;
	int16_t hs;

	int16_t minw;
	int16_t minh;
	//std::vector<sPixelData> pixels;
	std::vector<Color> pixels;
};

void DrawCenterRefGrid(uint16_t w, uint16_t h, uint16_t gap);

sImgData LoadImageCenterGap(const char* fname);
void DrawImageCenter(uint16_t w, uint16_t h, uint16_t gap, const sImgData& img);

void DrawCenterRefCross(uint16_t w, uint16_t h, uint16_t gap);

void rotateForward(const sImgData& imgIN, sImgData& imgOUT, float deg);
void rotateBackward(const sImgData& imgIN, sImgData& imgOUT, float deg);
void rotateFastBresen(const sImgData& imgIN, sImgData& imgOUT, float deg);

void moveImage(const sImgData& img, sImgData& out, uint16_t x, uint16_t y);


