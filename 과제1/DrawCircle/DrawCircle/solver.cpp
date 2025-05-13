#include "pch.h"



Solver::Solver() {

}

Solver::~Solver() {

}

bool Solver::AddPoint(int x, int y) {
	if (points_.size() == 3) {
		return false;
	}
	points_.push_back({ x, y });
	return true;
}

bool Solver::MovePoint(int idx, int x, int y) {
	if (points_.size() <= idx) {
		return false;
	}
	points_[idx].x = x;
	points_[idx].y = y;
	return true;
}

Result Solver::Solve() const {
	if (points_.size() < 3) {
		return Result{ 0, 0, 0, ResultState::MorePointRequired };
	}

	double a = double(points_[0].x);
	double b = double(points_[0].y);
	double c = double(points_[1].x);
	double d = double(points_[1].y);
	double e = double(points_[2].x);
	double f = double(points_[2].y);

	double det = (c - a) * (f - b) - (d - b) * (e - a);
	if (det == 0.0) {
		return Result{ 0, 0, 0, ResultState::InvalidCoordinate };
	}

	double x = ((f - b) * ((-(a * a) - (b * b) + (c * c) + (d * d)) / 2.0) + (b - d) * ((-(a * a) - (b * b) + (e * e) + (f * f)) / 2.0)) / det;
	double y = ((a - e) * ((-(a * a) - (b * b) + (c * c) + (d * d)) / 2.0) + (c - a) * ((-(a * a) - (b * b) + (e * e) + (f * f)) / 2.0)) / det;
	double r = sqrt((a - x) * (a - x) + (b - y) * (b - y));
	
	return Result{x, y, r, ResultState::Success};
}

void Solver::Clear() {
	points_.clear();
}

void Solver::RandomGenerate(int x_max, int y_max) {
	points_.clear();

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, 1000000);

	while(true) {
		for (int i = 0; i < 3; i++) {
			int x = dist(mt) % x_max;
			int y = dist(mt) % y_max;
			points_.push_back({ x, y });
		}

		auto result = Solve();

		if (result.state == ResultState::Success)
			break;
	}
}