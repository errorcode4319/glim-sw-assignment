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

#define OUT_METHOD_NAME "[" << typeid(*this).name() << "::" << __func__ << "]"


double GetDistance(int x1, int y1, int x2, int y2);