#include "Application.h"
#include "GLHelper.h"
#include <stdexcept>
#include <chrono>

Application* Application::instance = nullptr;

/**
 * @brief Create main window
 * @return true if window creation is succeded, otherwise false
 */
bool Application::CreateWindow(int _width, int _height, std::string _title, bool _isFullScreen)
{
    width        = _width;
    height       = _height;
    title        = _title;
    isFullScreen = _isFullScreen;

    if(!glfwInit())
        throw std::runtime_error(ERROR + "glfwInit failed");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if(isFullScreen)
        mainWindow = glfwCreateWindow(width, height, title.c_str(), glfwGetPrimaryMonitor(), nullptr);
    else
        mainWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if(!mainWindow)
    {
        glfwTerminate();
        throw std::runtime_error(ERROR + "glfwCreateWindow failed");
    }

    // Making the OpenGL context current
    glfwMakeContextCurrent(mainWindow);

    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return true;
}

void Application::DestroyWindow()
{
    if(mainWindow)
        glfwDestroyWindow(mainWindow);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void Application::SetGame(Game *_game)
{
    assert(_game != nullptr);
    game = _game;
}

void Application::Loop()
{
    game->Start();
    frame = 0;
    time = 0.0;
    while(!glfwWindowShouldClose(mainWindow))
    {
        std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

        game->Loop();
        glfwSwapBuffers(mainWindow);
        glfwPollEvents();

        std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        frame++;
        time += elapsed.count();
        deltaTime = elapsed.count();

        if(time >= 1.0)
        {
            FPS = frame;
            std::string title = "HMK - FPS: ";
            title += std::to_string(FPS);
            glfwSetWindowTitle(Application::GetInstance()->GetWindow(), title.c_str());
            time = 0;
            frame = 0;
        }
    }
}

float Application::GetDeltaTime() const
{
    return deltaTime;
}

int Application::GetFps() const
{
    return FPS;
}

GLFWwindow *Application::GetWindow() const
{
    return mainWindow;
}

Application *Application::GetInstance()
{
    if(!instance)
        instance = new Application();
    return instance;
}

// ##################### Input Handling Callback Functions ############################

// These are the callback functions for cursor enter/leave window
static void CursorEnterCallback(GLFWwindow* window, int entered)
{
    Application::GetInstance()->CursorEnterCallbackImpl(window, entered);
}

void Application::CursorEnterCallbackImpl(GLFWwindow* window, int entered)
{
    game->OnCursorEnter(window, entered);
}

void Application::EnableCursorEnterCallback()
{
    glfwSetCursorEnterCallback(mainWindow, CursorEnterCallback);
}

// These are the callback functions for keyboard handling
static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Application::GetInstance()->KeyCallbackImpl(window, key, scancode, action, mods);
}

void Application::KeyCallbackImpl(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    game->OnKey(window, key, scancode, action, mods);
}

void Application::EnableKeyCallback()
{
    glfwSetKeyCallback(mainWindow, KeyCallback);
}

// These are the callback functions for cursor position
static void CursorPosCallback(GLFWwindow *window, double xPos, double yPos)
{
    Application::GetInstance()->CursorPosCallbackImpl(window, xPos, yPos);
}

void Application::CursorPosCallbackImpl(GLFWwindow *window, double xPos, double yPos)
{
    game->OnCursorPos(window, xPos, yPos);
}

void Application::EnableCursorPosCallback()
{
    glfwSetCursorPosCallback(mainWindow, CursorPosCallback);
}

// These are the callback functions for mouse button actions
static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    Application::GetInstance()->MouseButtonCallbackImpl(window, button, action, mods);
}

void Application::MouseButtonCallbackImpl(GLFWwindow *window, int button, int action, int mods)
{
    game->OnMouseButton(window, button, action, mods);
}

void Application::EnableMouseButtonCallback()
{
    glfwSetMouseButtonCallback(mainWindow, MouseButtonCallback);
}

// These are the callback functions for scroll

static void ScrollCallback(GLFWwindow *window, double xOffset, double yOffset)
{
    Application::GetInstance()->ScrollCallbackImpl(window, xOffset, yOffset);
}

void Application::ScrollCallbackImpl(GLFWwindow *window, double xOffset, double yOffset)
{
    game->OnScroll(window, xOffset, yOffset);
}

void Application::EnableScrollCallback()
{
    glfwSetScrollCallback(mainWindow, ScrollCallback);
}

static void ResizeWindowCallback(GLFWwindow *window, int width, int height)
{
    Application::GetInstance()->ResizeWindowImpl(window, width, height);
}

void Application::ResizeWindowImpl(GLFWwindow *window, int width, int height)
{
    game->OnResize(window, width, height);
}

void Application::EnableResizeWindowCallback()
{
    glfwSetFramebufferSizeCallback(mainWindow, ResizeWindowCallback);
}
