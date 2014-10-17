#include "Fog.h"

using namespace hmk;

Fog::Fog()
{
    m_color   = glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);
    m_start   = 0.01f;
    m_end     = 100.0f;
    m_density = 0.04f;
    m_equation = FogEquation::LINEAR;
}

Fog::Fog(glm::vec4 color, uint8 eq) :
    m_color(color), m_equation(eq)
{
    m_start   = 0.01f;
    m_end     = 100.0f;
    m_density = 0.04f;
}

Fog::Fog(uint8 eq) :
    m_equation(eq)
{
    m_color   = glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);
    m_start   = 0.01f;
    m_end     = 100.0f;
    m_density = 0.04f;
}

Fog::Fog(glm::vec4 color, float start, float end) :
    m_color(color), m_start(start), m_end(end)
{
    m_density = 0.04f;
    m_equation = FogEquation::LINEAR;
}

Fog::Fog(glm::vec4 color, float density, uint8 eq) :
    m_color(color), m_density(density), m_equation(eq)
{
    m_start   = 0.01f;
    m_end     = 100.0f;
}

Fog::~Fog()
{
}

void Fog::setColor(glm::vec4 color)
{
    m_color = color;
}

glm::vec4 Fog::getColor() const
{
    return m_color;
}

void Fog::setStart(float start)
{
    m_start = start;
}

float Fog::getStart() const
{
    return m_start;
}

void Fog::setEnd(float end)
{
    m_end = end;
}

float Fog::getEnd() const
{
    return m_end;
}

void Fog::setDensity(float density)
{
    m_density = density;
}

float Fog::getDensity() const
{
    return m_density;
}

void Fog::setEquation(uint8 equation)
{
    assert(equation >= 0 && equation <= 2);
    m_equation = equation;
}

uint8 Fog::getEquation() const
{
    return m_equation;
}
