#pragma once

#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Core {
    class InputManager
    {
    public:
        static void Initialize();
        static void Update();
        static bool KeyPressed(int key);
        static bool MouseButtonPressed(int button);
        static double GetMouseX();
        static double GetMouseY();

        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);

    private:
        static double _mouseX, _mouseY;
        static bool _keys[GLFW_KEY_LAST + 1];
        static bool _mouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];
        static std::vector<int> _activeKeys;
    };
}

#endif //INPUTMANAGER_HPP
