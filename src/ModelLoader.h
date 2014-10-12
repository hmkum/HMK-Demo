#pragma once
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace hmk
{
    class ModelLoader
    {
    public:
	    ModelLoader();
	    ~ModelLoader();

	    bool loadOBJFile(std::string fileName);

	    std::vector<float> getVertexData() const;
	    std::vector<short> getVertexIndices() const;
	    std::vector<float> getNormals() const;

	    std::string getTextureName() const;

	    std::size_t getVertexSize() const;
	    std::size_t getIndexSize() const;
	    std::size_t getTexCoordsSize() const;
	    std::size_t getNormalSize() const;
	    std::size_t getVertexCount() const;
	    GLsizei getIndexCount();

	    GLenum getRenderMode() const;

    private:
	    bool initScene(const aiScene *scene, const std::string &filename);
	    void initMesh(unsigned int index, const aiMesh *mesh);
	    bool initMaterials(const aiScene *scene, const std::string &filename);

    private:
	    std::vector<float> m_vertexPositions;
	    std::vector<float> m_vertexNormals;
	    std::vector<float> m_vertexTexCoords;
	    std::vector<float> m_vertexData;
	    std::vector<short> m_vertexIndices;
	    std::string m_textureName;
	    GLenum m_renderMode;
    };
}