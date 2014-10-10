#include <iostream>
#include "ShaderManager.h"
#include "GLHelper.h"

using namespace hmk;

ShaderManager* ShaderManager::m_Instance = nullptr;

ShaderManager* ShaderManager::GetInstance()
{
	if(m_Instance == nullptr)
		m_Instance = new ShaderManager();
	return m_Instance;
}

void ShaderManager::AddProgram(std::string name, Program *program)
{
	std::map<std::string, Program*> p;
	p[name] = program;
	m_Programs.push_back(p);
}

void ShaderManager::Use(std::string name)
{
	if(name == "")
	{
		glUseProgram(0);
		return ;
	}
	for(auto &p : m_Programs)
	{
		if(p.find(name) != p.end())
		{
			m_Name = name;
			glUseProgram(p.begin()->second->GetProgram());
		}
	}
}

GLuint ShaderManager::GetProgram(std::string name)
{
	for(auto &p : m_Programs)
	{
		if(p.find(name) != p.end())
		{
			return (p.begin()->second->GetProgram());
		}
	}
	return 0;
}

GLint ShaderManager::GetActiveProgram()
{
	GLint id;
	glGetIntegerv(GL_CURRENT_PROGRAM, &id);
	return id;
}

GLint ShaderManager::GetUniform(std::string name)
{
	GLint id = GetActiveProgram();
	auto loc = glGetUniformLocation(id, name.c_str());
	if(loc == -1)
		std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
	return loc;
}

bool ShaderManager::SetUniformf(std::string name, float v0)
{
	GLint loc = GetUniform(name);
	if(loc == -1)
	{
		std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
		return false;
	}
	else
	{
		glUniform1f(loc, v0);
		return true;
	}
}

bool ShaderManager::SetUniformf(std::string name, float v0, float v1)
{
	GLint loc = GetUniform(name);
	if(loc == -1)
	{
		std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
		return false;
	}
	else
	{
		glUniform2f(loc, v0, v1);
		return true;
	}
}

bool ShaderManager::SetUniformf(std::string name, float v0, float v1, float v2)
{
	GLint loc = GetUniform(name);
	if(loc == -1)
	{
		std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
		return false;
	}
	else
	{
		glUniform3f(loc, v0, v1, v2);
		return true;
	}
}

bool ShaderManager::SetUniformf(std::string name, float v0, float v1, float v2, float v3)
{
	GLint loc = GetUniform(name);
	if(loc == -1)
	{
		std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
		return false;
	}
	else
	{
		glUniform4f(loc, v0, v1, v2, v3);
		return true;
	}
}

bool ShaderManager::SetUniformf(std::string name, glm::vec2 v)
{
	GLint loc = GetUniform(name);
	if(loc == -1)
	{
		std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
		return false;
	}
	else
	{
		glUniform2fv(loc, 1, glm::value_ptr(v));
		return true;
	}
}

bool ShaderManager::SetUniformf(std::string name, glm::vec3 v)
{
	GLint loc = GetUniform(name);
	if(loc == -1)
	{
		std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
		return false;
	}
	else
	{
		glUniform3fv(loc, 1, glm::value_ptr(v));
		return true;
	}
}

bool ShaderManager::SetUniformf(std::string name, glm::vec4 v)
{
	GLint loc = GetUniform(name);
	if(loc == -1)
	{
		std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
		return false;
	}
	else
	{
		glUniform4fv(loc, 1, glm::value_ptr(v));
		return true;
	}
}

bool ShaderManager::SetUniformi(std::string name, int v0)
{
	GLint loc = GetUniform(name);
	if(loc == -1)
	{
		std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
		return false;
	}
	else
	{
		glUniform1i(loc, v0);
		return true;
	}
}

bool ShaderManager::SetUniformi(std::string name, int v0, int v1)
{
	GLint loc = GetUniform(name);
	if(loc == -1)
	{
		std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
		return false;
	}
	else
	{
		glUniform2i(loc, v0, v1);
		return true;
	}
}

bool ShaderManager::SetUniformi(std::string name, int v0, int v1, int v2)
{
	GLint loc = GetUniform(name);
	if(loc == -1)
	{
		std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
		return false;
	}
	else
	{
		glUniform3i(loc, v0, v1, v2);
		return true;
	}
}

bool ShaderManager::SetUniformi(std::string name, int v0, int v1, int v2, int v3)
{
	GLint loc = GetUniform(name);
	if(loc == -1)
	{
		std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
		return false;
	}
	else
	{
		glUniform4i(loc, v0, v1, v2, v3);
		return true;
	}
}

bool ShaderManager::SetUniformf(std::string name, glm::mat3 m)
{
	GLint loc = GetUniform(name);
	if(loc == -1)
	{
		std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
		return false;
	}
	else
	{
		glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(m));
		return true;
	}
}

bool ShaderManager::SetUniformf(std::string name, glm::mat4 m)
{
	GLint loc = GetUniform(name);
	if(loc == -1)
	{
		std::cerr << ERROR << "\nError: Could not find uniform \'" << name << "\'" << std::endl;
		return false;
	}
	else
	{
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m));
		return true;
	}
}
