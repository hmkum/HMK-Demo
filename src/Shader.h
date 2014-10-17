#pragma once

#include "thirdparty/GL/glew.h"
#include <string>

namespace hmk {
class Shader {
public:
    Shader(std::string shaderCode, GLenum shaderType, std::string filePath);
    ~Shader();

    static Shader createFromFile(std::string filePath, GLenum shaderType);
    GLuint getShader() const;
private:
    GLuint m_shaderID;
};
}
