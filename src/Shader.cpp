#include "Shader.h"
#include "GLHelper.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace hmk;

Shader Shader::createFromFile(std::string filePath, GLenum shaderType)
{
    std::ifstream in(filePath);
    if(!in.is_open())
        throw std::runtime_error(ERROR + std::string("Failed to open: ") + filePath);
    //read whole file into stringstream buffer
    std::stringstream ss;
    ss << in.rdbuf();

    Shader shader(ss.str(), shaderType, filePath);
    return shader;
}

Shader::Shader(std::string shaderCode, GLenum shaderType, std::string filePath)
{
    // Create shader object
	shaderID = 0;
    shaderID = glCreateShader(shaderType);
    if(shaderID == 0)
        throw std::runtime_error(ERROR + "glCreateShader failed\n");

    // set the source code
    const char *code = shaderCode.c_str();
    glShaderSource(shaderID, 1, &code, nullptr);

    // compile shader
    glCompileShader(shaderID);

    // Check the result of the compilation
    GLint result;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    if(!result)
    {
        std::vector<char> log(512);
        glGetShaderInfoLog(shaderID, log.size(), nullptr, &log[0]);
        glDeleteShader(shaderID); shaderID = 0;
        throw std::runtime_error(std::string(ERROR + "Shader compilation failed with this message("+filePath+"):\n") + &log[0]);
    }
}

Shader::~Shader()
{
}

GLuint Shader::GetShader() const
{
    return shaderID;
}
