#pragma once
#include "base.h"

#include <string>
#include <vector>
#include <GL/gl.h>
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
    int32 m_width, m_height, m_component;
    float m_heightScale, m_widthScale;
    GLuint m_vao;

    void getPixel(uint32 x, uint32 y, unsigned &r, unsigned &g, unsigned &b);
};
}
