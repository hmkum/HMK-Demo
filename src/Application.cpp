#include "Application.h"
#include "GLHelper.h"
#include <stdexcept>
#include <chrono>

Application* Application::m_instance = nullptr;

/**
 * @brief Create main window
 * @return true if window creation is succeded, otherwise false
 */
bool Application::createWindow(int width, int32 height, std::string title, bool isFullScreen)
{
    m_width        = width;
    m_height       = height;
    m_title        = title;
    m_isFullScreen = isFullScreen;

    if(!glfwInit())
        throw std::runtime_error(ERROR + "glfwInit failed");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if(m_isFullScreen)
        m_mainWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), glfwGetPrimaryMonitor(), nullptr);
    else
        m_mainWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

    if(!m_mainWindow)
    {
        glfwTerminate();
        throw std::runtime_error(ERROR + "glfwCreateWindow failed");
    }

    // Making the OpenGL context current
    glfwMakeContextCurrent(m_mainWindow);

    glfwSetInputMode(m_mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return true;
}

void Application::destroyWindow()
{
    if(m_mainWindow)
        glfwDestroyWindow(m_mainWindow);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void Application::setGame(Game *game)
{
    assert(game != nullptr);
    m_game = game;
}

void Application::loop()
{
    m_game->Start();
    m_frame = 0;
    m_time = 0.0;
    while(!glfwWindowShouldClose(m_mainWindow))
    {
        std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

        m_game->Loop();
        glfwSwapBuffers(m_mainWindow);
        glfwPollEvents();

        std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        m_frame++;
        m_time += elapsed.count();
        m_deltaTime = elapsed.count();

        if(m_time >= 1.0)
        {
            m_FPS = m_frame;
            std::string title = "HMK - FPS: ";
            title += std::to_string(m_FPS);
            glfwSetWindowTitle(Application::getInstance()->getWindow(), title.c_str());
            m_time = 0;
            m_frame = 0;
        }
    }
}

float Application::getDeltaTime() const
{
    return m_deltaTime;
}

int32 Application::getFps() const
{
    return m_FPS;
}

GLFWwindow *Application::getWindow() const
{
    return m_mainWindow;
}

std::string Application::getWorkingDirectory()
{
    char currPath[FILENAME_MAX];
    GetCurrentDir(currPath, sizeof(currPath));
    return std::string(currPath);
}

Application *Application::getInstance()
{
    if(!m_instance)
        m_instance = new Application();
    return m_instance;
}

// ##################### Input Handling Callback Functions ############################

// These are the callback functions for cursor enter/leave window
static void CursorEnterCallback(GLFWwindow* window, int32 entered)
{
    Application::getInstance()->cursorEnterCallbackImpl(window, entered);
}

void Application::cursorEnterCallbackImpl(GLFWwindow *window, int32 entered)
{
    m_game->OnCursorEnter(window, entered);
}

void Application::enableCursorEnterCallback()
{
    glfwSetCursorEnterCallback(m_mainWindow, CursorEnterCallback);
}

// These are the callback functions for keyboard handling
static void KeyCallback(GLFWwindow* window, int32 key, int32 scancode, int32 action, int32 mods)
{
    Application::getInstance()->keyCallbackImpl(window, key, scancode, action, mods);
}

void Application::keyCallbackImpl(GLFWwindow *window, int32 key, int32 scancode, int32 action, int32 mods)
{
    m_game->OnKey(window, key, scancode, action, mods);
}

void Application::enableKeyCallback()
{
    glfwSetKeyCallback(m_mainWindow, KeyCallback);
}

// These are the callback functions for cursor position
static void CursorPosCallback(GLFWwindow *window, double xPos, double yPos)
{
    Application::getInstance()->cursorPosCallbackImpl(window, xPos, yPos);
}

void Application::cursorPosCallbackImpl(GLFWwindow *window, double xPos, double yPos)
{
    m_game->OnCursorPos(window, xPos, yPos);
}

void Application::enableCursorPosCallback()
{
    glfwSetCursorPosCallback(m_mainWindow, CursorPosCallback);
}

// These are the callback functions for mouse button actions
static void MouseButtonCallback(GLFWwindow *window, int32 button, int32 action, int32 mods)
{
    Application::getInstance()->mouseButtonCallbackImpl(window, button, action, mods);
}

void Application::mouseButtonCallbackImpl(GLFWwindow *window, int32 button, int32 action, int32 mods)
{
    m_game->OnMouseButton(window, button, action, mods);
}

void Application::enableMouseButtonCallback()
{
    glfwSetMouseButtonCallback(m_mainWindow, MouseButtonCallback);
}

// These are the callback functions for scroll

static void ScrollCallback(GLFWwindow *window, double xOffset, double yOffset)
{
    Application::getInstance()->scrollCallbackImpl(window, xOffset, yOffset);
}

void Application::scrollCallbackImpl(GLFWwindow *window, double xOffset, double yOffset)
{
    m_game->OnScroll(window, xOffset, yOffset);
}

void Application::enableScrollCallback()
{
    glfwSetScrollCallback(m_mainWindow, ScrollCallback);
}

static void ResizeWindowCallback(GLFWwindow *window, int32 width, int32 height)
{
    Application::getInstance()->resizeWindowImpl(window, width, height);
}

void Application::resizeWindowImpl(GLFWwindow *window, int32 width, int32 height)
{
    m_game->OnResize(window, width, height);
}

void Application::enableResizeWindowCallback()
{
    glfwSetFramebufferSizeCallback(m_mainWindow, ResizeWindowCallback);
}
