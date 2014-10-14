#pragma once

#include <memory>
#include "Mesh.h"
#include "Texture.h"
namespace hmk
{
class Skybox
{
public:
    Skybox(){}
    ~Skybox(){ delete m_mesh; }

    void load();
    void render();
private:
    Mesh *m_mesh;
    GLuint m_vao;
    GLuint m_texID;
};
}
