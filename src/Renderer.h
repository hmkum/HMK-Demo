#pragma once
#include "base.h"

#include <vector>
#include "Mesh.h"
#include "MeshLibrary.h"
#include "Camera.h"
#include "Terrain.h"
#include "Fog.h"

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
    void addFog(hmk::Fog *fog);

    void setEnableFog(bool fogEnable);
    bool isFogEnable() const;

    void setAmbientLightColor(glm::vec3 color);
private:
    std::vector<hmk::MeshLibrary*> m_meshes;
    hmk::Camera *m_camera;
    hmk::Terrain *m_terrain;
    hmk::Fog *m_fog;

    glm::vec3 m_ambientLightColor;

    bool m_fogEnable;
};
}
