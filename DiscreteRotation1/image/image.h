#pragma once

#include "..\raylib\raylib.h"
#include <cstdint>
#include <vector>



struct sPixelData {
	int16_t xs;
	int16_t ys;
	Color pixel;
};

struct sImgData {
	int16_t ws;
	int16_t hs;
	std::vector<sPixelData> pixels;
};

void DrawCenterRefGrid(uint16_t w, uint16_t h, uint16_t gap);

sImgData LoadImageCenterGap(const char* fname);
void DrawImageCenter(uint16_t w, uint16_t h, uint16_t gap, const sImgData& img);

void DrawCenterRefCross(uint16_t w, uint16_t h, uint16_t gap);

void rotateForward(const sImgData& imgIN, sImgData& imgOUT, float deg);
void rotateBackward(const sImgData& imgIN, sImgData& imgOUT, float deg);

void moveImage(const sImgData& imgIN, sImgData& imgOUT, uint16_t x, uint16_t y);


