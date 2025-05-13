#pragma once



struct MouseCoord {
	int		x = 0;
	int		y = 0;
};

class MouseController {

public:
	MouseController() = default;
	~MouseController() = default;

	void Click(int x, int y);
	void MoveTo(int x, int y);
	void Release();

	bool OnClicked() const { return on_clicked_; }
	bool OnDrag() const { return on_drag_; }
	auto GetCurMouseCoord() const { return cur_mouse_coord_; }

private:
	MouseCoord cur_mouse_coord_{};
	bool	on_clicked_ = false;
	bool	on_drag_ = false;

};