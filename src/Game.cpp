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

	hmk::ShaderManager::GetInstance()->AddProgram("basic", basicShader);
	hmk::ShaderManager::GetInstance()->AddProgram("sky", skyShader);

	camera.SetFov(60.0f);
	camera.SetViewportAspectRatio(1024.0f / 768.0f);
	camera.SetNearAndFarPlanes(0.5f, 1000.0f);
	camera.LookAt(glm::vec3(0.0f, 0.0f, 0.0f));
	camera.SetPosition(glm::vec3(28.0f, 4.0f, 55.0f));

	sky = new hmk::Skybox();
	sky->Load();

	terrain.Load(PATH + "textures/hm.png");

	m_MeshManager = new hmk::MeshManager();

	house = new hmk::Mesh();
    house->LoadMesh(PATH + "models/Medieval_House.obj");
	house->SetPosition(glm::vec3(50.0f, 0.0f, 40.0f));
	house->SetRotation(-90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	house->SetScale(glm::vec3(0.03f));

	house2 = new hmk::Mesh();
	house2->LoadMesh(PATH + "models/house.obj");
	house2->SetPosition(glm::vec3(15.0f, 0.0f, 30.0f));
	house2->SetRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	house2->SetScale(glm::vec3(0.02f));

	windmill = new hmk::Mesh();
	windmill->LoadMesh(PATH + "models/windmill.obj");
	windmill->SetPosition(glm::vec3(32.0f, 0.0f, 10.0f));
	windmill->SetScale(glm::vec3(0.02f));

	deskWorn = new hmk::Mesh();
	deskWorn->LoadMesh(PATH + "models/deskWorn.obj");
	deskWorn->SetPosition(glm::vec3(30.0f, 0.0f, 42.0f));
	deskWorn->SetScale(glm::vec3(0.07f));

	stool = new hmk::Mesh();
	stool->LoadMesh(PATH + "models/stool.obj");
	stool->SetPosition(glm::vec3(28.6f, 0.0f, 41.4f));
	stool->SetScale(glm::vec3(1.3f));

	m_MeshManager->Add(house);
	m_MeshManager->Add(house->Copy());
	m_MeshManager->GetLast().OffsetPosition(glm::vec3(-2.0f, 0.0, -10.0f));
	m_MeshManager->Add(house->Copy());
	m_MeshManager->GetLast().OffsetPosition(glm::vec3(-4.0f, 0.0, -20.0f));
	m_MeshManager->Add(house2);
	m_MeshManager->Add(windmill);
	m_MeshManager->Add(deskWorn);
	m_MeshManager->Add(stool);
	m_MeshManager->Add(stool->Copy());
	m_MeshManager->GetLast().OffsetPosition(glm::vec3(2.6f, 0.0, 0.0f));
	m_MeshManager->Add(stool->Copy());
	m_MeshManager->GetLast().OffsetPosition(glm::vec3(2.6f, 0.0, 1.4f));
	m_MeshManager->Add(stool->Copy());
	m_MeshManager->GetLast().OffsetPosition(glm::vec3(0.0f, 0.0, 1.4f));

	// Set fog parameters
	hmk::ShaderManager::GetInstance()->Use("basic");
	hmk::ShaderManager::GetInstance()->SetUniformf("fogParams.color", glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
	hmk::ShaderManager::GetInstance()->SetUniformi("fogParams.equation", 0);
	hmk::ShaderManager::GetInstance()->SetUniformf("fogParams.start", 0.01f);
	hmk::ShaderManager::GetInstance()->SetUniformf("fogParams.end", 200.0f);
	hmk::ShaderManager::GetInstance()->Use("");

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
    if(glfwGetKey(Application::GetInstance()->GetWindow(), 'A'))
	    camera.OffsetPosition(-10.0f * dt * camera.GetRight());
    if(glfwGetKey(Application::GetInstance()->GetWindow(), 'D'))
	    camera.OffsetPosition(10.0f * dt * camera.GetRight());
    if(glfwGetKey(Application::GetInstance()->GetWindow(), 'W'))
	    camera.OffsetPosition(50.0f * dt * camera.GetForward());
    if(glfwGetKey(Application::GetInstance()->GetWindow(), 'S'))
	    camera.OffsetPosition(-50.0f * dt * camera.GetForward());
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

	hmk::ShaderManager::GetInstance()->Use("basic");
    m_MeshManager->Render();
	terrain.Render(GL_TRIANGLES);
	hmk::ShaderManager::GetInstance()->Use("");

	sky->Render();
}

/**
 * @brief Main Game Loop
 */
void Game::Loop()
{
    Update(Application::GetInstance()->GetDeltaTime());
    Render();
}

void Game::OnKey(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        Application::GetInstance()->DestroyWindow();
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
	camera.OffsetOrientation(dy * sensitivity, dx * sensitivity);
    oldMouseX = xPos;
    oldMouseY = yPos;
}

void Game::OnResize(GLFWwindow *window, int width, int height)
{
	camera.SetViewportAspectRatio(width / (float) height);
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void Game::CameraUpdate()
{
	hmk::ShaderManager::GetInstance()->Use("basic");
	hmk::ShaderManager::GetInstance()->SetUniformf("worldToCameraMatrix", camera.GetView());
	hmk::ShaderManager::GetInstance()->SetUniformf("cameraToClipMatrix", camera.GetProjection());

	// Light Update
	sunPos = glm::vec3(15.0f, cos(sunAngle * 3.1415f / 180.0f) * 30, sin(sunAngle * 3.1415f / 180.0f) * 30);
	hmk::ShaderManager::GetInstance()->SetUniformf("light.position", glm::vec4(-glm::normalize(sunPos), 1.0f));
	hmk::ShaderManager::GetInstance()->SetUniformf("light.intensity", color);
	hmk::ShaderManager::GetInstance()->Use("");

	hmk::ShaderManager::GetInstance()->Use("sky");
	hmk::ShaderManager::GetInstance()->SetUniformf("worldToCameraMatrix", camera.GetOrientation());
	hmk::ShaderManager::GetInstance()->SetUniformf("cameraToClipMatrix", camera.GetProjection());
	hmk::ShaderManager::GetInstance()->Use("");
}
