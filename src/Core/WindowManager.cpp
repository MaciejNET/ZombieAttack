#include "WindowManager.hpp"
#include "InputManager.hpp"

#include <iostream>

namespace Core {
    std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> WindowManager::_window {nullptr, glfwDestroyWindow};
    std::vector<Resolution> WindowManager::resolutions;
    int WindowManager::currentResolutionIndex;
    bool WindowManager::_isFullscreen;
    float WindowManager::_clearColor[4];

    void WindowManager::Initialize(int width, int height, const char* title)
    {
        resolutions = { {1024, 768}, {1280, 960}, {1920, 1080} };
        currentResolutionIndex = 0;
        std::fill_n(_clearColor, 4, 0.0f);

        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW\n";
            exit(EXIT_FAILURE);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window)
        {
            glfwTerminate();
            std::cerr << "Failed to create GLFW window\n";
            exit(EXIT_FAILURE);
        }
        _window.reset(window);

        glfwMakeContextCurrent(_window.get());
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD\n";
            exit(EXIT_FAILURE);
        }

        glfwSetFramebufferSizeCallback(_window.get(), FramebufferSizeCallback);
        glfwSetCursorPosCallback(_window.get(), CursorPositionCallback);
        glEnable(GL_DEPTH_TEST);
    }

    GLFWwindow* WindowManager::GetWindow()
    {
        return _window.get();
    }

    void WindowManager::UpdateViewport(int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void WindowManager::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
        auto* manager = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
        if (manager)
        {
            WindowManager::UpdateViewport(width, height);
        }
    }

    void WindowManager::Cleanup()
    {
        glfwTerminate();
    }

    int WindowManager::GetWidth()
    {
        int width, height;
        glfwGetWindowSize(_window.get(), &width, &height);
        return width;
    }

    int WindowManager::GetHeight()
    {
        int width, height;
        glfwGetWindowSize(_window.get(), &width, &height);
        return height;
    }

    void WindowManager::SetResolution(int width, int height)
    {
        if (_window)
        {
            glfwSetWindowSize(_window.get(), width, height);
        }
    }

    void WindowManager::SetTitle(const char* title)
    {
        if (_window)
        {
            glfwSetWindowTitle(_window.get(), title);
        }
    }

    void WindowManager::ToggleFullscreen()
    {
        _isFullscreen = !_isFullscreen;
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        if (_isFullscreen)
        {
            glfwSetWindowMonitor(_window.get(), monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
            UpdateViewport(mode->width, mode->height);
        }
        else
        {
            auto res = resolutions[currentResolutionIndex];
            int xpos = (mode->width - res.width) / 2;
            int ypos = (mode->height - res.height) / 2;

            glfwSetWindowMonitor(_window.get(), nullptr, xpos, ypos, res.width, res.height, mode->refreshRate);
            UpdateViewport(res.width, res.height);
        }
    }

    void WindowManager::ToggleWindowed()
    {
        if (!_isFullscreen) return;
        _isFullscreen = false;
        auto res = resolutions[currentResolutionIndex];
        glfwSetWindowMonitor(_window.get(), nullptr, 100, 100, res.width, res.height, GLFW_DONT_CARE);
    }

    void WindowManager::ClearScreen()
    {
        glClearColor(_clearColor[0], _clearColor[1], _clearColor[2], _clearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void WindowManager::SetClearColor(float r, float g, float b, float a)
    {
        _clearColor[0] = r;
        _clearColor[1] = g;
        _clearColor[2] = b;
        _clearColor[3] = a;
    }

    void WindowManager::TurnOnCursor()
    {
        glfwSetInputMode(_window.get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void WindowManager::TurnOffCursor()
    {
        glfwSetInputMode(_window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void WindowManager::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
    {
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        if (xpos < 0) xpos = 0;
        if (xpos > width) xpos = width;
        if (ypos < 0) ypos = 0;
        if (ypos > height) ypos = height;

        glfwSetCursorPos(window, xpos, ypos);
        InputManager::CursorPosCallback(window, xpos, ypos);
    }

    void WindowManager::CloseWindow()
    {
        glfwSetWindowShouldClose(_window.get(), true);
    }

}
