#include "PlayerController.hpp"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>

#include "Core/InputManager.hpp"
#include "Core/WindowManager.hpp"
#include "Scene/Components.hpp"

void PlayerController::OnCreate()
{
    auto& camera = GetComponent<Scene::CameraComponent>().Camera;
    auto position = glm::vec3(-10.0f, 10.0f, 10.0f); // Adjusted position
    camera.Translate(position);

    auto& transform = GetComponent<Scene::TransformComponent>().Transform;

    const auto targetPosition = glm::vec3(transform[3]);
    camera.LookAt(targetPosition);
}

void PlayerController::OnUpdate(float deltaTime)
{
    auto& camera = GetComponent<Scene::CameraComponent>().Camera;
    auto& transform = GetComponent<Scene::TransformComponent>().Transform;
    auto& collision = GetComponent<Scene::CollisionComponent>();

    double mouseX = Core::InputManager::GetMouseX();
    double mouseY = Core::InputManager::GetMouseY();
    double viewportWidth = Core::WindowManager::GetWidth();
    double viewportHeight = Core::WindowManager::GetHeight();

    // Calculate mouse position relative to the center of the screen
    glm::vec2 mousePosRelativeToCenter(
        (mouseX - viewportWidth / 2.0) / (viewportWidth / 2.0),
        -(mouseY - viewportHeight / 2.0) / (viewportHeight / 2.0) // Invert Y-axis
    );

    // Calculate yaw angle (rotation around the Y-axis) using atan2
    float yaw = atan2(-mousePosRelativeToCenter.x, mousePosRelativeToCenter.y);

    // Update the character's rotation
    glm::vec3 playerPosition(transform[3]); // Extract current player position
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), yaw, glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::translate(glm::mat4(1.0f), playerPosition) * rotation;

    glm::vec3 translation(0.0f);

    const float playerSpeed = _speed * deltaTime;

    if (Core::InputManager::KeyHeld(GLFW_KEY_W))
    {
        translation.z -= playerSpeed;
    }
    if (Core::InputManager::KeyHeld(GLFW_KEY_S))
    {
        translation.z += playerSpeed;
    }
    if (Core::InputManager::KeyHeld(GLFW_KEY_A))
    {
        translation.x -= playerSpeed;
    }
    if (Core::InputManager::KeyHeld(GLFW_KEY_D))
    {
        translation.x += playerSpeed;
    }

    if (translation != glm::vec3(0.0f))
    {
        auto oldTranslation = translation;
        transform = glm::translate(transform, translation);
        if (collision.CollisionDetection(_entity))
        {
            transform = glm::translate(transform, -oldTranslation);
        }
    }

    const glm::vec3 cameraOffset(-10.0f, 10.0f, 10.0f);
    glm::vec3 cameraPosition = playerPosition + cameraOffset;
    camera.SetPosition(cameraPosition);
    camera.LookAt(playerPosition);
}
