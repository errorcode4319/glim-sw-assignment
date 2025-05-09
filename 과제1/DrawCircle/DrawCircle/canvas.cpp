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

	RGBQUAD color_table[256];
	for (int i = 0; i < 256; i++) {
		color_table[i] = RGBQUAD{uint8_t(i), uint8_t(i), uint8_t(i), 0};
	}
	mfc_image_->SetColorTable(0, 256, color_table);

	return true;
}

void Canvas::BufferClear(uint8_t color) {
	std::fill(frame_buffer_.begin(), frame_buffer_.end(), color);
}

bool Canvas::DrawCircle(int x, int y, int r, int thickness) {


	return true;
}

void Canvas::BufferUpdate() {
	auto pitch = mfc_image_->GetPitch();
	auto* p_dst = reinterpret_cast<uint8_t*>(mfc_image_->GetBits());
	for (int row = 0; row < height_; row++) {
		std::memcpy(p_dst + row * pitch, &frame_buffer_[0] + row * width_, width_);
	}
}

ATL::CImage* Canvas::GetMFCImage() {
	return mfc_image_.get();
}