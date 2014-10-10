#pragma once

#include <vector>
#include <map>
#include <string>
#include "Program.h"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace hmk
{
	class ShaderManager
	{
	public:
		static ShaderManager* GetInstance();

		void AddProgram(std::string, Program *program);
		void Use(std::string name);
		GLint GetActiveProgram();
		GLuint GetProgram(std::string name);
		GLint GetUniform(std::string name);
		bool SetUniformf(std::string name, float v0);
		bool SetUniformf(std::string name, float v0, float v1);
		bool SetUniformf(std::string name, float v0, float v1, float v2);
		bool SetUniformf(std::string name, float v0, float v1, float v2, float v3);
		bool SetUniformf(std::string name, glm::vec2 v);
		bool SetUniformf(std::string name, glm::vec3 v);
		bool SetUniformf(std::string name, glm::vec4 v);
		bool SetUniformi(std::string name, int v0);
		bool SetUniformi(std::string name, int v0, int v1);
		bool SetUniformi(std::string name, int v0, int v1, int v2);
		bool SetUniformi(std::string name, int v0, int v1, int v2, int v3);
		bool SetUniformf(std::string name, glm::mat3 m);
		bool SetUniformf(std::string name, glm::mat4 m);
	private:
		// Singleton
		ShaderManager() {}
		ShaderManager(const ShaderManager&) {}
		static ShaderManager *m_Instance;

		std::vector<std::map<std::string, Program*>> m_Programs;
		std::string m_Name;
	};
}