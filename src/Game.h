#pragma once

#include "base.h"

#include <thirdparty/GL/glew.h>
#include <thirdparty/sdl/SDL.h>
#define GLM_FORCE_RADIANS
#include <thirdparty/glm/glm.hpp>
#include <thirdparty/glm/common.hpp>
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
    void OnKeyDown(SDL_Keysym keysym);
	void OnKeyUp(SDL_Keysym keysym);
    void OnMouseButtonDown(SDL_MouseButtonEvent e);
	void OnMouseButtonUp(SDL_MouseButtonEvent e);
    void OnMouseWheel(int32 xOffset, int32 yOffset);
    void OnMouseMotion(SDL_MouseMotionEvent e);
    void OnResize(int32 width, int32 height);

private:
    void CameraUpdate();

private:
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
	bool keys[259]; // SDL's all key
    bool isWireframe;
	bool isRightMouseClicked;
	
};
