#pragma once

// C++ Headers 
#include <cstdint>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <thread>
#include <atomic>
#include <memory>

#define OUT_METHOD_NAME "[" << typeid(*this).name() << "::" << __func__ << "]"