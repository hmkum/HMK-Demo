#include "MeshManager.h"

using namespace hmk;

MeshManager::MeshManager()
{
}

MeshManager::~MeshManager()
{
    for(auto mesh : m_meshes)
        delete mesh;
}

void MeshManager::add(Mesh *mesh)
{
    m_meshes.push_back(mesh);
}

void MeshManager::render()
{
    for(const auto mesh : m_meshes)
    {
        mesh->render();
    }
}

Mesh &MeshManager::getLast()
{
    return *m_meshes[m_meshes.size() - 1];
}

Mesh &MeshManager::get(uint32 index)
{
    return *m_meshes[index];
}
