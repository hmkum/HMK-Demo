#pragma once
#include "base.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
namespace hmk
{
enum FogEquation {LINEAR, EXP, EXP2};
class Fog
{
public:
    Fog();
    Fog(glm::vec4 color, uint8 eq);
    Fog(uint8 eq);
    Fog(glm::vec4 color, float start, float end); // Linear
    Fog(glm::vec4 color, float density, uint8 eq); // Exp or Exp2
    ~Fog();

    void setColor(glm::vec4 color);
    glm::vec4 getColor() const;

    void setStart(float);
    float getStart() const;

    void setEnd(float);
    float getEnd() const;

    void setDensity(float density);
    float getDensity() const;

    void setEquation(uint8 equation);
    uint8 getEquation() const;

    glm::vec4 m_color;
    float m_start; // This is only for linear fog
    float m_end; // This is only for linear fog
    float m_density; // This is for exp and exp2 fog
    uint8 m_equation;
};
}
