#pragma once
#include <iostream>
#include <sstream>
#include <math.h>
#include <array>
#include <limits>
#include <vector>
#include "Dependencies/GLUT/include/GL/glut.h"
#include "Dependencies/ImGui/imgui.h"
#include "Dependencies/ImGui/imgui_impl_opengl3.h"
#include "Dependencies/ImGui/imgui_impl_glfw.h"
#include "Dependencies/ImGui/imgui.h"
#include "Dependencies/ImGui/imgui_impl_opengl3.h"
#include "Dependencies/ImGui/imgui_impl_glfw.h"

template <typename T>
std::string ConvertToString(T value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}
