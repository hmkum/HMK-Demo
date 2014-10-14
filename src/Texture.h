#pragma once

#include <GL/glew.h>
#include <Magick++.h>

namespace hmk
{
class Texture
{
public:
    Texture(std::string filePath,
            GLint minMagFiler = GL_LINEAR,
            GLint wrapMode = GL_CLAMP_TO_EDGE);

    ~Texture();
    Texture(const Texture&);
    const Texture& operator=(const Texture&);

    void bind();
    void unbind();
    void setParameter(GLenum target, GLenum pname, GLint param);

    GLuint getTextureID() const;

    GLfloat getWidth() const;
    GLfloat getHeight() const;

private:
    Magick::Image *m_image;
    Magick::Blob m_blob;
    GLuint m_textureID;
    GLfloat m_width;
    GLfloat m_height;
};

}
