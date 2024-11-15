#include "PlayerController.hpp"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>

#include "Core/InputManager.hpp"
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
        else
        {
            camera.Translate(translation);
        }
    }


    // double xpos = Core::InputManager::GetMouseX();
    // double ypos = Core::InputManager::GetMouseY();
    //
    // static double lastX = xpos;
    // static double lastY = ypos;
    //
    // auto xoffset = static_cast<float>(xpos - lastX);
    // auto yoffset = static_cast<float>(lastY - ypos);
    //
    // lastX = xpos;
    // lastY = ypos;
    //
    // float sensitivity = 0.1f;
    // xoffset *= sensitivity;
    // yoffset *= sensitivity;
    //
    // // Apply yaw rotation to the transform
    // transform = glm::rotate(transform, glm::radians(xoffset), glm::vec3(0.0f, 1.0f, 0.0f));
}
