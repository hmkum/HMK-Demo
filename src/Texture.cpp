#include "Texture.h"
#include "GLHelper.h"
#include <stdexcept>
#include <iostream>
#include "thirdparty/stb_image.h"

using namespace hmk;

Texture::Texture()
{
}

Texture::~Texture()
{
    stbi_image_free(m_data);
    glDeleteTextures(1, &m_textureID);
}

void Texture::Initialize(std::string filePath, GLint minMagFiler, GLint wrapMode)
{
	m_data = stbi_load(filePath.c_str(), &m_width, &m_height, &m_component, 0);

	if(!m_data)
	{
		std::cout << (ERROR + "Loading Texture: " + filePath + "\n") << std::endl;
		return;
	}

	GLint format;
	switch(m_component)
	{
	case 3:
		format = GL_RGB;
		break;
	case 4:
		format = GL_RGBA;
		break;
	default:
		format = GL_RGBA;
	}

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMagFiler);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minMagFiler);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexImage2D(GL_TEXTURE_2D,
		0,
		format,
		(GLsizei)m_width,
		(GLsizei)m_height,
		0,
		format,
		GL_UNSIGNED_BYTE,
		m_data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
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
