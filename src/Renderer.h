#pragma once
#include "base.h"

#include <vector>
#include "Mesh.h"
#include "Camera.h"
#include "Terrain.h"

class Renderer
{
public:
    Renderer();

    void render();

    void addMesh(hmk::Mesh *mesh);
    void addCamera(hmk::Camera *camera);
    void addTerrain(hmk::Terrain *terrain);
private:
    std::vector<hmk::Mesh*> m_meshes;
    hmk::Camera *m_camera;
    hmk::Terrain *m_terrain;
};
