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
        Camera(const glm::vec3 &position, const glm::vec3 &worldUp, float yaw, float pitch, float movementSpeed);
        ~Camera();
        void MoveForward(float deltaTime);
        void MoveBackward(float deltaTime);
        void MoveRight(float deltaTime);
        void MoveLeft(float deltaTime);
        void MoveUp(float deltaTime);
        void MoveDown(float deltaTime);
        void Rotate(float xoffset, float yoffset, bool constrainPitch = true);
        void UpdateCameraVectors();
        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetProjectionMatrix() const;
        glm::vec3 GetPosition() const;
        glm::vec3 GetFront() const;
        glm::vec3 GetUp() const;
        glm::vec3 GetRight() const;
        glm::vec3 GetWorldUp() const;
        float GetZoom() const;

    private:
        glm::vec3 _position{};
        glm::vec3 _front{};
        glm::vec3 _up{};
        glm::vec3 _right{};
        glm::vec3 _worldUp{};
        float _yaw{};
        float _pitch{};
        float _movementSpeed{};
        float _mouseSensitivity{};
        float _zoom{};
    };
}

#endif //CAMERA_HPP
