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

	    bool LoadOBJFile(std::string fileName);

	    std::vector<float> GetVertexData() const;
	    std::vector<short> GetVertexIndices() const;
	    std::vector<float> GetNormals() const;

	    std::string GetTextureName() const;

	    std::size_t GetVertexSize() const;
	    std::size_t GetIndexSize() const;
	    std::size_t GetTexCoordsSize() const;
	    std::size_t GetNormalSize() const;
	    std::size_t GetVertexCount() const;
	    GLsizei GetIndexCount();

	    GLenum GetRenderMode() const;

    private:
	    bool InitScene(const aiScene *scene, const std::string &filename);
	    void InitMesh(unsigned int index, const aiMesh *mesh);
	    bool InitMaterials(const aiScene *scene, const std::string &filename);

    private:
	    std::vector<float> vertexPositions;
	    std::vector<float> vertexNormals;
	    std::vector<float> vertexTexCoords;
	    std::vector<float> vertexData;
	    std::vector<short> vertexIndices;
	    std::string textureName;
	    GLenum renderMode;
    };
}