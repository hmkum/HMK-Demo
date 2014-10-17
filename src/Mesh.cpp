#include "Mesh.h"
#include "GLHelper.h"
#include "ShaderManager.h"

using namespace hmk;

Mesh::Mesh()
{
    m_modelMatrix = glm::mat4(1.0f);
    m_position = m_rotation = m_scale = glm::vec3(1.0f);
    m_angle = 0.0f;
    m_matrixUpdateNeed = true;
}

Mesh::Mesh(const Mesh &other) :
    m_modelMatrix(other.m_modelMatrix), m_position(other.m_position), m_rotation(other.m_rotation),
    m_scale(other.m_scale), m_tex(other.m_tex), m_angle(other.m_angle), m_vao(other.m_vao), m_vbo(other.m_vbo),
    m_ibo(other.m_ibo), m_indexCount(other.m_indexCount), m_renderMode(other.m_renderMode),
    m_matrixUpdateNeed(other.m_matrixUpdateNeed)
{
}

Mesh::~Mesh()
{
    delete m_tex;
}
const Mesh &Mesh::operator=(Mesh const &param)
{
    Mesh m(param);
    std::swap(m_indexCount, m.m_indexCount);
    std::swap(m_vao, m.m_vao);
    std::swap(m_vbo, m.m_vbo);
    std::swap(m_ibo, m.m_ibo);
    std::swap(m_renderMode, m.m_renderMode);
    std::swap(m_position, m.m_position);
    std::swap(m_rotation, m.m_rotation);
    std::swap(m_scale, m.m_scale);
    std::swap(m_angle, m.m_angle);
    std::swap(m_matrixUpdateNeed, m.m_matrixUpdateNeed);
    std::swap(m_modelMatrix, m.m_modelMatrix);
    std::swap(m_tex, m.m_tex);
    return *this;
}


bool Mesh::loadMesh(const std::string &meshName)
{
    ModelLoader model;

    if(model.loadOBJFile(meshName))
    {
        std::vector<float> vertexData = model.getVertexData();
        std::vector<short> indexData = model.getVertexIndices();
        size_t vertexSize = model.getVertexSize();
        size_t indexSize = model.getIndexSize();
        m_indexCount = model.getIndexCount();
        m_renderMode = model.getRenderMode();

        size_t posTexSize = vertexSize + model.getTexCoordsSize();

        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), &vertexData.front(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glGenBuffers(1, &m_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, &indexData.front(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glEnableVertexAttribArray(VertexAttrib::Position);
        glEnableVertexAttribArray(VertexAttrib::TexCoord);
        glEnableVertexAttribArray(VertexAttrib::Normal);
        glVertexAttribPointer(VertexAttrib::Position, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glVertexAttribPointer(VertexAttrib::TexCoord, 2, GL_FLOAT, GL_FALSE, 0, (void*)vertexSize);
        glVertexAttribPointer(VertexAttrib::Normal, 3, GL_FLOAT, GL_FALSE, 0, (void*)posTexSize);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

        glBindVertexArray(0);

        m_tex = new Texture(PATH + "textures/" + model.getTextureName(), GL_LINEAR, GL_REPEAT);

        return true;
    }
    return false;
}

void Mesh::render()
{
    updateModelMatrix();

    glBindVertexArray(m_vao);
    m_tex->bind();
    hmk::ShaderManager::getInstance()->use("basic");
    GLint texLoc = hmk::ShaderManager::getInstance()->getUniform("tex");
    glUniform1i(texLoc, 0);
    glDrawElements(m_renderMode, m_indexCount, GL_UNSIGNED_SHORT, 0);
    m_tex->unbind();
    glBindVertexArray(0);

}

void Mesh::render(std::string shaderName)
{
    updateModelMatrix();

    glBindVertexArray(m_vao);
    m_tex->bind();
    GLint lastProgram = hmk::ShaderManager::getInstance()->getActiveProgram();
    hmk::ShaderManager::getInstance()->use(shaderName);
    GLint texLoc = hmk::ShaderManager::getInstance()->getUniform("tex");
    glUniform1i(texLoc, 0);
    glDrawElements(m_renderMode, m_indexCount, GL_UNSIGNED_SHORT, 0);
    m_tex->unbind();
    hmk::ShaderManager::getInstance()->use(lastProgram);
    glBindVertexArray(0);
}

Mesh* Mesh::copy()
{
    Mesh *mesh = new Mesh(*this);
    return mesh;
}

glm::mat4 Mesh::getMatrix() const
{
    return m_modelMatrix;
}

void Mesh::updateModelMatrix()
{
    if(m_matrixUpdateNeed)
    {
        auto translateMatrix = glm::translate(m_position);
        auto rotateMatrix = glm::rotate(glm::radians(m_angle), m_rotation);
        auto scaleMatrix = glm::scale(m_scale);
        m_modelMatrix = translateMatrix * rotateMatrix * scaleMatrix;
        m_matrixUpdateNeed = false;
    }
    hmk::ShaderManager::getInstance()->use("basic");
    GLint modelMatrixLoc = hmk::ShaderManager::getInstance()->getUniform("modelToWorldMatrix");
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
}

Mesh &Mesh::setPosition(glm::vec3 _pos)
{
    m_position = _pos;
    m_matrixUpdateNeed = true;
    return *this;
}

Mesh &Mesh::offsetPosition(glm::vec3 _pos)
{
    m_position += _pos;
    m_matrixUpdateNeed = true;
    return *this;
}

Mesh &Mesh::setRotation(float _angle, glm::vec3 _rot)
{
    m_angle = _angle;
    m_rotation = _rot;
    m_matrixUpdateNeed = true;
    return *this;
}

Mesh &Mesh::offsetRotation(float _angle, glm::vec3 _rot)
{
    m_angle += _angle;
    m_rotation = _rot;
    m_matrixUpdateNeed = true;
    return *this;
}

Mesh &Mesh::setScale(glm::vec3 _scale)
{
    m_scale = _scale;
    m_matrixUpdateNeed = true;
    return *this;
}

Mesh &Mesh::offsetScale(glm::vec3 _scale)
{
    m_scale += _scale;
    m_matrixUpdateNeed = true;
    return *this;
}
