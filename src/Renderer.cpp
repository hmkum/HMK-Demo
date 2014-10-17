#include "Renderer.h"
#include "ShaderManager.h"
#include <iostream>

using namespace hmk;

Renderer::Renderer()
{
    m_camera = nullptr;
    m_terrain = nullptr;
}

void Renderer::render()
{

    // Render meshes
    for(uint32 i = 0; i < m_meshes.size(); i++)
    {
        std::vector<hmk::Mesh*> meshes = m_meshes[i]->getMeshes();
        for(uint32 j = 0; j < meshes.size(); j++)
        {
            hmk::Mesh *mesh = meshes[j];
            mesh->render("basic");
        }
    }

    // Render camera
    if(m_camera)
    {
        hmk::ShaderManager::getInstance()->use("basic");
        hmk::ShaderManager::getInstance()->setUniformf("worldToCameraMatrix", m_camera->getView());
        hmk::ShaderManager::getInstance()->setUniformf("cameraToClipMatrix", m_camera->getProjection());
        hmk::ShaderManager::getInstance()->use("");
    }

    // Render terrain
    if(m_terrain)
    {
        m_terrain->render(GL_TRIANGLES);
    }
}

void Renderer::addMeshLibrary(hmk::MeshLibrary *mesh)
{
    m_meshes.push_back(mesh);
}

void Renderer::addCamera(hmk::Camera *camera)
{
    assert(camera != nullptr);
    m_camera = camera;
}

void Renderer::addTerrain(hmk::Terrain *terrain)
{
    assert(terrain != nullptr);
    m_terrain = terrain;
}
