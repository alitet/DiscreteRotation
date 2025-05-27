#pragma once

#include "..\raylib\raylib.h"
#include <cstdint>
#include <vector>

struct sImgData {
	int16_t ws;
	int16_t hs;
	Color pixel;
};

void DrawCenterRefGrid(uint16_t w, uint16_t h, uint16_t gap);

std::vector<sImgData> LoadImageCenterGap(const char* fname);
void DrawImageCenter(uint16_t w, uint16_t h, uint16_t gap, const std::vector<sImgData>& img);

