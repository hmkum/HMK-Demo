#pragma once

#include <string>
#include <GL/gl.h>
#include "Magick++.h"
#include "Texture.h"

namespace hmk
{
class Terrain
{
public:
    Terrain() {}
    ~Terrain() { delete tex;}

    bool load(std::string heightMap);
    void render(GLenum mode);
private:
    unsigned char *m_data;
    std::vector<GLfloat> m_vertData;
    std::vector<GLfloat> m_vertices;
    std::vector<GLfloat> m_texCoords;
    std::vector<GLfloat> m_normals;
    std::vector<GLuint> m_indices;
    Texture *tex;
    unsigned int m_width, m_height, m_lenght;
    float m_heightScale, m_widthScale;
    GLuint m_vao;

    void getPixel(int x, int y, unsigned &r, unsigned &g, unsigned &b);
};
}
