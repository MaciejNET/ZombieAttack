#pragma once

#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/vec3.hpp>

namespace Core {
    class Camera
    {
    public:
        Camera();
        Camera(const glm::vec3 &position, const glm::vec3 &worldUp, float yaw, float pitch, float movementSpeed);
        ~Camera();
        void Translate(const glm::vec3 &translation);
        void Rotate(const glm::vec3 &axis, float angle);
        void UpdateCameraVectors();
        void LookAt(const glm::vec3 &target);
        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetProjectionMatrix() const;
        glm::vec3 GetPosition() const;
        glm::vec3 GetFront() const;
        glm::vec3 GetUp() const;
        glm::vec3 GetRight() const;
        glm::vec3 GetWorldUp() const;
        float GetZoom() const;

    private:
        glm::vec3 _position{0.0f, 0.0f, 0.0f};
        glm::vec3 _front{0.0f, 0.0f, -1.0f};
        glm::vec3 _up{0.0f, 1.0f, 0.0f};
        glm::vec3 _right{1.0f, 0.0f, 0.0f};
        glm::vec3 _worldUp{0.0f, 1.0f, 0.0f};
        float _yaw{-90.0f};
        float _pitch{0.0f};
        float _movementSpeed{2.5f};
        float _mouseSensitivity{0.1f};
        float _zoom{45.0f};
    };
}

#endif //CAMERA_HPP