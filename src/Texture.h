#pragma once

#include <GL/glew.h>
#include <Magick++.h>

namespace hmk
{
    
    /**
     Represents an OpenGL texture
     */
    class Texture
    {
    public:
        /**
         Creates a texture from a bitmap.
         
         The texture will be loaded upside down because tdogl::Bitmap pixel data
         is ordered from the top row down, but OpenGL expects the data to
         be from the bottom row up.
         
         @param bitmap  The bitmap to load the texture from
         @param minMagFiler  GL_NEAREST or GL_LINEAR
         @param wrapMode GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, or GL_CLAMP_TO_BORDER
         */
        Texture(std::string filePath,
                GLint minMagFiler = GL_LINEAR,
                GLint wrapMode = GL_CLAMP_TO_EDGE);
        
        /**
         Deletes the texture object with glDeleteTextures
         */
        ~Texture();
	    Texture(const Texture&);
	    const Texture& operator=(const Texture&);

	    void Bind();
	    void Unbind();
	    void SetParameter(GLenum target, GLenum pname, GLint param);

        /**
         @result The texure object, as created by glGenTextures
         */
        GLuint GetTextureID() const;
        
        /**
         @result The original width (in pixels) of the bitmap this texture was made from
         */
        GLfloat GetOriginalWidth() const;

        /**
         @result The original height (in pixels) of the bitmap this texture was made from
         */
        GLfloat GetOriginalHeight() const;
        
    private:
	    Magick::Image *image;
	    Magick::Blob blob;
        GLuint textureID;
        GLfloat originalWidth;
        GLfloat originalHeight;
    };
    
}
