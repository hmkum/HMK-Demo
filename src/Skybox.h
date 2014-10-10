#pragma once

#include <memory>
#include "Mesh.h"
#include "Texture.h"
namespace hmk
{
	class Skybox
	{
	public:
		Skybox(){}
		~Skybox(){}

		void Load();
		void Render();
	private:
		std::shared_ptr<Mesh> mesh;
		GLuint vao;
		GLuint texID;
	};
}