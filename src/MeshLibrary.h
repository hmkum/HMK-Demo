#pragma once

#include "base.h"

#include <vector>
#include <memory>
#include "Mesh.h"

namespace hmk
{
class MeshLibrary
{
public:
    MeshLibrary();
    ~MeshLibrary();

    void add(Mesh *mesh);
    std::vector<Mesh *> getMeshes() const;
    Mesh &getLast();
    Mesh &get(uint32 index);
private:
    std::vector<Mesh*> m_meshes;
};
}
