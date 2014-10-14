#include "ModelLoader.h"
#include "GLHelper.h"
#include <stdint.h>

using namespace hmk;

ModelLoader::ModelLoader()
{
    m_renderMode = GL_TRIANGLES;
}

ModelLoader::~ModelLoader()
{

}

bool ModelLoader::loadOBJFile(std::string fileName)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(fileName, aiProcess_FlipWindingOrder | aiProcess_CalcTangentSpace |
                                             aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

    if(scene)
    {
        return initScene(scene, fileName);
    }
    else
    {
        std::cerr << ERROR << "\nError: Could not parse mesh: " << importer.GetErrorString() << std::endl;
        return false;
    }
}

bool ModelLoader::initScene(const aiScene *scene, const std::string &filename)
{
    // Initialize the meshes in the scene one by one
    for (unsigned int i = 0 ; i < scene->mNumMeshes ; i++)
    {
        const aiMesh* mesh = scene->mMeshes[i];
        initMesh(i, mesh);
    }
    for(auto &x : m_vertexPositions)
        m_vertexData.push_back(x);
    for(auto &x : m_vertexTexCoords)
        m_vertexData.push_back(x);
    for(auto &x : m_vertexNormals)
        m_vertexData.push_back(x);
    return initMaterials(scene, filename);
}

void ModelLoader::initMesh(unsigned int index, const aiMesh *mesh)
{
    const aiVector3D zero3D(0.0f, 0.0f, 0.0f);
    const aiVector3D one3D(1.0f, 1.0f, 1.0f);

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        const aiVector3D *pos = &(mesh->mVertices[i]);
        const aiVector3D *normal = mesh->HasNormals() ? &(mesh->mNormals[i]): &one3D;
        const aiVector3D *tex = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &zero3D;

        m_vertexPositions.push_back(pos->x);
        m_vertexPositions.push_back(pos->y);
        m_vertexPositions.push_back(pos->z);

        m_vertexTexCoords.push_back(tex->x);
        m_vertexTexCoords.push_back(tex->y);

        m_vertexNormals.push_back(normal->x);
        m_vertexNormals.push_back(normal->y);
        m_vertexNormals.push_back(normal->z);
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace &face = mesh->mFaces[i];
        m_renderMode = GL_TRIANGLES;
        m_vertexIndices.push_back(face.mIndices[0]);
        m_vertexIndices.push_back(face.mIndices[1]);
        m_vertexIndices.push_back(face.mIndices[2]);
    }
}

bool ModelLoader::initMaterials(const aiScene *scene, const std::string &filename)
{
    bool ret = true;

    for(unsigned int i = 0; i < scene->mNumMaterials; i++)
    {
        const aiMaterial *material = scene->mMaterials[i];

        aiString path;
        if(material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
            m_textureName = path.data;
        else
            m_textureName = "default.png";
    }

    return ret;
}

std::vector<float> ModelLoader::getVertexData() const
{
    return m_vertexData;
}

std::vector<short> ModelLoader::getVertexIndices() const
{
    return m_vertexIndices;
}

std::vector<float> ModelLoader::getNormals() const
{
    return m_vertexNormals;
}

std::size_t ModelLoader::getTexCoordsSize() const
{
    return m_vertexTexCoords.size() * sizeof(float);
}

std::size_t ModelLoader::getNormalSize() const
{
    return m_vertexNormals.size() * sizeof(float);
}

std::size_t ModelLoader::getVertexSize() const
{
    return m_vertexPositions.size() * sizeof(float);
}

std::size_t ModelLoader::getIndexSize() const
{
    return m_vertexIndices.size() * sizeof(std::size_t);
}

std::size_t ModelLoader::getVertexCount() const
{
    return m_vertexPositions.size();
}

GLsizei ModelLoader::getIndexCount()
{
    return m_vertexIndices.size();
}

GLenum ModelLoader::getRenderMode() const
{
    return m_renderMode;
}


std::string ModelLoader::getTextureName() const
{
    return m_textureName;
}
