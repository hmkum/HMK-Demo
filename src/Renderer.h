#pragma once
#include "base.h"

#include <vector>
#include "Mesh.h"
#include "MeshLibrary.h"
#include "Camera.h"
#include "Terrain.h"

namespace hmk
{
class Renderer
{
public:
    Renderer();

    void render();

    void addMeshLibrary(hmk::MeshLibrary *meshMgr);
    void addCamera(hmk::Camera *camera);
    void addTerrain(hmk::Terrain *terrain);
private:
    std::vector<hmk::MeshLibrary*> m_meshes;
    hmk::Camera *m_camera;
    hmk::Terrain *m_terrain;
};
}
