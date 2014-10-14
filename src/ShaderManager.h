#pragma once

#include <vector>
#include <map>
#include <string>
#include "Program.h"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace hmk
{
class ShaderManager
{
public:
    static ShaderManager* getInstance();

    void addProgram(std::string, Program *program);
    void use(std::string name);
    GLint getActiveProgram();
    GLuint getProgram(std::string name);
    GLint getUniform(std::string name);
    bool setUniformf(std::string name, float v0);
    bool setUniformf(std::string name, float v0, float v1);
    bool setUniformf(std::string name, float v0, float v1, float v2);
    bool setUniformf(std::string name, float v0, float v1, float v2, float v3);
    bool setUniformf(std::string name, glm::vec2 v);
    bool setUniformf(std::string name, glm::vec3 v);
    bool setUniformf(std::string name, glm::vec4 v);
    bool setUniformi(std::string name, int v0);
    bool setUniformi(std::string name, int v0, int v1);
    bool setUniformi(std::string name, int v0, int v1, int v2);
    bool setUniformi(std::string name, int v0, int v1, int v2, int v3);
    bool setUniformf(std::string name, glm::mat3 m);
    bool setUniformf(std::string name, glm::mat4 m);
private:
    // Singleton
    ShaderManager() {}
    ShaderManager(const ShaderManager&) {}
    static ShaderManager *m_instance;

    std::vector<std::map<std::string, Program*>> m_programs;
    std::string m_name;
};
}
