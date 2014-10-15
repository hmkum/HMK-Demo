#pragma once
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace hmk
{
class DirectionalLight
{
public:
    DirectionalLight();
    ~DirectionalLight();

    void render();

    void setColor(glm::vec3 color);
    void setOrientation(float verticalAngle, float horizontalAngle);
    glm::vec3 getOrientation();
private:
    glm::vec3 m_color;
    float m_verticalAngle, m_horizontalAngle;
};
}