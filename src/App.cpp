#include "App.hpp"

#include <iostream>

#include "Core/InputManager.hpp"
#include "Core/Macros.hpp"
#include "Core/WindowManager.hpp"
#include "Events/Event.hpp"
#include "Events/EventBus.hpp"

App::App()
{
    Core::WindowManager::Initialize(1280, 960, "OpenGL App");
    Core::InputManager::Initialize();
    _game = Game();
}

void App::Run()
{
    _game.Init();
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(Core::WindowManager::GetWindow()))
    {
        glfwMakeContextCurrent(Core::WindowManager::GetWindow());
        glfwSwapInterval(0);
        const auto startFrame = static_cast<float>(glfwGetTime());
        Core::InputManager::Update();

        if (Core::InputManager::KeyPressed(GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(Core::WindowManager::GetWindow(), true);
        }

        if (Core::InputManager::KeyPressed(GLFW_KEY_F10))
        {
            Core::WindowManager::ToggleFullscreen();
        }

        if (Core::InputManager::KeyPressed(GLFW_KEY_F9))
        {
            Core::WindowManager::ToggleWindowed();
        }

        Core::WindowManager::ClearScreen();
        _game.Update(_deltaTime);
        Events::EventBus::DispatchEvents();

        glfwSwapBuffers(Core::WindowManager::GetWindow());
        glfwPollEvents();

        const auto endFrame = static_cast<float>(glfwGetTime());
        _deltaTime = endFrame - startFrame;
    }
}
