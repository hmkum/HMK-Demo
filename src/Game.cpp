#include "Game.h"
#include "Application.h"
#include "GLHelper.h"
#include <iostream>
#include "ShaderManager.h"

/**
 * @brief Resource initialization
 */
void Game::Start()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    oldMouseX = oldMouseY = 0.0;
    isWireframe = false;

    window = Application::getInstance()->getWindow();
    renderer = new hmk::Renderer();

    // Load shaders then create programs
    std::vector<hmk::Shader> shaders;
    shaders.push_back(hmk::Shader::createFromFile(PATH + "shaders/vert.shader", GL_VERTEX_SHADER));
    shaders.push_back(hmk::Shader::createFromFile(PATH + "shaders/frag.shader", GL_FRAGMENT_SHADER));
    basicShader = new hmk::Program(shaders);
    shaders.clear();
    shaders.push_back(hmk::Shader::createFromFile(PATH + "shaders/sky.vert", GL_VERTEX_SHADER));
    shaders.push_back(hmk::Shader::createFromFile(PATH + "shaders/sky.frag", GL_FRAGMENT_SHADER));
    skyShader = new hmk::Program(shaders);

    hmk::ShaderManager::getInstance()->addProgram("basic", basicShader);
    hmk::ShaderManager::getInstance()->addProgram("sky", skyShader);

    // Setting up camera
    camera = new hmk::Camera();
    camera->setFov(60.0f);
    camera->setViewportAspectRatio(1024.0f / 768.0f);
    camera->setNearAndFarPlanes(0.5f, 1000.0f);
    camera->lookAt(glm::vec3(0.0f, 0.0f, 0.0f));
    camera->setPosition(glm::vec3(28.0f, 4.0f, 55.0f));
    renderer->addCamera(camera);

    // Load Sky
    sky = new hmk::Skybox();
    sky->load();

    // Create terrain
    terrain = new hmk::Terrain();
    terrain->load(PATH + "textures/hm.png");
    renderer->addTerrain(terrain);

    // Hold house and windmill
    m_structures = new hmk::MeshLibrary();
    // House deskworn and stools
    m_deskStools = new hmk::MeshLibrary();

    house = new hmk::Mesh();
    house->loadMesh(PATH + "models/Medieval_House.obj");
    house->setPosition(glm::vec3(50.0f, 0.0f, 40.0f));
    house->setRotation(-90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    house->setScale(glm::vec3(0.03f));

    house2 = new hmk::Mesh();
    house2->loadMesh(PATH + "models/house.obj");
    house2->setPosition(glm::vec3(15.0f, 0.0f, 30.0f));
    house2->setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    house2->setScale(glm::vec3(0.02f));

    windmill = new hmk::Mesh();
    windmill->loadMesh(PATH + "models/windmill.obj");
    windmill->setPosition(glm::vec3(32.0f, 0.0f, 10.0f));
    windmill->setScale(glm::vec3(0.02f));

    deskWorn = new hmk::Mesh();
    deskWorn->loadMesh(PATH + "models/deskWorn.obj");
    deskWorn->setPosition(glm::vec3(30.0f, 0.0f, 42.0f));
    deskWorn->setScale(glm::vec3(0.07f));

    stool = new hmk::Mesh();
    stool->loadMesh(PATH + "models/stool.obj");
    stool->setPosition(glm::vec3(28.6f, 0.0f, 41.4f));
    stool->setScale(glm::vec3(1.3f));

    m_structures->add(house);
    m_structures->add(house->copy());
    m_structures->getLast().offsetPosition(glm::vec3(-2.0f, 0.0, -10.0f));
    m_structures->add(house->copy());
    m_structures->getLast().offsetPosition(glm::vec3(-4.0f, 0.0, -20.0f));
    m_structures->add(house2);
    m_structures->add(windmill);
    m_deskStools->add(deskWorn);
    m_deskStools->add(stool);
    m_deskStools->add(stool->copy());
    m_deskStools->getLast().offsetPosition(glm::vec3(2.6f, 0.0, 0.0f));
    m_deskStools->add(stool->copy());
    m_deskStools->getLast().offsetPosition(glm::vec3(2.6f, 0.0, 1.4f));
    m_deskStools->add(stool->copy());
    m_deskStools->getLast().offsetPosition(glm::vec3(0.0f, 0.0, 1.4f));

    renderer->addMeshLibrary(m_structures);
    renderer->addMeshLibrary(m_deskStools);

    // Set fog parameters
    fog = new hmk::Fog(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f), 0.01f, 200.0f);
    renderer->addFog(fog);
    renderer->setEnableFog(true);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);

    /***
    * at sunrise sunset = 0.71f, 0.49f, 0.36f
    noon = 0.75f, 0.75f, 0.68f
    clouds, haze=189.0f / 255.0f,190.0f / 255.0f,192.0f / 255.0f
    overcast=174.0f / 255.0f,183.0f / 255.0f,190.0f / 255.0f
    */
    color = glm::vec3(0.71f, 0.49f, 0.36f);
    sunAngle = 0.0f;
    dLight = new hmk::DirectionalLight();
    dLight->setColor(color);
    dLight->setOrientation(sunAngle, sunAngle);
    dLight->enable();

    // Enable ambient light
    renderer->setAmbientLightColor(glm::vec3(0.05f));
}

