#include "InputManager.hpp"

#include <GLFW/glfw3.h>
#include <algorithm>
#include <vector>

#include "WindowManager.hpp"
#include "Events/EventBus.hpp"
#include "Events/KeyHeldEvent.hpp"
#include "Events/KeyPressedEvent.hpp"
#include "Events/KeyReleasedEvent.hpp"
#include "Events/MouseMovedEvent.hpp"
#include "Events/MouseButtonPressedEvent.hpp"

namespace Core {
    double InputManager::_mouseX;
    double InputManager::_mouseY;
    bool InputManager::_keys[GLFW_KEY_LAST + 1];
    bool InputManager::_mouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];
    std::vector<int> InputManager::_activeKeys;

    void InputManager::Initialize()
    {
        _mouseX = 0.0;
        _mouseY = 0.0;
        std::fill(std::begin(_keys), std::end(_keys), false);
        std::fill(std::begin(_mouseButtons), std::end(_mouseButtons), false);
        _activeKeys.clear();

        GLFWwindow* window = WindowManager::GetWindow();
        glfwSetKeyCallback(window, KeyCallback);
        glfwSetMouseButtonCallback(window, MouseButtonCallback);
        // Cursor position callback set in WindowManager
    }

    bool InputManager::KeyPressed(int key)
    {
        if (key < 0 || key > GLFW_KEY_LAST) return false;
        return _keys[key];
    }

    bool InputManager::MouseButtonPressed(int button)
    {
        if (button < 0 || button > GLFW_MOUSE_BUTTON_LAST) return false;
        return _mouseButtons[button];
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
        for (int key : _activeKeys)
        {
            std::shared_ptr<Events::Event> event = std::make_shared<Events::KeyHeldEvent>(key);
            Events::EventBus::Publish(event);
        }
    }

    void InputManager::KeyCallback(GLFWwindow*, int key, int, int action, int)
    {
        if (key < 0 || key > GLFW_KEY_LAST) return;
        if (action == GLFW_PRESS)
        {
            if (!_keys[key])
            {
                _keys[key] = true;
                _activeKeys.push_back(key);
                std::shared_ptr<Events::Event> e = std::make_shared<Events::KeyPressedEvent>(key);
                Events::EventBus::Publish(e);
            }
        }
        else if (action == GLFW_RELEASE)
        {
            if (_keys[key])
            {
                _keys[key] = false;
                _activeKeys.erase(std::remove(_activeKeys.begin(), _activeKeys.end(), key), _activeKeys.end());
                std::shared_ptr<Events::Event> e = std::make_shared<Events::KeyReleasedEvent>(key);
                Events::EventBus::Publish(e);
            }
        }
    }

    void InputManager::MouseButtonCallback(GLFWwindow*, int button, int action, int)
    {
        if (button < 0 || button > GLFW_MOUSE_BUTTON_LAST) return;
        if (action == GLFW_PRESS)
        {
            _mouseButtons[button] = true;
            std::shared_ptr<Events::Event> e = std::make_shared<Events::MouseButtonPressedEvent>(button);
            Events::EventBus::Publish(e);
        }
        else if (action == GLFW_RELEASE)
        {
            _mouseButtons[button] = false;
        }
    }

    void InputManager::CursorPosCallback(GLFWwindow*, double xpos, double ypos)
    {
        _mouseX = xpos;
        _mouseY = ypos;
        std::shared_ptr<Events::Event> e = std::make_shared<Events::MouseMovedEvent>(_mouseX, _mouseY);
        Events::EventBus::Publish(e);
    }
}
