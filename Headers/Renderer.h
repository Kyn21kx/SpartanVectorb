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
	Renderer(int n, char** argint, int winWidth, int winHeight, void MainLoopFunc(), void InputFunc(unsigned char k, int x, int y));
	void Init();
	static void DrawCartesianPlane(int units);
	void DrawVector(Vector3 v, float lineWidth);
	//void DrawVector(Vector2 v, float lineWidth);
	void DrawVector(Vector3 fromAltOrigin, Vector3 toPoint, float lineWidth);
	//void DrawVector(Vector2 fromAltOrigin, Vector2 toPoint, float lineWidth);
	void ClearScreen();
	void CameraPerspective();
	//Function needs to be called from main
private:
	void GLUTWindow(int n, char **arg, void mainLoopFunc(), void inputFunc(unsigned char k, int x, int y));
	int windowHeight, windowWidth;
	int WindowSetup(int width, int height);
};
