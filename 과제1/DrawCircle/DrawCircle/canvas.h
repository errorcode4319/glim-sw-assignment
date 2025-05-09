#pragma once

#include "utils.h"

namespace ATL {	// Forward Decl
	class CImage;
}

class Canvas {

public:
	Canvas();
	~Canvas();

	bool Init(int width, int height, uint8_t color = 255);

	void BufferClear(uint8_t color = 255);

	bool DrawCircle(int x, int y, int r, int thickness = 1);

	void BufferUpdate();

	ATL::CImage* GetMFCImage();

private:

	int width_;
	int height_;
	const int bpp_ = 8;

	std::vector<uint8_t>	frame_buffer_;
	std::unique_ptr<ATL::CImage> mfc_image_;
	
};