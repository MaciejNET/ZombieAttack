#pragma once

#ifndef WINDOWMANAGER_HPP
#define WINDOWMANAGER_HPP
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

namespace Core {
    struct Resolution
    {
        int width;
        int height;
    };

    class WindowManager
    {
    public:
        static void Initialize(int width = 1024, int height = 768, const char* title = "Window");
        static void Cleanup();
        static GLFWwindow* GetWindow();
        static int GetWidth();
        static int GetHeight();
        static void SetResolution(int width, int height);
        static void SetTitle(const char* title);
        static void ToggleFullscreen();
        static void ToggleWindowed();
        static void ClearScreen();
        static void SetClearColor(float r, float g, float b, float a);
        static void TurnOnCursor();
        static void TurnOffCursor();
        static void CloseWindow();

    private:
        static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
        static void UpdateViewport(int width, int height);
        static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
        static std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> _window;
        static std::vector<Resolution> resolutions;
        static int currentResolutionIndex;
        static bool _isFullscreen;
        static float _clearColor[4];
    };
}

#endif //WINDOWMANAGER_HPP
