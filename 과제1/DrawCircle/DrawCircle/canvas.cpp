#include "pch.h"

#include <atlimage.h>	// CImage class header 


Canvas::Canvas() {

}

Canvas::~Canvas() {

}

bool Canvas::Init(int width, int height, uint8_t color) {
	if (width <= 0 || height <= 0) {
		std::cerr << OUT_METHOD_NAME << "Invalid Frame Size (width: " << width << ", height: " << height << ")" << std::endl;
	}

	width_ = width;
	height_ = height;

	frame_buffer_.resize(width_ * height_, 0);

	mfc_image_ = std::make_unique<ATL::CImage>();
	mfc_image_->Create(width_, height_, bpp_);

	RGBQUAD palette[256];
	for (int i = 0; i < 256; ++i)
	{
		palette[i].rgbRed = i;
		palette[i].rgbGreen = i;
		palette[i].rgbBlue = i;
		palette[i].rgbReserved = 0;
	}
	mfc_image_->SetColorTable(0, 256, palette);

	return true;
}

void Canvas::BufferClear(uint8_t color) {
	std::fill(frame_buffer_.begin(), frame_buffer_.end(), color);
}

bool Canvas::DrawCircle(int x, int y, int r, int thickness, uint8_t color) {

	if (r <= 0) 
		return false;

	int x_start = max(x - r, 0);
	int y_start = max(y - r, 0);
	int x_end = min(x+r, width_);
	int y_end = min(y+r, height_);


	for (int i = y_start; i < y_end; i++) {
		for (int j = x_start; j < x_end; j++) {
			double dist = sqrt((i-y)*(i-y) + (j-x)*(j-x));
			int idx = i * width_ + j;

			if (thickness == -1 && dist <= r) {	// Fill
				frame_buffer_[idx] = color;
			}
			else if (dist <= r && dist >= double(r - thickness)) {
				frame_buffer_[idx] = color;
			}
		}
 	}

	return true;
}

void Canvas::BufferUpdate() {
	int pitch = mfc_image_->GetPitch();
	BYTE* p_dst = reinterpret_cast<BYTE*>(mfc_image_->GetBits());
	for (int row = 0; row < height_; row++) {
		std::memcpy(p_dst + row * pitch, &frame_buffer_[0] + row * width_, width_);
	}
}

ATL::CImage* Canvas::GetMFCImage() {
	return mfc_image_.get();
}