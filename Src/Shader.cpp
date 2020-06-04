#include "Headers/Shader.h"


Shader::ShaderProgramSource Shader::PassShader(const std::string& filePath) {
    std::ifstream inputStream(filePath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    ShaderType type = ShaderType::NONE;
    std::string line;
    std::stringstream ss[2];

    while (getline(inputStream, line)) {
        if (line.find("#shader") != std::string::npos) {

            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(), ss[1].str() };
    return ShaderProgramSource();
}

unsigned int Shader::CompileShader(unsigned int type, const std::string source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    //Get the source code
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    //Check for errors
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    //if (result == GL_FALSE)
    if (!result) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile shaders: " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    //Delete the shaders because they are already stored in the program
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void Shader::ChangeColor(unsigned int _shader, const char* variableName, Vector4 newColor) {
    int location = glGetUniformLocation(_shader, variableName);
    glUniform4f(location, newColor.GetX(), newColor.GetY(), newColor.GetZ(), newColor.GetW());
}
