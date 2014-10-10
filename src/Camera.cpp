#include <cmath>
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace hmk;

static const float MaxVerticalAngle = 85.0f; //must be less than 90 to avoid gimbal lock

Camera::Camera() :
        position(0.0f, 0.0f, 1.0f),
        horizontalAngle(0.0f),
        verticalAngle(0.0f),
        fov(50.0f),
        nearPlane(0.01f),
        farPlane(100.0f),
        viewportAspectRatio(4.0f/3.0f)
{
}

const glm::vec3& Camera::GetPosition() const
{
    return position;
}

void Camera::SetPosition(const glm::vec3 &_position)
{
    position = _position;
}

void Camera::OffsetPosition(const glm::vec3 &offset)
{
    position += offset;
}

float Camera::GetFov() const
{
    return fov;
}

void Camera::SetFov(float _fov)
{
    assert(_fov > 0.0f && _fov < 180.0f);
    fov = _fov;
}

float Camera::GetNearPlane() const
{
    return nearPlane;
}

float Camera::GetFarPlane() const
{
    return farPlane;
}

void Camera::SetNearAndFarPlanes(float _nearPlane, float _farPlane)
{
    assert(_nearPlane > 0.0f);
    assert(_farPlane > _nearPlane);
    nearPlane = _nearPlane;
    farPlane = _farPlane;
}

glm::mat4 Camera::GetOrientation() const
{
    glm::mat4 orientation = glm::mat4(1.0f);
    orientation = glm::rotate(orientation, glm::radians(verticalAngle), glm::vec3(1,0,0));
    orientation = glm::rotate(orientation, glm::radians(horizontalAngle), glm::vec3(0,1,0));
    return orientation;
}

void Camera::OffsetOrientation(float upAngle, float rightAngle)
{
    horizontalAngle += rightAngle;
    verticalAngle += upAngle;
	NormalizeAngles();
}

void Camera::LookAt(glm::vec3 _position)
{
    assert(_position != position);
    auto direction = glm::normalize(position - _position);
    verticalAngle = asinf(direction.y);
    horizontalAngle = -atan2f(-direction.x, -direction.z);
	NormalizeAngles();
}

float Camera::GetViewportAspectRatio() const
{
    return viewportAspectRatio;
}

void Camera::SetViewportAspectRatio(float _viewportAspectRatio)
{
    assert(_viewportAspectRatio > 0.0);
    viewportAspectRatio = _viewportAspectRatio;
}

glm::vec3 Camera::GetForward() const
{
    auto forward = glm::inverse(GetOrientation()) * glm::vec4(0,0,-1,1);
    return glm::vec3(forward);
}

glm::vec3 Camera::GetRight() const
{
    auto right = glm::inverse(GetOrientation()) * glm::vec4(1,0,0,1);
    return glm::vec3(right);
}

glm::vec3 Camera::GetUp() const
{
    auto up = glm::inverse(GetOrientation()) * glm::vec4(0,1,0,1);
    return glm::vec3(up);
}

glm::mat4 Camera::GetMatrix() const
{
    return GetProjection() * GetView();
}

glm::mat4 Camera::GetProjection() const
{
    return glm::perspective(glm::radians(fov), viewportAspectRatio, nearPlane, farPlane);
}

glm::mat4 Camera::GetView() const
{
    return GetOrientation() * glm::translate(glm::mat4(), -position);
}

void Camera::NormalizeAngles()
{
    horizontalAngle = fmodf(horizontalAngle, 360.0f);
    //fmodf can return negative values, but this will make them all positive
    if(horizontalAngle < 0.0f)
        horizontalAngle += 360.0f;

    if(verticalAngle > MaxVerticalAngle)
        verticalAngle = MaxVerticalAngle;
    else if(verticalAngle < -MaxVerticalAngle)
        verticalAngle = -MaxVerticalAngle;
}