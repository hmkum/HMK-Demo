#include "Renderer.h"
#include "ShaderManager.h"
#include <iostream>

using namespace hmk;

Renderer::Renderer()
{
    m_camera = nullptr;
    m_terrain = nullptr;
    m_fog = nullptr;
    m_fogEnable = false;
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

    // Render fog
    if(m_fogEnable)
    {
        GLint lastProgram = hmk::ShaderManager::getInstance()->getActiveProgram();
        hmk::ShaderManager::getInstance()->use("basic");
        hmk::ShaderManager::getInstance()->setUniformf("fogParams.color", m_fog->getColor());
        hmk::ShaderManager::getInstance()->setUniformi("fogParams.equation", m_fog->getEquation());
        hmk::ShaderManager::getInstance()->setUniformf("fogParams.start", m_fog->getStart());
        hmk::ShaderManager::getInstance()->setUniformf("fogParams.end", m_fog->getEnd());
        hmk::ShaderManager::getInstance()->use(lastProgram);
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

void Renderer::addFog(Fog *fog)
{
    assert(fog != nullptr);
    m_fog = fog;
}

void Renderer::setEnableFog(bool fogEnable)
{
    m_fogEnable = fogEnable;
    if(m_fogEnable)
    {
        GLint lastProgram = hmk::ShaderManager::getInstance()->getActiveProgram();
        hmk::ShaderManager::getInstance()->use("basic");
        hmk::ShaderManager::getInstance()->setUniformi("isFogEnable", 1);
        hmk::ShaderManager::getInstance()->use(lastProgram);
    }
    else
    {
        GLint lastProgram = hmk::ShaderManager::getInstance()->getActiveProgram();
        hmk::ShaderManager::getInstance()->use("basic");
        hmk::ShaderManager::getInstance()->setUniformi("isFogEnable", 0);
        hmk::ShaderManager::getInstance()->use(lastProgram);
    }
}

bool Renderer::isFogEnable() const
{
    return m_fogEnable;
}
