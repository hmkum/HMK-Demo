#include <iostream>
#include <string>
#define GLEW_STATIC
#include "src/thirdparty/GL/glew.h"
#include "src/Application.h"
#include <stdexcept>

using namespace std;

const int WIDTH  = 1024;
const int HEIGHT = 768;

int main(int argc, char **argv)
{
    Game *game = new Game();

    string windowTitle = "HMK";
    Application::getInstance()->createWindow(WIDTH, HEIGHT, windowTitle, false);

    glewExperimental = true;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");

    Application::getInstance()->setGame(game);
    Application::getInstance()->enableKeyCallback();
    Application::getInstance()->enableCursorPosCallback();
    Application::getInstance()->enableResizeWindowCallback();
    Application::getInstance()->enableScrollCallback();
    Application::getInstance()->loop();
    Application::getInstance()->destroyWindow();

    delete game;
    return 0;
}

