#pragma once
#include <GL/glew.h>
#include "ModelLoader.h"
#include "Texture.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <memory>

namespace hmk
{
    class Mesh
    {
    public:
	    Mesh();
		~Mesh();
		Mesh(const Mesh &other);
	    const Mesh& operator=(const Mesh&);

	    bool LoadMesh(const std::string &meshName);
	    void Render();
	    void Render(GLuint texID);
		Mesh* Copy();

	    Mesh &SetPosition(glm::vec3 _pos);
	    Mesh &OffsetPosition(glm::vec3 _pos);
		Mesh &SetRotation(float _angle, glm::vec3 _rot);
	    Mesh &OffsetRotation(float _angle, glm::vec3 _rot);
		Mesh &SetScale(glm::vec3 _scale);
	    Mesh &OffsetScale(glm::vec3 _scale);

	    glm::mat4 GetMatrix() const;

    private:
	    void UpdateModelMatrix();

    private:
	    glm::mat4 modelMatrix;
	    glm::vec3 position, rotation, scale;
	    Texture *tex;
	    float angle;
	    GLuint vao, vbo, ibo;
	    GLsizei indexCount;
	    GLenum renderMode;
	    bool matrixUpdateNeed;
    };
}
