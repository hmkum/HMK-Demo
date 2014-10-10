#include "ModelLoader.h"
#include "GLHelper.h"
#include <stdint.h>

using namespace hmk;

ModelLoader::ModelLoader()
{
    renderMode = GL_TRIANGLES;
}

ModelLoader::~ModelLoader()
{

}

bool ModelLoader::LoadOBJFile(std::string fileName)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(fileName, aiProcess_FlipWindingOrder | aiProcess_CalcTangentSpace |
			aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

	if(scene)
	{
		return InitScene(scene, fileName);
	}
	else
	{
		std::cerr << ERROR << "\nError: Could not parse mesh: " << importer.GetErrorString() << std::endl;
		return false;
	}
}

bool ModelLoader::InitScene(const aiScene *scene, const std::string &filename)
{
	// Initialize the meshes in the scene one by one
	for (unsigned int i = 0 ; i < scene->mNumMeshes ; i++)
	{
		const aiMesh* mesh = scene->mMeshes[i];
		InitMesh(i, mesh);
	}
	for(auto &x : vertexPositions)
		vertexData.push_back(x);
	for(auto &x : vertexTexCoords)
		vertexData.push_back(x);
	for(auto &x : vertexNormals)
		vertexData.push_back(x);
	return InitMaterials(scene, filename);
}

void ModelLoader::InitMesh(unsigned int index, const aiMesh *mesh)
{
	const aiVector3D zero3D(0.0f, 0.0f, 0.0f);
	const aiVector3D one3D(1.0f, 1.0f, 1.0f);

	for(unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		const aiVector3D *pos = &(mesh->mVertices[i]);
		const aiVector3D *normal = mesh->HasNormals() ? &(mesh->mNormals[i]): &one3D;
		const aiVector3D *tex = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &zero3D;

		vertexPositions.push_back(pos->x);
		vertexPositions.push_back(pos->y);
		vertexPositions.push_back(pos->z);

		vertexTexCoords.push_back(tex->x);
		vertexTexCoords.push_back(tex->y);

		vertexNormals.push_back(normal->x);
		vertexNormals.push_back(normal->y);
		vertexNormals.push_back(normal->z);
	}

	for(unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		const aiFace &face = mesh->mFaces[i];
		renderMode = GL_TRIANGLES;
		vertexIndices.push_back(face.mIndices[0]);
		vertexIndices.push_back(face.mIndices[1]);
		vertexIndices.push_back(face.mIndices[2]);
	}
}

bool ModelLoader::InitMaterials(const aiScene *scene, const std::string &filename)
{
	bool ret = true;

	for(unsigned int i = 0; i < scene->mNumMaterials; i++)
	{
		const aiMaterial *material = scene->mMaterials[i];

		aiString path;
		if(material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
			textureName = path.data;
		else
			textureName = "default.png";
	}

	return ret;
}

std::vector<float> ModelLoader::GetVertexData() const
{
	return vertexData;
}

std::vector<short> ModelLoader::GetVertexIndices() const
{
    return vertexIndices;
}

std::vector<float> ModelLoader::GetNormals() const
{
	return vertexNormals;
}

std::size_t ModelLoader::GetTexCoordsSize() const
{
	return vertexTexCoords.size() * sizeof(float);
}

std::size_t ModelLoader::GetNormalSize() const
{
	return vertexNormals.size() * sizeof(float);
}

std::size_t ModelLoader::GetVertexSize() const
{
    return vertexPositions.size() * sizeof(float);
}

std::size_t ModelLoader::GetIndexSize() const
{
    return vertexIndices.size() * sizeof(std::size_t);
}

std::size_t ModelLoader::GetVertexCount() const
{
    return vertexPositions.size();
}

GLsizei ModelLoader::GetIndexCount()
{
    return vertexIndices.size();
}

GLenum ModelLoader::GetRenderMode() const
{
    return renderMode;
}


std::string ModelLoader::GetTextureName() const
{
	return textureName;
}
