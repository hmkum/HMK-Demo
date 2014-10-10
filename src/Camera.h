#pragma once
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

namespace hmk {

    class Camera {
    public:
        Camera();

        const glm::vec3& GetPosition() const;
        void SetPosition(const glm::vec3 &_position);
        void OffsetPosition(const glm::vec3 &offset);

        float GetFov() const;
        void SetFov(float _fov);


        float GetNearPlane() const;
        float GetFarPlane() const;

        void SetNearAndFarPlanes(float _nearPlane, float _farPlane);

        glm::mat4 GetOrientation() const;

        void OffsetOrientation(float upAngle, float rightAngle);

        void LookAt(glm::vec3 _position);

        float GetViewportAspectRatio() const;
        void SetViewportAspectRatio(float _viewportAspectRatio);

        glm::vec3 GetForward() const;
        glm::vec3 GetRight() const;
        glm::vec3 GetUp() const;


        glm::mat4 GetMatrix() const;
        glm::mat4 GetProjection() const;
        glm::mat4 GetView() const;

    private:
        glm::vec3 position;
        float horizontalAngle;
        float verticalAngle;
        float fov;
        float nearPlane;
        float farPlane;
        float viewportAspectRatio;

        void NormalizeAngles();
    };

}
