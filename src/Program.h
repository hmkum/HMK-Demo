#pragma once

#include "Shader.h"
#include <vector>

namespace hmk
{
    class Program{
    public:
	    Program() {}

        Program(const std::vector<Shader>& shaders);
        ~Program();
	    Program(const Program&);
	    const Program& operator=(const Program&);

        GLuint getProgram() const;
        GLint getAttrib(const GLchar* attribName) const;
        GLint getUniform(const GLchar* uniformName) const;


    private:
        GLuint m_programID;
    };
}