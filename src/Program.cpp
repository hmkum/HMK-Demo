#include "Program.h"
#include "GLHelper.h"

#include <stdexcept>
#include <iostream>

using namespace hmk;

Program::Program(std::vector<Shader> const &shaders) : programID(0)
{
    if(shaders.size() <= 0)
        throw std::runtime_error(ERROR + "No shaders were provided to create the program");

    // create the program object
    programID = glCreateProgram();
    if(programID == 0)
        throw std::runtime_error(ERROR + "glCreateProgram failed");

    // attach all shaders
    for(uint8_t i = 0; i < shaders.size(); ++i)
    {
        glAttachShader(programID, shaders[i].GetShader());
    }

    // link and validate the shaders
    glLinkProgram(programID);
    glValidateProgram(programID);

    // We are done with link process
    // now detach the all shaders
    for(uint8_t i = 0; i < shaders.size(); ++i)
    {
        glDetachShader(programID, shaders[i].GetShader());
    }

    // delete the all shaders
    for(uint8_t i = 0; i < shaders.size(); ++i)
    {
        glDeleteShader(shaders[i].GetShader());
    }

    // Check the result of the linking
    GLint result;
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    if(!result)
    {
        std::vector<char> log(512);
        glGetProgramInfoLog(programID, log.size(), nullptr, &log[0]);
        glDeleteProgram(programID); programID = 0;
        throw std::runtime_error(std::string(ERROR + "Shader linking failed with this message:\n") + &log[0]);
    }
}

Program::~Program()
{
    if(programID != 0)
        glDeleteProgram(programID);
}

GLuint Program::GetProgram() const
{
    return programID;
}

GLint Program::GetAttrib(const GLchar *attribName) const
{
    if(!attribName)
        throw std::runtime_error(ERROR + "attribName was NULL");

    GLint attrib;
    attrib = glGetAttribLocation(programID, attribName);
    if(attrib == -1)
        throw std::runtime_error(ERROR + std::string("Program attribute not found: ") + attribName);

    return attrib;
}

GLint Program::GetUniform(const GLchar *uniformName) const
{
    if(!uniformName)
        throw std::runtime_error(ERROR + "uniformName was NULL");

    GLint uniform;
    uniform = glGetUniformLocation(programID, uniformName);
    if(uniform == -1)
        throw std::runtime_error(ERROR + std::string("Program uniform not found: ") + uniformName);

    return uniform;
}

Program::Program(Program const &param) :
	programID(param.programID)
{
	std::cout << "cons: " << param.GetProgram() << std::endl;
}

Program const &Program::operator=(Program const &param)
{
	Program tmp(param);
	std::cout << "=: " << param.GetProgram() << std::endl;
	std::cout << "=: " << programID << std::endl;
	std::swap(programID, tmp.programID);
	std::cout << "=: " << programID << std::endl;
	return *this;
}
