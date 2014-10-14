#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE
#define GLM_FORCE_PURE
#include <glm/glm.hpp>
#include <glm/common.hpp>
#include "Shader.h"
#include "Program.h"
#include "Mesh.h"
#include "Camera.h"
#include "Skybox.h"
#include "MeshManager.h"
#include "Terrain.h"

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
    }

    virtual void Start();
    virtual void Update(float dt);
    virtual void Render();
    void Loop();

    // Event Functions
    virtual void OnKey(GLFWwindow *window, int key, int scancode, int action, int mods);
    virtual void OnMouseButton(GLFWwindow *window, int button, int action, int mods);
    virtual void OnScroll(GLFWwindow *window, double xOffset, double yOffset);
    virtual void OnCursorEnter(GLFWwindow *window, int entered);
    virtual void OnCursorPos(GLFWwindow *window, double xPos, double yPos);
    virtual void OnResize(GLFWwindow *window, int width, int height);

private:
    void CameraUpdate();

private:
    hmk::Program *basicShader, *skyShader;
    hmk::Camera camera;
    hmk::Mesh  *house, *house2, *windmill, *deskWorn, *stool;
    hmk::Skybox *sky;
    hmk::MeshManager *m_MeshManager;
    hmk::Terrain terrain;
    glm::vec3 color;
    glm::vec3 sunPos;
    float sunAngle;
    double oldMouseX, oldMouseY;
    bool isWireframe;
};
