#include <iostream>
#include "ShaderManager.h"
#include "GLHelper.h"

using namespace hmk;

ShaderManager* ShaderManager::m_instance = nullptr;

ShaderManager* ShaderManager::getInstance()
{
    if(m_instance == nullptr)
        m_instance = new ShaderManager();
    return m_instance;
}

void ShaderManager::addProgram(std::string name, Program *program)
{
    std::map<std::string, Program*> p;
    p[name] = program;
    m_programs.push_back(p);
}

void ShaderManager::use(std::string name)
{
    if(name == "")
    {
        glUseProgram(0);
        return ;
    }
    for(auto &p : m_programs)
    {
        if(p.find(name) != p.end())
        {
            m_name = name;
            glUseProgram(p.begin()->second->getProgram());
        }
    }
}

void ShaderManager::use(GLint program)
{
    if(program != getActiveProgram())
        glUseProgram(program);
}

GLuint ShaderManager::getProgram(std::string name)
{
    for(auto &p : m_programs)
    {
        if(p.find(name) != p.end())
        {
            return (p.begin()->second->getProgram());
        }
    }
    return 0;
}

GLint ShaderManager::getActiveProgram()
{
    GLint id;
    glGetIntegerv(GL_CURRENT_PROGRAM, &id);
    return id;
}

GLint ShaderManager::getUniform(std::string name)
{
    GLint id = getActiveProgram();
    auto loc = glGetUniformLocation(id, name.c_str());
    if(loc == -1)
        std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
    return loc;
}

bool ShaderManager::setUniformf(std::string name, float v0)
{
    GLint loc = getUniform(name);
    if(loc == -1)
    {
        std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
        return false;
    }
    else
    {
        glUniform1f(loc, v0);
        return true;
    }
}

bool ShaderManager::setUniformf(std::string name, float v0, float v1)
{
    GLint loc = getUniform(name);
    if(loc == -1)
    {
        std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
        return false;
    }
    else
    {
        glUniform2f(loc, v0, v1);
        return true;
    }
}

bool ShaderManager::setUniformf(std::string name, float v0, float v1, float v2)
{
    GLint loc = getUniform(name);
    if(loc == -1)
    {
        std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
        return false;
    }
    else
    {
        glUniform3f(loc, v0, v1, v2);
        return true;
    }
}

bool ShaderManager::setUniformf(std::string name, float v0, float v1, float v2, float v3)
{
    GLint loc = getUniform(name);
    if(loc == -1)
    {
        std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
        return false;
    }
    else
    {
        glUniform4f(loc, v0, v1, v2, v3);
        return true;
    }
}

bool ShaderManager::setUniformf(std::string name, glm::vec2 v)
{
    GLint loc = getUniform(name);
    if(loc == -1)
    {
        std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
        return false;
    }
    else
    {
        glUniform2fv(loc, 1, glm::value_ptr(v));
        return true;
    }
}

bool ShaderManager::setUniformf(std::string name, glm::vec3 v)
{
    GLint loc = getUniform(name);
    if(loc == -1)
    {
        std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
        return false;
    }
    else
    {
        glUniform3fv(loc, 1, glm::value_ptr(v));
        return true;
    }
}

bool ShaderManager::setUniformf(std::string name, glm::vec4 v)
{
    GLint loc = getUniform(name);
    if(loc == -1)
    {
        std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
        return false;
    }
    else
    {
        glUniform4fv(loc, 1, glm::value_ptr(v));
        return true;
    }
}

bool ShaderManager::setUniformi(std::string name, int32 v0)
{
    GLint loc = getUniform(name);
    if(loc == -1)
    {
        std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
        return false;
    }
    else
    {
        glUniform1i(loc, v0);
        return true;
    }
}

bool ShaderManager::setUniformi(std::string name, int32 v0, int32 v1)
{
    GLint loc = getUniform(name);
    if(loc == -1)
    {
        std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
        return false;
    }
    else
    {
        glUniform2i(loc, v0, v1);
        return true;
    }
}

bool ShaderManager::setUniformi(std::string name, int32 v0, int32 v1, int32 v2)
{
    GLint loc = getUniform(name);
    if(loc == -1)
    {
        std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
        return false;
    }
    else
    {
        glUniform3i(loc, v0, v1, v2);
        return true;
    }
}

bool ShaderManager::setUniformi(std::string name, int32 v0, int32 v1, int32 v2, int32 v3)
{
    GLint loc = getUniform(name);
    if(loc == -1)
    {
        std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
        return false;
    }
    else
    {
        glUniform4i(loc, v0, v1, v2, v3);
        return true;
    }
}

bool ShaderManager::setUniformf(std::string name, glm::mat3 m)
{
    GLint loc = getUniform(name);
    if(loc == -1)
    {
        std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
        return false;
    }
    else
    {
        glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(m));
        return true;
    }
}

bool ShaderManager::setUniformf(std::string name, glm::mat4 m)
{
    GLint loc = getUniform(name);
    if(loc == -1)
    {
        std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
        return false;
    }
    else
    {
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m));
        return true;
    }
}
