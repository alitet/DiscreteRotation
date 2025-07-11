#pragma once
#include "vixel.h"

class VixelRender
{
public:
	VixelRender(uint16_t screnW, uint16_t screnH, uint16_t screnGap);
	~VixelRender() = default;

	void DrawImageCenter(const sPixelImage& img);
	sPixelImage GetCanvasImage(const sPixelImage& iniImg);

private:
	uint16_t screnw;
	uint16_t screnh; 
	uint16_t mGap;
};

