#include "MeshManager.h"

using namespace hmk;

MeshManager::MeshManager()
{
}

MeshManager::~MeshManager()
{
	for(auto mesh : m_Meshes)
		delete mesh;
}

void MeshManager::Add(Mesh *mesh)
{
	m_Meshes.push_back(mesh);
}

void MeshManager::Render()
{
	for(const auto mesh : m_Meshes)
	{
		mesh->Render();
	}
}

Mesh &MeshManager::GetLast()
{
	return *m_Meshes[m_Meshes.size() - 1];
}

Mesh &MeshManager::Get(unsigned int index)
{
	return *m_Meshes[index];
}