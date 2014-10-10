#include <iostream>
#include <GL/glew.h>
#include "Terrain.h"
#include "GLHelper.h"
#include "ShaderManager.h"

using namespace hmk;

bool Terrain::Load(std::string heightMap)
{
	Magick::Blob blob;
	try {
		Magick::Image *img = new Magick::Image(heightMap);
		img->write(&blob, "GRAY");
		m_width = (unsigned int) img->rows();
		m_height = (unsigned int) img->columns();
	} catch (Magick::Error &e)
	{
		std::cerr << ERROR << "Could not load terrain" << std::endl;
		return false;
	}

	m_data = (unsigned char*)blob.data();
	m_lenght = (unsigned int) blob.length();
	m_heightScale = 10.0f;
	m_widthScale = 2.0f;

	unsigned r, g, b;
	//unsigned int tri = 0;
	//glm::vec3 triangle[3];
	//std::vector<GLfloat> tmpNorm;
	for(unsigned int z = 0; z < m_height; z++)
	{
		for(unsigned int x = 0; x < m_width; x++)
		{
			float _x, _y, _z;
			_x = float(x) * m_widthScale;
			getPixel(x, z, r, g, b);
			_y = (r / 255.0f) * m_heightScale;
			_z = float(z) * m_widthScale;

			m_vertices.push_back(_x);
			m_vertices.push_back(_y);
			m_vertices.push_back(_z);

			m_texCoords.push_back((x / float(m_height) * (m_height * 0.1f)));
			m_texCoords.push_back((z / float(m_width) * (m_width * 0.1f)));

			m_normals.push_back(1.0f);
			m_normals.push_back(1.0f);
			m_normals.push_back(1.0f);

			/*
			if(tri == 3)
			{
				// Calculate normal
				auto U = triangle[1] - triangle[0];
				auto V = triangle[2] - triangle[0];
				glm::vec3 norm = glm::normalize(glm::cross(U, V));

				tmpNorm.push_back(norm.x);
				tmpNorm.push_back(norm.y);
				tmpNorm.push_back(norm.y);
				tri = 0;
			}
			triangle[tri] = glm::vec3(_x, _y, _z);
			tri++;
		*/
		}
	}

	//for(int i = 0; i < tmpNorm.size(); i++)
	//{
	//	m_normals.push_back(glm::normalize(tmpNorm[i]));
	//}

	for(auto d : m_vertices)
		m_vertData.push_back(d);
	for(auto d : m_texCoords)
		m_vertData.push_back(d);
	for(auto d : m_normals)
		m_vertData.push_back(d);

	// Prepare indices
	unsigned int triCount = ((m_width - 1) * (m_height - 1));
	unsigned int widthCount = 0;
	for(unsigned int i = 0; i < triCount * 2; i++)
	{
		if(widthCount == (m_width - 1))
		{
			widthCount = 0;
			continue;
		}
		else
		{
			/**  0. <--- .1     .
			*     ^ \    ^      .
			*     |  \   |      .
			*     |    \ |      .
			*    5. ---> .6
			*
			*/
			m_indices.push_back(i); // 0
			m_indices.push_back(i + m_width + 1); // 6
			m_indices.push_back(i + m_width); // 5

			m_indices.push_back(i + 1); // 1
			m_indices.push_back(i + m_width + 1); // 6
			m_indices.push_back(i); // 0
			widthCount++;
		}
	}

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertData.size() * sizeof(GLfloat), &m_vertData.front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLshort), &m_indices.front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(VertexAttrib::Position);
	glEnableVertexAttribArray(VertexAttrib::TexCoord);
	glEnableVertexAttribArray(VertexAttrib::Normal);
	glVertexAttribPointer(VertexAttrib::Position, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(VertexAttrib::TexCoord, 2, GL_FLOAT, GL_FALSE, 0, (void*)(m_vertices.size() * sizeof(GLfloat)));
	glVertexAttribPointer(VertexAttrib::Normal, 3, GL_FLOAT, GL_FALSE, 0, (void*)((m_vertices.size() + m_texCoords.size()) * sizeof(GLfloat)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glBindVertexArray(0);

	tex = new Texture(PATH + "textures/grass1.png", GL_LINEAR, GL_REPEAT);

	return true;
}

void Terrain::Render(GLenum mode)
{
	hmk::ShaderManager::GetInstance()->Use("basic");
	GLint modelMatrixLoc = hmk::ShaderManager::GetInstance()->GetUniform("modelToWorldMatrix");
	glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
	tex->Bind();
	GLint texLoc = hmk::ShaderManager::GetInstance()->GetUniform("tex");
	glUniform1i(texLoc, 0);
	glBindVertexArray(vao);
	glDrawElements(mode, (GLsizei)m_indices.size(), GL_UNSIGNED_INT, 0);
	tex->Unbind();
	glBindVertexArray(0);
}

void Terrain::getPixel(int x, int y, unsigned &r, unsigned &g, unsigned &b)
{
	size_t index = (x + y * m_width);
	r = m_data[index];
	g = m_data[index + 1];
	b = m_data[index + 2];
}
