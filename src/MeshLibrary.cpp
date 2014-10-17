#include "MeshLibrary.h"

using namespace hmk;

MeshLibrary::MeshLibrary()
{
}

MeshLibrary::~MeshLibrary()
{
    for(auto mesh : m_meshes)
        delete mesh;
}

void MeshLibrary::add(Mesh *mesh)
{
    m_meshes.push_back(mesh);
}

std::vector<Mesh *> MeshLibrary::getMeshes() const
{
    return m_meshes;
}

Mesh &MeshLibrary::getLast()
{
    return *m_meshes[m_meshes.size() - 1];
}

Mesh &MeshLibrary::get(uint32 index)
{
    return *m_meshes[index];
}
