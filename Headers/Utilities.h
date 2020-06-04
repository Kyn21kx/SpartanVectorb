#pragma once
#include <iostream>
#include <sstream>
#include <math.h>
#include <array>
#include <limits>
#include <vector>

template <typename T>
std::string ConvertToString(T value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}
