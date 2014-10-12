#pragma once
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

namespace hmk {

    class Camera {
    public:
        Camera();

        const glm::vec3& getPosition() const;
        void setPosition(const glm::vec3 &_position);
        void offsetPosition(const glm::vec3 &offset);

        float getFov() const;
        void setFov(float _fov);

        float getNearPlane() const;
        float getFarPlane() const;

        void setNearAndFarPlanes(float _nearPlane, float _farPlane);

        glm::mat4 getOrientation() const;

        void offsetOrientation(float upAngle, float rightAngle);

        void lookAt(glm::vec3 _position);

        float getViewportAspectRatio() const;
        void setViewportAspectRatio(float _viewportAspectRatio);

        glm::vec3 getForward() const;
        glm::vec3 getRight() const;
        glm::vec3 getUp() const;


        glm::mat4 getMatrix() const;
        glm::mat4 getProjection() const;
        glm::mat4 getView() const;

    private:
        glm::vec3 m_position;
        float m_horizontalAngle;
        float m_verticalAngle;
        float m_fov;
        float m_nearPlane;
        float m_farPlane;
        float m_viewportAspectRatio;

        void NormalizeAngles();
    };

}
