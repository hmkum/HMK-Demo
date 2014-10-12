#include <cmath>
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace hmk;

static const float MaxVerticalAngle = 85.0f; //must be less than 90 to avoid gimbal lock

Camera::Camera() :
		m_position(0.0f, 0.0f, 1.0f),
		m_horizontalAngle(0.0f),
		m_verticalAngle(0.0f),
		m_fov(50.0f),
		m_nearPlane(0.01f),
		m_farPlane(100.0f),
		m_viewportAspectRatio(4.0f/3.0f)
{
}

const glm::vec3& Camera::getPosition() const
{
    return m_position;
}

void Camera::setPosition(const glm::vec3 &_position)
{
	m_position = _position;
}

void Camera::offsetPosition(const glm::vec3 &offset)
{
	m_position += offset;
}

float Camera::getFov() const
{
    return m_fov;
}

void Camera::setFov(float _fov)
{
    assert(_fov > 0.0f && _fov < 180.0f);
	m_fov = _fov;
}

float Camera::getNearPlane() const
{
    return m_nearPlane;
}

float Camera::getFarPlane() const
{
    return m_farPlane;
}

void Camera::setNearAndFarPlanes(float _nearPlane, float _farPlane)
{
    assert(_nearPlane > 0.0f);
    assert(_farPlane > _nearPlane);
	m_nearPlane = _nearPlane;
	m_farPlane = _farPlane;
}

glm::mat4 Camera::getOrientation() const
{
    glm::mat4 orientation = glm::mat4(1.0f);
    orientation = glm::rotate(orientation, glm::radians(m_verticalAngle), glm::vec3(1,0,0));
    orientation = glm::rotate(orientation, glm::radians(m_horizontalAngle), glm::vec3(0,1,0));
    return orientation;
}

void Camera::offsetOrientation(float upAngle, float rightAngle)
{
	m_horizontalAngle += rightAngle;
	m_verticalAngle += upAngle;
	NormalizeAngles();
}

void Camera::lookAt(glm::vec3 _position)
{
    assert(_position != m_position);
    auto direction = glm::normalize(m_position - _position);
	m_verticalAngle = asinf(direction.y);
	m_horizontalAngle = -atan2f(-direction.x, -direction.z);
	NormalizeAngles();
}

float Camera::getViewportAspectRatio() const
{
    return m_viewportAspectRatio;
}

void Camera::setViewportAspectRatio(float _viewportAspectRatio)
{
    assert(_viewportAspectRatio > 0.0);
	m_viewportAspectRatio = _viewportAspectRatio;
}

glm::vec3 Camera::getForward() const
{
    auto forward = glm::inverse(getOrientation()) * glm::vec4(0,0,-1,1);
    return glm::vec3(forward);
}

glm::vec3 Camera::getRight() const
{
    auto right = glm::inverse(getOrientation()) * glm::vec4(1,0,0,1);
    return glm::vec3(right);
}

glm::vec3 Camera::getUp() const
{
    auto up = glm::inverse(getOrientation()) * glm::vec4(0,1,0,1);
    return glm::vec3(up);
}

glm::mat4 Camera::getMatrix() const
{
    return getProjection() * getView();
}

glm::mat4 Camera::getProjection() const
{
    return glm::perspective(glm::radians(m_fov), m_viewportAspectRatio, m_nearPlane, m_farPlane);
}

glm::mat4 Camera::getView() const
{
    return getOrientation() * glm::translate(glm::mat4(), -m_position);
}

void Camera::NormalizeAngles()
{
	m_horizontalAngle = fmodf(m_horizontalAngle, 360.0f);
    //fmodf can return negative values, but this will make them all positive
    if(m_horizontalAngle < 0.0f)
	    m_horizontalAngle += 360.0f;

    if(m_verticalAngle > MaxVerticalAngle)
	    m_verticalAngle = MaxVerticalAngle;
    else if(m_verticalAngle < -MaxVerticalAngle)
	    m_verticalAngle = -MaxVerticalAngle;
}