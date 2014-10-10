#include "Skybox.h"
#include "GLHelper.h"
#include "ShaderManager.h"
using namespace hmk;

const GLenum types[6] = {  GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };

void Skybox::Load()
{
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);

	Magick::Image *img = nullptr;
	Magick::Blob blob;

	std::string filenames[] = {"textures/txStormydays_front.bmp", "textures/txStormydays_back.bmp",
			"textures/txStormydays_up.bmp","textures/txStormydays_down.bmp",
			"textures/txStormydays_right.bmp","textures/txStormydays_left.bmp"};

	for(size_t i = 0; i < 6; i++)
	{
		try {
			img = new Magick::Image(PATH + filenames[i]);
			img->write(&blob, "RGBA");
		}catch (Magick::Error &e)
		{
			delete img;
			throw std::runtime_error(ERROR + "Loading Texture: " + filenames[i] + "\n" + e.what());
		}

		glTexImage2D(types[i], 0, GL_RGBA,
				(GLsizei)img->columns(), (GLsizei)img->rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, blob.data());
		delete img;
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	hmk::ShaderManager::GetInstance()->Use("sky");
	GLint texLoc = hmk::ShaderManager::GetInstance()->GetUniform("tex");
	glUniform1i(texLoc, 0);
	hmk::ShaderManager::GetInstance()->Use("");

	float points[] = {
			-100.0f,  100.0f, -100.0f,
			-100.0f, -100.0f, -100.0f,
			100.0f, -100.0f, -100.0f,
			100.0f, -100.0f, -100.0f,
			100.0f,  100.0f, -100.0f,
			-100.0f,  100.0f, -100.0f,

			-100.0f, -100.0f,  100.0f,
			-100.0f, -100.0f, -100.0f,
			-100.0f,  100.0f, -100.0f,
			-100.0f,  100.0f, -100.0f,
			-100.0f,  100.0f,  100.0f,
			-100.0f, -100.0f,  100.0f,

			100.0f, -100.0f, -100.0f,
			100.0f, -100.0f,  100.0f,
			100.0f,  100.0f,  100.0f,
			100.0f,  100.0f,  100.0f,
			100.0f,  100.0f, -100.0f,
			100.0f, -100.0f, -100.0f,

			-100.0f, -100.0f,  100.0f,
			-100.0f,  100.0f,  100.0f,
			100.0f,  100.0f,  100.0f,
			100.0f,  100.0f,  100.0f,
			100.0f, -100.0f,  100.0f,
			-100.0f, -100.0f,  100.0f,

			-100.0f,  100.0f, -100.0f,
			100.0f,  100.0f, -100.0f,
			100.0f,  100.0f,  100.0f,
			100.0f,  100.0f,  100.0f,
			-100.0f,  100.0f,  100.0f,
			-100.0f,  100.0f, -100.0f,

			-100.0f, -100.0f, -100.0f,
			-100.0f, -100.0f,  100.0f,
			100.0f, -100.0f, -100.0f,
			100.0f, -100.0f, -100.0f,
			-100.0f, -100.0f,  100.0f,
			100.0f, -100.0f,  100.0f
	};
	GLuint vbo;
	glGenBuffers (1, &vbo);
	glBindBuffer (GL_ARRAY_BUFFER, vbo);
	glBufferData (GL_ARRAY_BUFFER, 3 * 36 * sizeof (float), &points, GL_STATIC_DRAW);

	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);
	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Skybox::Render()
{
	glDepthMask (GL_FALSE);
	glCullFace(GL_FRONT);
	hmk::ShaderManager::GetInstance()->Use("sky");
	glActiveTexture (GL_TEXTURE0);
	glBindTexture (GL_TEXTURE_CUBE_MAP, texID);
	glBindVertexArray (vao);
	glDrawArrays (GL_TRIANGLES, 0, 36);
	glBindVertexArray (0);
	hmk::ShaderManager::GetInstance()->Use("");
	glCullFace(GL_BACK);
	glDepthMask (GL_TRUE);
}
