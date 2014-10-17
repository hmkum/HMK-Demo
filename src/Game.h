#pragma once

#include "base.h"

#include "thirdparty/GL/glew.h"
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/common.hpp>
#include "Shader.h"
#include "Program.h"
#include "Mesh.h"
#include "Camera.h"
#include "Skybox.h"
#include "MeshLibrary.h"
#include "Terrain.h"
#include "Fog.h"
#include "DirectionalLight.h"
#include "Renderer.h"

class Game
{
public:
    Game() {}
    virtual ~Game()
    {
        delete house;
        delete basicShader;
        delete skyShader;
        delete windmill;
        delete deskWorn;
        delete stool;

        delete basicShader;
        delete skyShader;
        delete sky;
        delete m_structures;
        delete m_deskStools;
        delete dLight;
        delete camera;
        delete terrain;
        delete fog;
        delete renderer;
    }

    virtual void Start();
    virtual void Update(float dt);
    virtual void Render();
    void Loop();

    // Event Functions
    virtual void OnKey(GLFWwindow *window, int32 key, int32 scancode, int32 action, int32 mods);
    virtual void OnMouseButton(GLFWwindow *window, int32 button, int32 action, int32 mods);
    virtual void OnScroll(GLFWwindow *window, double xOffset, double yOffset);
    virtual void OnCursorEnter(GLFWwindow *window, int32 entered);
    virtual void OnCursorPos(GLFWwindow *window, double xPos, double yPos);
    virtual void OnResize(GLFWwindow *window, int32 width, int32 height);

private:
    void CameraUpdate();

private:
    GLFWwindow *window;
    hmk::Renderer *renderer;
    hmk::Program *basicShader, *skyShader;
    hmk::Camera *camera;
    hmk::Mesh  *house, *house2, *windmill, *deskWorn, *stool;
    hmk::Skybox *sky;
    hmk::MeshLibrary *m_structures, *m_deskStools;
    hmk::DirectionalLight *dLight;
    hmk::Terrain *terrain;
    hmk::Fog *fog;
    glm::vec3 color;
    float sunAngle;
    double oldMouseX, oldMouseY;
    bool isWireframe;
};
