#pragma once
#define GLM_FORCE_RADIANS
#include <thirdparty/glm/glm.hpp>
#include <thirdparty/glm/ext.hpp>

namespace hmk
{
class DirectionalLight
{
public:
    DirectionalLight();
    ~DirectionalLight();

    void enable();
    void disable();
    bool isEnable() const;

    void update();

    void setColor(glm::vec3 color);
    void setOrientation(float verticalAngle, float horizontalAngle);
    glm::vec3 getOrientation();
private:
    glm::vec3 m_color;
    float m_verticalAngle, m_horizontalAngle;
    bool m_enable;
};
}
