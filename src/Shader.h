#pragma once

#include <GL/glew.h>
#include <string>

namespace hmk {
    /**
    Represents a compiled OpenGL shader.
    */
    class Shader {
    public:
        /**
        Creates a shader from a string of shader source code.

        @param shaderCode  The source code for the shader.
        @param shaderType  Same as the argument to glCreateShader. For example GL_VERTEX_SHADER
        or GL_FRAGMENT_SHADER.

        @throws std::exception if an error occurs.
        */
        Shader(std::string shaderCode, GLenum shaderType, std::string filePath);
        ~Shader();

        /**
        Creates a shader from a text file.

        @param filePath    The path to the text file containing the shader source.
        @param shaderType  Same as the argument to glCreateShader. For example GL_VERTEX_SHADER
        or GL_FRAGMENT_SHADER.

        @throws std::exception if an error occurs.
        */
        static Shader createFromFile(std::string filePath, GLenum shaderType);

        GLuint GetShader() const;
    private:
        GLuint shaderID;
    };
}