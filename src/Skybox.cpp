#include "Skybox.h"
#include "GLHelper.h"
#include "ShaderManager.h"
#include "thirdparty/stb_image.h"

using namespace hmk;

const GLenum types[6] = {  GL_TEXTURE_CUBE_MAP_POSITIVE_X,
                           GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
                           GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
                           GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
                           GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
                           GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };

void Skybox::load()
{
    glGenTextures(1, &m_texID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texID);

    std::string filenames[] = {"textures/txStormydays_front.bmp", "textures/txStormydays_back.bmp",
                               "textures/txStormydays_up.bmp","textures/txStormydays_down.bmp",
                               "textures/txStormydays_right.bmp","textures/txStormydays_left.bmp"};

    for(uint8 i = 0; i < 6; i++)
    {
        int32 width, height, comp;
        unsigned char *data;
        std::string path = PATH + filenames[i];
        data = stbi_load(path.c_str(), &width, &height, &comp, 0);
        if(!data)
        {
            const char *err = stbi_failure_reason();
            std::cout << (ERROR + "Loading Texture: " + filenames[i] + "\n") << std::endl;
            std::cout << err << std::endl;
            return ;
        }

        GLint format;
        switch(comp)
        {
            case 3:
                format = GL_RGB;
                break;
            case 4:
                format = GL_RGBA;
                break;
            default:
                format = GL_RGBA;
        }
        glTexImage2D(types[i], 0, format,
                     (GLsizei)width, (GLsizei)height, 0, format, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    hmk::ShaderManager::getInstance()->use("sky");
    GLint texLoc = hmk::ShaderManager::getInstance()->getUniform("tex");
    glUniform1i(texLoc, 0);
    hmk::ShaderManager::getInstance()->use("");

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

    glGenVertexArrays (1, &m_vao);
    glBindVertexArray (m_vao);
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Skybox::render()
{
    glDepthMask (GL_FALSE);
    glCullFace(GL_FRONT);
    hmk::ShaderManager::getInstance()->use("sky");
    glActiveTexture (GL_TEXTURE0);
    glBindTexture (GL_TEXTURE_CUBE_MAP, m_texID);
    glBindVertexArray (m_vao);
    glDrawArrays (GL_TRIANGLES, 0, 36);
    glBindVertexArray (0);
    hmk::ShaderManager::getInstance()->use("");
    glCullFace(GL_BACK);
    glDepthMask (GL_TRUE);
}
