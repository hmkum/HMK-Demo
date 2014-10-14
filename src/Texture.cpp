#include "Texture.h"
#include "GLHelper.h"
#include <stdexcept>
#include <iostream>

using namespace hmk;

Texture::Texture(std::string filePath, GLint minMagFiler, GLint wrapMode)
{
    try {
        m_image = new Magick::Image(filePath);
        m_image->flip();
        m_image->write(&m_blob, "RGBA");
        Magick::Geometry geometry = m_image->size();
        m_width = geometry.width();
        m_height = geometry.height();
    }catch (Magick::Error &e)
    {
        std::cout << (ERROR + "Loading Texture: " + filePath + "\n" + e.what()) << std::endl;
        delete m_image;
    }

    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMagFiler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minMagFiler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 (GLsizei)m_image->columns(),
                 (GLsizei)m_image->rows(),
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 m_blob.data());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_textureID);
}


void Texture::bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::unbind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::setParameter(GLenum target, GLenum pname, GLint param)
{
    glTexParameteri(target, pname, param);
}

GLuint Texture::getTextureID() const
{
    return m_textureID;
}

GLfloat Texture::getWidth() const
{
    return m_width;
}

GLfloat Texture::getHeight() const
{
    return m_height;
}

Texture::Texture(Texture const &param) :
    m_textureID(param.m_textureID), m_width(param.m_width), m_height(param.m_height)
{
}

const Texture &Texture::operator=(Texture const &param)
{
    Texture tmp(param);

    std::swap(m_textureID, tmp.m_textureID);
    std::swap(m_width, tmp.m_width);
    std::swap(m_height, tmp.m_height);
    return *this;
}
