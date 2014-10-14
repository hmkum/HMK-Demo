#pragma once

#include <vector>
#include <memory>
#include "Mesh.h"

namespace hmk
{
class MeshManager
{
public:
    MeshManager();
    ~MeshManager();

    void add(Mesh *mesh);
    void render();
    Mesh &getLast();
    Mesh &get(unsigned int index);
private:
    std::vector<Mesh*> m_meshes;
};
}
