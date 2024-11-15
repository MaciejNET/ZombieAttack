#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "WindowManager.hpp"

namespace Core {
    Camera::Camera()
    {
        UpdateCameraVectors();
    }

    Camera::Camera(const glm::vec3 &position, const glm::vec3 &worldUp, float yaw, float pitch, float movementSpeed)
        : _position(position), _worldUp(worldUp), _yaw(yaw), _pitch(pitch), _movementSpeed(movementSpeed)
    {
        UpdateCameraVectors();
    }

    Camera::~Camera() = default;

    void Camera::Translate(const glm::vec3 &translation)
    {
        _position += translation;
        UpdateCameraVectors();
    }

    void Camera::Rotate(const glm::vec3 &axis, float angle)
    {
        _yaw += angle * axis.x;
        _pitch += angle * axis.y;

        if (_pitch > 89.0f)
        {
            _pitch = 89.0f;
        }
        if (_pitch < -89.0f)
        {
            _pitch = -89.0f;
        }

        UpdateCameraVectors();
    }

    void Camera::LookAt(const glm::vec3 &target)
    {
        _front = glm::normalize(target - _position);
        _yaw = glm::degrees(atan2(_front.z, _front.x));
        _pitch = glm::degrees(asin(_front.y));
        UpdateCameraVectors();
    }


    void Camera::UpdateCameraVectors()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
        front.y = sin(glm::radians(_pitch));
        front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
        _front = glm::normalize(front);

        _right = glm::normalize(glm::cross(_front, _worldUp));
        _up = glm::normalize(glm::cross(_right, _front));
    }

    glm::mat4 Camera::GetViewMatrix() const
    {
        return glm::lookAt(_position, _position + _front, _up);
    }

    glm::mat4 Camera::GetProjectionMatrix() const
    {
        const auto height = WindowManager::GetHeight();
        const auto width = WindowManager::GetWidth();
        return glm::perspective(glm::radians(_zoom), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);
    }

    glm::vec3 Camera::GetPosition() const
    {
        return _position;
    }

    glm::vec3 Camera::GetFront() const
    {
        return _front;
    }

    glm::vec3 Camera::GetUp() const
    {
        return _up;
    }

    glm::vec3 Camera::GetRight() const
    {
        return _right;
    }

    glm::vec3 Camera::GetWorldUp() const
    {
        return _worldUp;
    }

    float Camera::GetZoom() const
    {
        return _zoom;
    }
}