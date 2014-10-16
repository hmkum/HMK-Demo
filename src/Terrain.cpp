#include <iostream>
#include <GL/glew.h>
#include "Terrain.h"
#include "GLHelper.h"
#include "ShaderManager.h"
#include "stb_image.h"

using namespace hmk;

bool Terrain::load(std::string heightMap)
{

    m_data = stbi_load(heightMap.c_str(), &m_width, &m_height, &m_component, 0);

    if(!m_data)
    {
        std::cerr << ERROR << "Could not load terrain" << std::endl;
        return false;
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

    m_heightScale = 10.0f;
    m_widthScale = 2.0f;

    unsigned r, g, b;
    for(uint32 z = 0; z < m_height; z++)
    {
        for(uint32 x = 0; x < m_width; x++)
        {
            float _x, _y, _z;
            _x = float(x) * m_widthScale;
            getPixel(x, z, r, g, b);
            _y = (r / 255.0f) * m_heightScale;
            _z = float(z) * m_widthScale;

            m_vertices.push_back(_x);
            m_vertices.push_back(_y);
            m_vertices.push_back(_z);

            m_texCoords.push_back((x / float(m_height) * (m_height * 0.1f)));
            m_texCoords.push_back((z / float(m_width) * (m_width * 0.1f)));

            m_normals.push_back(1.0f);
            m_normals.push_back(1.0f);
            m_normals.push_back(1.0f);
        }
    }

    for(auto d : m_vertices)
        m_vertData.push_back(d);
    for(auto d : m_texCoords)
        m_vertData.push_back(d);
    for(auto d : m_normals)
        m_vertData.push_back(d);

    // Prepare indices
    uint32 triCount = ((m_width - 1) * (m_height - 1));
    uint32 widthCount = 0;
    for(uint32 i = 0; i < triCount * 2; i++)
    {
        if(widthCount == (m_width - 1))
        {
            widthCount = 0;
            continue;
        }
        else
        {
            /**  0. <--- .1     .
            *     ^ \    ^      .
            *     |  \   |      .
            *     |    \ |      .
            *    5. ---> .6
            *
            */
            m_indices.push_back(i); // 0
            m_indices.push_back(i + m_width + 1); // 6
            m_indices.push_back(i + m_width); // 5

            m_indices.push_back(i + 1); // 1
            m_indices.push_back(i + m_width + 1); // 6
            m_indices.push_back(i); // 0
            widthCount++;
        }
    }

    GLuint vbo, ibo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertData.size() * sizeof(GLfloat), &m_vertData.front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLshort), &m_indices.front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(VertexAttrib::Position);
    glEnableVertexAttribArray(VertexAttrib::TexCoord);
    glEnableVertexAttribArray(VertexAttrib::Normal);
    glVertexAttribPointer(VertexAttrib::Position, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(VertexAttrib::TexCoord, 2, GL_FLOAT, GL_FALSE, 0, (void*)(m_vertices.size() * sizeof(GLfloat)));
    glVertexAttribPointer(VertexAttrib::Normal, 3, GL_FLOAT, GL_FALSE, 0, (void*)((m_vertices.size() + m_texCoords.size()) * sizeof(GLfloat)));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glBindVertexArray(0);

    tex = new Texture(PATH + "textures/grass1.png", GL_LINEAR, GL_REPEAT);

    return true;
}

void Terrain::render(GLenum mode)
{
    hmk::ShaderManager::getInstance()->use("basic");
    GLint modelMatrixLoc = hmk::ShaderManager::getInstance()->getUniform("modelToWorldMatrix");
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
    tex->bind();
    GLint texLoc = hmk::ShaderManager::getInstance()->getUniform("tex");
    glUniform1i(texLoc, 0);
    glBindVertexArray(m_vao);
    glDrawElements(mode, (GLsizei)m_indices.size(), GL_UNSIGNED_INT, 0);
    tex->unbind();
    glBindVertexArray(0);
}

void Terrain::getPixel(uint32 x, uint32 y, unsigned &r, unsigned &g, unsigned &b)
{
    size_t index = (x + y * m_width) * m_component;
    r = m_data[index];
    g = m_data[index + 1];
    b = m_data[index + 2];
}
