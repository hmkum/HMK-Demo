#pragma once
#include "thirdparty/GL/glew.h"
#include "ModelLoader.h"
#include "Texture.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <memory>

namespace hmk
{
class Mesh
{
public:
    Mesh();
    ~Mesh();
    Mesh(const Mesh &other);
    const Mesh& operator=(const Mesh&);

    bool loadMesh(const std::string &meshName);
    void render();
    void render(std::string shaderName);
    Mesh* copy();

    Mesh &setPosition(glm::vec3 _pos);
    Mesh &offsetPosition(glm::vec3 _pos);
    Mesh &setRotation(float _angle, glm::vec3 _rot);
    Mesh &offsetRotation(float _angle, glm::vec3 _rot);
    Mesh &setScale(glm::vec3 _scale);
    Mesh &offsetScale(glm::vec3 _scale);

    glm::mat4 getMatrix() const;

private:
    void updateModelMatrix();

private:
    glm::mat4 m_modelMatrix;
    glm::vec3 m_position, m_rotation, m_scale;
    Texture *m_tex;
    float m_angle;
    GLuint m_vao, m_vbo, m_ibo;
    GLsizei m_indexCount;
    GLenum m_renderMode;
    bool m_matrixUpdateNeed;
};
}
