#include "App.hpp"

#include <iostream>

#include "Core/InputManager.hpp"
#include "Core/WindowManager.hpp"
#include "Events/EventBus.hpp"
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

App::App()
{
    Core::WindowManager::Initialize(1280, 960, "OpenGL App");
    Core::InputManager::Initialize();
    _game = Game();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(Core::WindowManager::GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void App::Run()
{
    _game.Init();
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(Core::WindowManager::GetWindow()))
    {
        glfwSwapInterval(0);
        const auto startFrame = static_cast<float>(glfwGetTime());
        Core::InputManager::Update();

        if (Core::InputManager::KeyPressed(GLFW_KEY_ESCAPE))
        {
            _game.Stop();
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

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        _game.Update(_deltaTime);
        Events::EventBus::DispatchEvents();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(Core::WindowManager::GetWindow());
        glfwPollEvents();

        const auto endFrame = static_cast<float>(glfwGetTime());
        _deltaTime = endFrame - startFrame;

        const auto fps = static_cast<int>(1.0f / _deltaTime);
        Core::WindowManager::SetTitle(("OpenGL App - FPS: " + std::to_string(fps)).c_str());
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
