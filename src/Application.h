#pragma once

#include <string>
#include <cassert>
#include <iostream>
#include "Game.h"
#include <GLFW/glfw3.h>
#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

class Application
{
public:

    bool createWindow(int width, int height, std::string title, bool isFullScreen);
    void destroyWindow();
    void setGame(Game *game);
    void loop();
    float getDeltaTime() const;
    int getFps() const;
    GLFWwindow *getWindow() const;
    std::string getWorkingDirectory();
    static Application *getInstance();

    virtual void keyCallbackImpl(GLFWwindow *window, int key, int scancode, int action, int mods);
    void enableKeyCallback();

    virtual void cursorEnterCallbackImpl(GLFWwindow *window, int entered);
    void enableCursorEnterCallback();

    virtual void cursorPosCallbackImpl(GLFWwindow *window, double xPos, double yPos);
    void enableCursorPosCallback();

    virtual void mouseButtonCallbackImpl(GLFWwindow *window, int button, int action, int mods);
    void enableMouseButtonCallback();

    virtual void scrollCallbackImpl(GLFWwindow *window, double xOffset, double yOffset);
    void enableScrollCallback();

    virtual void resizeWindowImpl(GLFWwindow *window, int width, int height);
    void enableResizeWindowCallback();
private:
    // Singleton
    Application() {}
    Application(const Application&) {}
    void operator= (const Application&) {}
    static Application *m_instance;

    Game *m_game;
    GLFWwindow *m_mainWindow;
    int m_width, m_height;
    std::string m_title;
    int m_frame;
    int m_FPS;
    double m_time;
    float m_deltaTime;
    bool m_isFullScreen;
};
