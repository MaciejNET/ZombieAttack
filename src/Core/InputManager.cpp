#include "InputManager.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "WindowManager.hpp"
#include "Events/EventBus.hpp"
#include "Events/KeyHeldEvent.hpp"
#include "Events/KeyPressedEvent.hpp"
#include "Events/KeyReleasedEvent.hpp"
#include "Events/MouseMovedEvent.hpp"

namespace Core {
    double InputManager::_mouseX;
    double InputManager::_mouseY;

    void InputManager::Initialize()
    {
        _mouseX = 0.0;
        _mouseY = 0.0;
    }

    bool InputManager::KeyPressed(int key)
    {
        return glfwGetKey(WindowManager::GetWindow(), key) == GLFW_PRESS;
    }

    bool InputManager::MouseButtonPressed(int button)
    {
        return glfwGetMouseButton(WindowManager::GetWindow(), button) == GLFW_PRESS;
    }

    double InputManager::GetMouseX()
    {
        return _mouseX;
    }

    double InputManager::GetMouseY()
    {
        return _mouseY;
    }

    void InputManager::Update()
    {
        const auto window = WindowManager::GetWindow();
        for (int i = 0; i < 512; i++)
        {
            if (KeyPressed(i))
            {
                std::shared_ptr<Events::Event> event = std::make_shared<Events::KeyPressedEvent>(i);
                Events::EventBus::Publish(event);
            }
        }

        double x, y;
        glfwGetCursorPos(window, &x, &y);
        _mouseX = x;
        _mouseY = y;

        const std::shared_ptr<Events::Event> event = std::make_shared<Events::MouseMovedEvent>(_mouseX, _mouseY);
        Events::EventBus::Publish(event);
    }
}
