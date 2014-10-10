#pragma once

#include <vector>
#include <memory>
#include "Mesh.h"

namespace hmk
{
	class MeshManager
	{
	public:
		MeshManager();
		~MeshManager();

		void Add(Mesh *mesh);
		void Render();
		Mesh &GetLast();
		Mesh &Get(unsigned int index);
	private:
		std::vector<Mesh*> m_Meshes;
	};
}