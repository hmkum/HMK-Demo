#include "Program.h"
#include "GLHelper.h"

#include <stdexcept>
#include <iostream>

using namespace hmk;

Program::Program(std::vector<Shader> const &shaders) : m_programID(0)
{
    if(shaders.size() <= 0)
        throw std::runtime_error(ERROR + "No shaders were provided to create the program");

    // create the program object
    m_programID = glCreateProgram();
    if(m_programID == 0)
        throw std::runtime_error(ERROR + "glCreateProgram failed");

    // attach all shaders
    for(uint8 i = 0; i < shaders.size(); ++i)
    {
        glAttachShader(m_programID, shaders[i].getShader());
    }

    // link and validate the shaders
    glLinkProgram(m_programID);
    glValidateProgram(m_programID);

    // We are done with link process
    // now detach the all shaders
    for(uint8 i = 0; i < shaders.size(); ++i)
    {
        glDetachShader(m_programID, shaders[i].getShader());
    }

    // delete the all shaders
    for(uint8 i = 0; i < shaders.size(); ++i)
    {
        glDeleteShader(shaders[i].getShader());
    }

    // Check the result of the linking
    GLint result;
    glGetProgramiv(m_programID, GL_LINK_STATUS, &result);
    if(!result)
    {
        std::vector<char> log(512);
        glGetProgramInfoLog(m_programID, log.size(), nullptr, &log[0]);
        glDeleteProgram(m_programID);
        m_programID = 0;
        std::cout << std::string(ERROR + "Shader linking failed with this message:\n")  << &log[0];
    }
}

Program::~Program()
{
    if(m_programID != 0)
        glDeleteProgram(m_programID);
}

GLuint Program::getProgram() const
{
    return m_programID;
}

GLint Program::getAttrib(const GLchar *attribName) const
{
    if(!attribName)
        throw std::runtime_error(ERROR + "attribName was NULL");

    GLint attrib;
    attrib = glGetAttribLocation(m_programID, attribName);
    if(attrib == -1)
        throw std::runtime_error(ERROR + std::string("Program attribute not found: ") + attribName);

    return attrib;
}

GLint Program::getUniform(const GLchar *uniformName) const
{
    if(!uniformName)
        throw std::runtime_error(ERROR + "uniformName was NULL");

    GLint uniform;
    uniform = glGetUniformLocation(m_programID, uniformName);
    if(uniform == -1)
        throw std::runtime_error(ERROR + std::string("Program uniform not found: ") + uniformName);

    return uniform;
}

Program::Program(Program const &param) :
    m_programID(param.m_programID)
{
    std::cout << "cons: " << param.getProgram() << std::endl;
}

Program const &Program::operator=(Program const &param)
{
    Program tmp(param);
    std::swap(m_programID, tmp.m_programID);
    return *this;
}
