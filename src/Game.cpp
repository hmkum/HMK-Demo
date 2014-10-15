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

    camera.setFov(60.0f);
    camera.setViewportAspectRatio(1024.0f / 768.0f);
    camera.setNearAndFarPlanes(0.5f, 1000.0f);
    camera.lookAt(glm::vec3(0.0f, 0.0f, 0.0f));
    camera.setPosition(glm::vec3(28.0f, 4.0f, 55.0f));

    sky = new hmk::Skybox();
    sky->load();

    terrain.load(PATH + "textures/hm.png");

    m_MeshManager = new hmk::MeshManager();

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

    m_MeshManager->add(house);
    m_MeshManager->add(house->copy());
    m_MeshManager->getLast().offsetPosition(glm::vec3(-2.0f, 0.0, -10.0f));
    m_MeshManager->add(house->copy());
    m_MeshManager->getLast().offsetPosition(glm::vec3(-4.0f, 0.0, -20.0f));
    m_MeshManager->add(house2);
    m_MeshManager->add(windmill);
    m_MeshManager->add(deskWorn);
    m_MeshManager->add(stool);
    m_MeshManager->add(stool->copy());
    m_MeshManager->getLast().offsetPosition(glm::vec3(2.6f, 0.0, 0.0f));
    m_MeshManager->add(stool->copy());
    m_MeshManager->getLast().offsetPosition(glm::vec3(2.6f, 0.0, 1.4f));
    m_MeshManager->add(stool->copy());
    m_MeshManager->getLast().offsetPosition(glm::vec3(0.0f, 0.0, 1.4f));

    // Set fog parameters
    hmk::ShaderManager::getInstance()->use("basic");
    hmk::ShaderManager::getInstance()->setUniformf("fogParams.color", glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
    hmk::ShaderManager::getInstance()->setUniformi("fogParams.equation", 0);
    hmk::ShaderManager::getInstance()->setUniformf("fogParams.start", 0.01f);
    hmk::ShaderManager::getInstance()->setUniformf("fogParams.end", 200.0f);
    hmk::ShaderManager::getInstance()->use("");

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
    sunPos = glm::vec3(cos(sunAngle*3.1415/180.0)*70, sin(sunAngle*3.1415/180.0)*70, 0.0);

    dLight = new hmk::DirectionalLight();
    dLight->setColor(color);
    dLight->setOrientation(sunAngle, sunAngle);
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

    if(glfwGetKey(Application::getInstance()->getWindow(), 'A'))
        camera.offsetPosition(-10.0f * dt * camera.getRight());
    if(glfwGetKey(Application::getInstance()->getWindow(), 'D'))
        camera.offsetPosition(10.0f * dt * camera.getRight());
    if(glfwGetKey(Application::getInstance()->getWindow(), 'W'))
        camera.offsetPosition(50.0f * dt * camera.getForward());
    if(glfwGetKey(Application::getInstance()->getWindow(), 'S'))
        camera.offsetPosition(-50.0f * dt * camera.getForward());
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
    dLight->render();
    m_MeshManager->render();
    terrain.render(GL_TRIANGLES);
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

void Game::OnKey(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        Application::getInstance()->destroyWindow();
    if(key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        isWireframe = !isWireframe;
}

void Game::OnMouseButton(GLFWwindow *window, int button, int action, int mods)
{
}

void Game::OnScroll(GLFWwindow *window, double xOffset, double yOffset)
{
}

void Game::OnCursorEnter(GLFWwindow *window, int entered)
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
    camera.offsetOrientation(dy * sensitivity, dx * sensitivity);
    oldMouseX = xPos;
    oldMouseY = yPos;
}

void Game::OnResize(GLFWwindow *window, int width, int height)
{
    camera.setViewportAspectRatio(width / (float) height);
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void Game::CameraUpdate()
{
    hmk::ShaderManager::getInstance()->use("basic");
    hmk::ShaderManager::getInstance()->setUniformf("worldToCameraMatrix", camera.getView());
    hmk::ShaderManager::getInstance()->setUniformf("cameraToClipMatrix", camera.getProjection());
    hmk::ShaderManager::getInstance()->use("");

    hmk::ShaderManager::getInstance()->use("sky");
    hmk::ShaderManager::getInstance()->setUniformf("worldToCameraMatrix", camera.getOrientation());
    hmk::ShaderManager::getInstance()->setUniformf("cameraToClipMatrix", camera.getProjection());
    hmk::ShaderManager::getInstance()->use("");
}
