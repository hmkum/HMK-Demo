#include "Renderer.h"

Renderer::Renderer()
{
    m_camera = nullptr;
    m_terrain = nullptr;
}

void Renderer::render()
{
}

void Renderer::addMesh(hmk::Mesh *mesh)
{
    m_meshes.push_back(mesh);
}

void Renderer::addCamera(hmk::Camera *camera)
{
    assert(camera == nullptr);
    m_camera = camera;
}

void Renderer::addTerrain(hmk::Terrain *terrain)
{
    assert(terrain == nullptr);
    m_terrain = terrain;
}
