#include <iostream>
#include <string>
#include <GL/glew.h>
#include "src/Application.h"
#include <stdexcept>
#include <Magick++.h>
using namespace std;

const int WIDTH  = 1024;
const int HEIGHT = 768;

int main(int argc, char **argv)
{
	Magick::InitializeMagick(*argv);
	Game *game = new Game();

    string windowTitle = "HMK";
    Application::GetInstance()->CreateWindow(WIDTH, HEIGHT, windowTitle, false);

    glewExperimental = true;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");

    Application::GetInstance()->SetGame(game);
    Application::GetInstance()->EnableKeyCallback();
    Application::GetInstance()->EnableCursorPosCallback();
    Application::GetInstance()->EnableResizeWindowCallback();
    Application::GetInstance()->EnableScrollCallback();
    Application::GetInstance()->Loop();
    Application::GetInstance()->DestroyWindow();

    delete game;
    return 0;
}

