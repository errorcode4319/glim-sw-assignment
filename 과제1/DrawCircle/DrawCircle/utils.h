#pragma once

// C++ Headers 
#include <cstdint>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <set>
#include <thread>
#include <atomic>
#include <random>
#include <memory>
#include <chrono>
#include <condition_variable>

#define OUT_METHOD_NAME "[" << typeid(*this).name() << "::" << __func__ << "]"


double GetDistance(int x1, int y1, int x2, int y2);

inline void SleepMs(uint64_t time_ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(time_ms));
}

inline uint64_t GetEpochTimeMs() {
	return uint64_t(
		std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::high_resolution_clock::now().time_since_epoch()
		).count()
	);
}