/**
 * @brief Game update, logic will be here
 * @param dt, delta time
 */
void Game::Update(float dt)
{
    sunAngle += dt * 30.0f;
    if(sunAngle >= 360.0f)
        sunAngle = -360.0f;
    dLight->setOrientation(sunAngle, sunAngle);
    dLight->update();

    if(glfwGetKey(window, 'A'))
        camera->offsetPosition(-10.0f * dt * camera->getRight());
    if(glfwGetKey(window, 'D'))
        camera->offsetPosition(10.0f * dt * camera->getRight());
    if(glfwGetKey(window, 'W'))
        camera->offsetPosition(50.0f * dt * camera->getForward());
    if(glfwGetKey(window, 'S'))
        camera->offsetPosition(-50.0f * dt * camera->getForward());
}

/**
 * @brief All render will be here
 */
void Game::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    CameraUpdate();

    if(isWireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    hmk::ShaderManager::getInstance()->use("basic");
    renderer->render();
    hmk::ShaderManager::getInstance()->use("");

    sky->render();
}

/**
 * @brief Main Game Loop
 */
void Game::Loop()
{
    Update(Application::getInstance()->getDeltaTime());
    Render();
}

void Game::OnKey(GLFWwindow *window, int32 key, int32 scancode, int32 action, int32 mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        Application::getInstance()->destroyWindow();
    if(key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        isWireframe = !isWireframe;

    // CTRL + F  enable/disable fog
    if(key == GLFW_KEY_F && action == GLFW_PRESS && mods == GLFW_MOD_CONTROL)
        renderer->setEnableFog(!renderer->isFogEnable());
    // CTRL + 1 enable/disable directional light
    if(key == GLFW_KEY_1 && action == GLFW_PRESS && mods == GLFW_MOD_CONTROL)
        dLight->isEnable() ? dLight->disable() : dLight->enable();
}

void Game::OnMouseButton(GLFWwindow *window, int32 button, int32 action, int32 mods)
{
}

void Game::OnScroll(GLFWwindow *window, double xOffset, double yOffset)
{
}

void Game::OnCursorEnter(GLFWwindow *window, int32 entered)
{
}

void Game::OnCursorPos(GLFWwindow *window, double xPos, double yPos)
{
    float dx = (float) (xPos - oldMouseX);
    float dy = (float) (yPos - oldMouseY);
    static bool first = true;
    if(first)
    {
        dx = 0.0f;
        dy = 0.0f;
        first = false;
    }
    const float sensitivity = 0.25f;
    camera->offsetOrientation(dy * sensitivity, dx * sensitivity);
    oldMouseX = xPos;
    oldMouseY = yPos;
}

void Game::OnResize(GLFWwindow *window, int32 width, int32 height)
{
    camera->setViewportAspectRatio(width / (float) height);
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void Game::CameraUpdate()
{
    hmk::ShaderManager::getInstance()->use("sky");
    hmk::ShaderManager::getInstance()->setUniformf("worldToCameraMatrix", camera->getOrientation());
    hmk::ShaderManager::getInstance()->setUniformf("cameraToClipMatrix", camera->getProjection());
    hmk::ShaderManager::getInstance()->use("");
}
