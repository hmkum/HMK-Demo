#pragma once

#include "base.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/common.hpp>
#include "Shader.h"
#include "Program.h"
#include "Mesh.h"
#include "Camera.h"
#include "Skybox.h"
#include "MeshManager.h"
#include "Terrain.h"
#include "DirectionalLight.h"

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
        delete m_MeshManager;
        delete dLight;
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
    hmk::Program *basicShader, *skyShader;
    hmk::Camera camera;
    hmk::Mesh  *house, *house2, *windmill, *deskWorn, *stool;
    hmk::Skybox *sky;
    hmk::MeshManager *m_MeshManager;
    hmk::DirectionalLight *dLight;
    hmk::Terrain terrain;
    glm::vec3 color;
    float sunAngle;
    double oldMouseX, oldMouseY;
    bool isWireframe;
};
