#pragma once

#include "utils.h"

struct Coord {
	int		x;
	int		y;
};

enum class ResultState {
	Success = 0,
	
	MorePointRequired,		// 포인트 수가 부족한 경우  (3개 필요)
	InvalidCoordinate,		// 유효하지 않은 좌표 정보 (예: 세 점이 나란히 있는 경우)
};

struct Result {
	double	x;
	double	y;
	double	r;
	ResultState		state;
};

class Solver {

public:
	Solver();
	~Solver();

	bool AddPoint(int x, int y);
	bool MovePoint(int idx, int x, int y);
	void Clear();

	void RandomGenerate(int x_max, int y_max);

	const auto& GetPoints() const { return points_; }
	size_t GetPointCount() const { return points_.size(); }

	Result Solve() const;

private:
	std::vector<Coord>	points_;

};