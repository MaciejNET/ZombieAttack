#include "CameraController.hpp"

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>

#include "Core/InputManager.hpp"

void CameraController::OnUpdate(float deltaTime)
{
    auto& camera = GetComponent<Scene::CameraComponent>().Camera;

    glm::vec3 translation(0.0f);
    glm::vec3 rotation(0.0f);

    float cameraSpeed = 2.5f;

    if (Core::InputManager::KeyHeld(GLFW_KEY_W))
    {
        translation.z += cameraSpeed;
    }
    if (Core::InputManager::KeyHeld(GLFW_KEY_S))
    {
        translation.z -= cameraSpeed;
    }
    if (Core::InputManager::KeyHeld(GLFW_KEY_A))
    {
        translation.x -= cameraSpeed;
    }
    if (Core::InputManager::KeyHeld(GLFW_KEY_D))
    {
        translation.x += cameraSpeed;
    }
    if (Core::InputManager::KeyHeld(GLFW_KEY_SPACE))
    {
        translation.y += cameraSpeed;
    }
    if (Core::InputManager::KeyHeld(GLFW_KEY_LEFT_SHIFT))
    {
        translation.y -= cameraSpeed;
    }

    double xpos = Core::InputManager::GetMouseX();
    double ypos = Core::InputManager::GetMouseY();

    static double lastX = xpos;
    static double lastY = ypos;

    auto xoffset = static_cast<float>(xpos - lastX);
    auto yoffset = static_cast<float>(lastY - ypos);

    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.5f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    rotation.x = yoffset;
    rotation.y = xoffset;

    camera.Transform(translation, rotation, deltaTime);
}
