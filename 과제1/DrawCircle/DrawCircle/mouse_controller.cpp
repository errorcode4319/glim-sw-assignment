#include "pch.h"


void MouseController::Click(int x, int y) {
	on_clicked_ = true;
	cur_mouse_coord_.x = x;
	cur_mouse_coord_.y = y;
}

void MouseController::MoveTo(int x, int y) {
	if (on_clicked_)
		on_drag_ = true;
	cur_mouse_coord_.x = x;
	cur_mouse_coord_.y = y;
}

void MouseController::Release() {
	on_clicked_ = false;
	on_drag_ = false;
}