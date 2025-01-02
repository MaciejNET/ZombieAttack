#include "PlayerController.hpp"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>

#include "BulletController.hpp"
#include "Core/BaseShapes.hpp"
#include "Core/InputManager.hpp"
#include "Core/WindowManager.hpp"
#include "Scene/Components.hpp"

void PlayerController::OnCreate()
{
    _inventory = std::make_shared<Inventory>();
    auto& camera = GetComponent<Scene::CameraComponent>().Camera;
    auto position = glm::vec3(-10.0f, 10.0f, 10.0f);
    camera.Translate(position);

    auto& transform = GetComponent<Scene::TransformComponent>().Transform;

    const auto targetPosition = glm::vec3(transform[3]);
    camera.LookAt(targetPosition);
}

void PlayerController::OnUpdate(float deltaTime)
{
    _inventory->Update(deltaTime);
    auto& camera = GetComponent<Scene::CameraComponent>().Camera;
    auto& transform = GetComponent<Scene::TransformComponent>().Transform;
    auto& collision = GetComponent<Scene::CollisionComponent>();

    double mouseX = Core::InputManager::GetMouseX();
    double mouseY = Core::InputManager::GetMouseY();
    double viewportWidth = Core::WindowManager::GetWidth();
    double viewportHeight = Core::WindowManager::GetHeight();

    glm::vec2 mousePosRelativeToCenter(
        (mouseX - viewportWidth / 2.0) / (viewportWidth / 2.0),
        -(mouseY - viewportHeight / 2.0) / (viewportHeight / 2.0)
    );

    glm::vec3 cameraFront = camera.GetFront();
    float cameraYaw = atan2(cameraFront.z, cameraFront.x);

    float yaw = atan2(-mousePosRelativeToCenter.x, mousePosRelativeToCenter.y) + cameraYaw;

    glm::vec3 playerPosition(transform[3]);
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), yaw, glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::translate(glm::mat4(1.0f), playerPosition) * rotation;

    glm::vec3 translation(0.0f);

    const float playerSpeed = _speed * deltaTime;

    if (Core::InputManager::KeyPressed(GLFW_KEY_W))
    {
        translation.z -= playerSpeed;
    }
    if (Core::InputManager::KeyPressed(GLFW_KEY_S))
    {
        translation.z += playerSpeed;
    }
    if (Core::InputManager::KeyPressed(GLFW_KEY_A))
    {
        translation.x -= playerSpeed;
    }
    if (Core::InputManager::KeyPressed(GLFW_KEY_D))
    {
        translation.x += playerSpeed;
    }

    if (Core::InputManager::KeyPressed(GLFW_KEY_E))
    {
        if (!_itemChanged)
        {
            _inventory->SelectNextItem();
            _itemChanged = true;
        }
    }
    else
    {
        _itemChanged = false;
    }

    if (Core::InputManager::MouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
    {
        glm::vec4 mouseClipSpace(
                (2.0f * mouseX) / viewportWidth - 1.0f,
                1.0f - (2.0f * mouseY) / viewportHeight,
                -1.0f,
                1.0f
            );

        glm::mat4 invProjView = glm::inverse(camera.GetProjectionMatrix() * camera.GetViewMatrix());
        glm::vec4 mouseWorldSpace = invProjView * mouseClipSpace;
        mouseWorldSpace /= mouseWorldSpace.w;

        glm::vec3 direction = glm::normalize(glm::vec3(mouseWorldSpace) - playerPosition);
        direction.y = 0.0f;

        glm::mat4 additionalRotation = glm::rotate(glm::mat4(1.0f), glm::radians(225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        direction = glm::vec3(additionalRotation * glm::vec4(direction, 0.0f));
        PlayerCoordinates playerCoordinates{transform, direction};
        Scene::Scene* scene = _entity.GetScene();
        _inventory->UseSelectedItem(playerCoordinates, *scene, deltaTime);
    }

    if (translation != glm::vec3(0.0f))
    {
        auto oldTranslation = translation;
        transform = glm::translate(transform, translation);
        if (collision.CollisionDetection(_entity).GetId() != -1)
        {
            transform = glm::translate(transform, -oldTranslation);
        }
    }

    constexpr glm::vec3 cameraOffset(-10.0f, 10.0f, 10.0f);
    glm::vec3 cameraPosition = playerPosition + cameraOffset;
    camera.SetPosition(cameraPosition);
    camera.LookAt(playerPosition);
}

