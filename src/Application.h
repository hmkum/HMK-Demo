#pragma once

#include "base.h"

#include <string>
#include <cassert>
#include <iostream>
#include "Game.h"
#include <thirdparty/sdl/SDL.h>


namespace hmk
{

class Application
{
public: 
	Application();
	~Application();

	virtual bool Initialize(std::string title, int32 width, int32 height);
	virtual bool CreateWindow();
	virtual void MainLoop();
	virtual void DestroyWindow();
	virtual void SetGame(Game *g);

protected:
	SDL_Window *mainWindow;
	SDL_GLContext mainGlContext;

	std::string windowTitle;
	uint16 windowWidth, windowHeight;

	Game *game;
};

}

/*
class Application
{
public:

    virtual bool createWindow(int32 width, int32 height, std::string title, bool isFullScreen);
    void destroyWindow();
    void setGame(Game *game);
    void loop();
    float getDeltaTime() const;
    int32 getFps() const;
    GLFWwindow *getWindow() const;
    std::string getWorkingDirectory();
    static Application *getInstance();

    virtual void keyCallbackImpl(GLFWwindow *window, int32 key, int32 scancode, int32 action, int32 mods);
    void enableKeyCallback();

    virtual void cursorEnterCallbackImpl(GLFWwindow *window, int32 entered);
    void enableCursorEnterCallback();

    virtual void cursorPosCallbackImpl(GLFWwindow *window, double xPos, double yPos);
    void enableCursorPosCallback();

    virtual void mouseButtonCallbackImpl(GLFWwindow *window, int32 button, int32 action, int32 mods);
    void enableMouseButtonCallback();

    virtual void scrollCallbackImpl(GLFWwindow *window, double xOffset, double yOffset);
    void enableScrollCallback();

    virtual void resizeWindowImpl(GLFWwindow *window, int32 width, int32 height);
    void enableResizeWindowCallback();
private:
    // Singleton
    Application() {}
    Application(const Application&) {}
    void operator= (const Application&) {}
    static Application *m_instance;

    Game *m_game;
    GLFWwindow *m_mainWindow;
    int32 m_width, m_height;
    std::string m_title;
    int32 m_frame;
    int32 m_FPS;
    double m_time;
    float m_deltaTime;
    bool m_isFullScreen;
};
*/