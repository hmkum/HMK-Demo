#include <iostream>
#include <string>
#define GLEW_STATIC
#include "src/thirdparty/GL/glew.h"
#include "src/Application.h"
#include "src/WindowsApplication.h"
#include <stdexcept>

using namespace std;

const int WIDTH  = 1024;
const int HEIGHT = 768;

int main(int argc, char **argv)
{
    Game *game = new Game();

    string windowTitle = "HMK";

#ifdef _WIN32
	hmk::Application *app = new hmk::WindowsApplication();
#endif
#ifdef __linux__
	hmk::Application *app = new hmk::LinuxApplication();
#endif
	if(app->Initialize(windowTitle, WIDTH, HEIGHT))
	{
		app->CreateWindow();
		app->SetGame(game);
	}

    glewExperimental = true;
    if(glewInit() != GLEW_OK)
       cerr << "glewInit failed" << std::endl;

	app->MainLoop();
	app->DestroyWindow();
    delete game;
    return 0;
}

