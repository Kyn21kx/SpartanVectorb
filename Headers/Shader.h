#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Headers/Vectors.h"

class Shader {
public:
    struct ShaderProgramSource {
        std::string VertexSource;
        std::string FragmentSource;
    };
    ShaderProgramSource PassShader(const std::string& filePath);
    unsigned int CompileShader(unsigned int type, const std::string source);
    //Parameters are the actual code
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    void ChangeColor(unsigned int _shader, const char* variableName, Vector4 newColor);
};

