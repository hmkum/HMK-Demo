#pragma once
#include "base.h"

#include "thirdparty/GL/glew.h"
#include <string>

namespace hmk
{
class Texture
{
public:
    Texture();
    ~Texture();
    Texture(const Texture&);
    const Texture& operator=(const Texture&);

	void Initialize(std::string filePath,
					GLint minMagFiler = GL_LINEAR,
					GLint wrapMode = GL_CLAMP_TO_EDGE);
    void bind();
    void unbind();
    void setParameter(GLenum target, GLenum pname, GLint param);

    GLuint getTextureID() const;

    GLfloat getWidth() const;
    GLfloat getHeight() const;

private:
    GLuint m_textureID;
    unsigned char *m_data;
    int32 m_width;
    int32 m_height;
    int32 m_component;

};

}
