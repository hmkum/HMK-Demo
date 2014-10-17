#include "DirectionalLight.h"
#include "ShaderManager.h"
using namespace hmk;

DirectionalLight::DirectionalLight()
{
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::setEnable(bool enable)
{
    m_enable = enable;
}

bool DirectionalLight::isEnable() const
{
    return m_enable;
}

void DirectionalLight::update()
{
    GLint lastProgram = hmk::ShaderManager::getInstance()->getActiveProgram();
    hmk::ShaderManager::getInstance()->use("basic");
    hmk::ShaderManager::getInstance()->setUniformf("light.position", glm::vec4(-glm::normalize(getOrientation()), 1.0f));
    hmk::ShaderManager::getInstance()->setUniformf("light.intensity", m_color);
    hmk::ShaderManager::getInstance()->use("");
    hmk::ShaderManager::getInstance()->use(lastProgram);
}

void DirectionalLight::setColor(glm::vec3 color)
{
    m_color = color;
}

void DirectionalLight::setOrientation(float verticalAngle, float horizontalAngle)
{
    m_verticalAngle = verticalAngle;
    m_horizontalAngle = horizontalAngle;
}

glm::vec3 DirectionalLight::getOrientation()
{
    return glm::vec3(15.0f, cos(glm::radians(m_verticalAngle)) * 70.0f, sin(glm::radians(m_horizontalAngle)) * 70.0f);
}
