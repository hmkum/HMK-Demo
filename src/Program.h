#pragma once

#include "Shader.h"
#include <vector>

namespace hmk
{
    /**
    Represents an OpenGL program made by linking shaders.
    */
    class Program{
    public:
	    Program() {}
        /**
        Creates a program by linking a list of hmk::Shader objects

        @param shaders  The shaders to link together to make the program

        @throws std::exception if an error occurs.

        @see hmk::Shader
        */
        Program(const std::vector<Shader>& shaders);
        ~Program();

	    /**
	    * Copy constructor
	    */
	    Program(const Program&);

	    /**
	    * Assignment operator
	    */
	    const Program& operator=(const Program&);

        /**
        @result The program's object ID, as returned from glCreateProgram
        */
        GLuint GetProgram() const;


        /**
        @result The attribute index for the given name, as returned from glGetAttribLocation.
        */
        GLint GetAttrib(const GLchar* attribName) const;


        /**
        @result The uniform index for the given name, as returned from glGetUniformLocation.
        */
        GLint GetUniform(const GLchar* uniformName) const;


    private:
        GLuint programID;
    };
}