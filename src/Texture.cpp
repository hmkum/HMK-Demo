#include "Texture.h"
#include "GLHelper.h"
#include <stdexcept>
#include <iostream>

using namespace hmk;

Texture::Texture(std::string filePath, GLint minMagFiler, GLint wrapMode)
{
	try {
		image = new Magick::Image(filePath);
		image->flip();
		image->write(&blob, "RGBA");
		Magick::Geometry geometry = image->size();
		originalWidth = geometry.width();
		originalHeight = geometry.height();
	}catch (Magick::Error &e)
	{
		std::cout << (ERROR + "Loading Texture: " + filePath + "\n" + e.what()) << std::endl;
		delete image;
	}

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMagFiler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minMagFiler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    glTexImage2D(GL_TEXTURE_2D,
                 0, 
                 GL_RGBA,
		         (GLsizei)image->columns(),
		         (GLsizei)image->rows(),
                 0, 
                 GL_RGBA,
                 GL_UNSIGNED_BYTE, 
                 blob.data());
	glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, &textureID);
}


void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::Unbind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::SetParameter(GLenum target, GLenum pname, GLint param)
{
	glTexParameteri(target, pname, param);
}

GLuint Texture::GetTextureID() const
{
    return textureID;
}

GLfloat Texture::GetOriginalWidth() const
{
    return originalWidth;
}

GLfloat Texture::GetOriginalHeight() const
{
    return originalHeight;
}

Texture::Texture(Texture const &param) :
	textureID(param.textureID), originalWidth(param.originalWidth), originalHeight(param.originalHeight)
{
}

const Texture &Texture::operator=(Texture const &param)
{
	Texture tmp(param);

	std::swap(textureID, tmp.textureID);
	std::swap(originalWidth, tmp.originalWidth);
	std::swap(originalHeight, tmp.originalHeight);
	return *this;
}
