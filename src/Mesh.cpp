#include "Mesh.h"
#include "GLHelper.h"
#include "ShaderManager.h"

using namespace hmk;

Mesh::Mesh()
{
    modelMatrix = glm::mat4(1.0f);
	position = rotation = scale = glm::vec3(1.0f);
	angle = 0.0f;
	matrixUpdateNeed = true;
}

Mesh::Mesh(const Mesh &other) :
		modelMatrix(other.modelMatrix), position(other.position), rotation(other.rotation), scale(other.scale),
		tex(other.tex), angle(other.angle), vao(other.vao), vbo(other.vbo), ibo(other.ibo),
	    indexCount(other.indexCount), renderMode(other.renderMode), matrixUpdateNeed(other.matrixUpdateNeed)
{
}

Mesh::~Mesh()
{
	delete tex;
}
const Mesh &Mesh::operator=(Mesh const &param)
{
	Mesh m(param);
	std::swap(indexCount, m.indexCount);
	std::swap(vao, m.vao);
	std::swap(vbo, m.vbo);
	std::swap(ibo, m.ibo);
	std::swap(renderMode, m.renderMode);
	std::swap(position, m.position);
	std::swap(rotation, m.rotation);
	std::swap(scale, m.scale);
	std::swap(angle, m.angle);
	std::swap(matrixUpdateNeed, m.matrixUpdateNeed);
	std::swap(modelMatrix, m.modelMatrix);
	std::swap(tex, m.tex);
	return *this;
}


bool Mesh::LoadMesh(const std::string &meshName)
{
	ModelLoader model;

    if(model.LoadOBJFile(meshName))
    {
	    std::vector<float> vertexData = model.GetVertexData();
	    std::vector<short> indexData = model.GetVertexIndices();
	    size_t vertexSize = model.GetVertexSize();
	    size_t indexSize = model.GetIndexSize();
        indexCount = model.GetIndexCount();
        renderMode = model.GetRenderMode();

		size_t posTexSize = vertexSize + model.GetTexCoordsSize();

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), &vertexData.front(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, &indexData.front(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glEnableVertexAttribArray(VertexAttrib::Position);
        glEnableVertexAttribArray(VertexAttrib::TexCoord);
	    glEnableVertexAttribArray(VertexAttrib::Normal);
        glVertexAttribPointer(VertexAttrib::Position, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glVertexAttribPointer(VertexAttrib::TexCoord, 2, GL_FLOAT, GL_FALSE, 0, (void*)vertexSize);
	    glVertexAttribPointer(VertexAttrib::Normal, 3, GL_FLOAT, GL_FALSE, 0, (void*)posTexSize);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        glBindVertexArray(0);

	    tex = new Texture(PATH + "textures/" +model.GetTextureName(), GL_LINEAR, GL_REPEAT);

	    return true;
    }
    return false;
}

void Mesh::Render()
{
    UpdateModelMatrix();

    glBindVertexArray(vao);
    tex->Bind();
	hmk::ShaderManager::GetInstance()->Use("basic");
    GLint texLoc = hmk::ShaderManager::GetInstance()->GetUniform("tex");
    glUniform1i(texLoc, 0);
	glDrawElements(renderMode, indexCount, GL_UNSIGNED_SHORT, 0);
    tex->Unbind();
	glBindVertexArray(0);

}

void Mesh::Render(GLuint texID)
{
	UpdateModelMatrix();

	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
	hmk::ShaderManager::GetInstance()->Use("basic");
	GLint texLoc = hmk::ShaderManager::GetInstance()->GetUniform("tex");
	glUniform1i(texLoc, 0);
	glDrawElements(renderMode, indexCount, GL_UNSIGNED_SHORT, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glBindVertexArray(0);

}

Mesh* Mesh::Copy()
{
	Mesh *mesh = new Mesh(*this);
	return mesh;
}

glm::mat4 Mesh::GetMatrix() const
{
    return modelMatrix;
}

void Mesh::UpdateModelMatrix()
{
	if(matrixUpdateNeed)
	{
		auto translateMatrix = glm::translate(position);
		auto rotateMatrix = glm::rotate(glm::radians(angle), rotation);
		auto scaleMatrix = glm::scale(scale);
		modelMatrix = translateMatrix * rotateMatrix * scaleMatrix;
		matrixUpdateNeed = false;
	}
	hmk::ShaderManager::GetInstance()->Use("basic");
	GLint modelMatrixLoc = hmk::ShaderManager::GetInstance()->GetUniform("modelToWorldMatrix");
	glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

Mesh &Mesh::SetPosition(glm::vec3 _pos)
{
	position = _pos;
	matrixUpdateNeed = true;
	return *this;
}

Mesh &Mesh::OffsetPosition(glm::vec3 _pos)
{
	position += _pos;
	matrixUpdateNeed = true;
	return *this;
}

Mesh &Mesh::SetRotation(float _angle, glm::vec3 _rot)
{
	angle = _angle;
	rotation = _rot;
	matrixUpdateNeed = true;
	return *this;
}

Mesh &Mesh::OffsetRotation(float _angle, glm::vec3 _rot)
{
	angle += _angle;
	rotation = _rot;
	matrixUpdateNeed = true;
	return *this;
}

Mesh &Mesh::SetScale(glm::vec3 _scale)
{
	scale = _scale;
	matrixUpdateNeed = true;
	return *this;
}

Mesh &Mesh::OffsetScale(glm::vec3 _scale)
{
	scale += _scale;
	matrixUpdateNeed = true;
	return *this;
}
