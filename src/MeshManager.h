#pragma once

#include "base.h"

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
    Mesh &get(uint32 index);
private:
    std::vector<Mesh*> m_meshes;
};
}
