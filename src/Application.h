#pragma once

#include <string>
#include <cassert>
#include <iostream>
#include "Game.h"
#include <GLFW/glfw3.h>

class Application
{
public:

    bool CreateWindow(int _width, int _height, std::string _title, bool _isFullScreen);
    void DestroyWindow();
    void SetGame(Game *_game);
    void Loop();
    float GetDeltaTime() const;
    int GetFps() const;
    GLFWwindow *GetWindow() const;
    static Application *GetInstance();

    virtual void KeyCallbackImpl(GLFWwindow *window, int key, int scancode, int action, int mods);
    void EnableKeyCallback();

    virtual void CursorEnterCallbackImpl(GLFWwindow *window, int entered);
    void EnableCursorEnterCallback();

    virtual void CursorPosCallbackImpl(GLFWwindow *window, double xPos, double yPos);
    void EnableCursorPosCallback();

    virtual void MouseButtonCallbackImpl(GLFWwindow *window, int button, int action, int mods);
    void EnableMouseButtonCallback();

    virtual void ScrollCallbackImpl(GLFWwindow *window, double xOffset, double yOffset);
    void EnableScrollCallback();

    virtual void ResizeWindowImpl(GLFWwindow *window, int width, int height);
    void EnableResizeWindowCallback();
private:
    // Singleton
    Application() {}
    Application(const Application&) {}
    void operator= (const Application&) {}
    static Application *instance;

    Game *game;
    GLFWwindow *mainWindow;
    int width, height;
    std::string title;
    int frame;
    int FPS;
    double time;
    float deltaTime;
	bool isFullScreen;
};
