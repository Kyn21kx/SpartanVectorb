#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gl/wglew.h>
#include "Headers/Vectors.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
class Renderer {
public:
	Renderer();
	Renderer(int winWidth, int winHeight);
	void DrawCartesianPlane() const;
	void DrawVector(Vector3 v, float lineWidth);
	//void DrawVector(Vector2 v, float lineWidth);
	void DrawVector(Vector3 fromAltOrigin, Vector3 toPoint, float lineWidth);
	//void DrawVector(Vector2 fromAltOrigin, Vector2 toPoint, float lineWidth);
	void ClearScreen();
	void CameraPerspective();
	GLFWwindow* GetWindow() {
		return m_window;
	}
private:
	int WindowSetup(int width, int height);
	GLFWwindow* m_window = nullptr;
};
