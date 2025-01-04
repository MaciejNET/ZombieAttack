#include "Game.hpp"

#include <imgui.h>
#include <glm/ext/matrix_transform.hpp>

#include "Components/PlayerController.hpp"
#include "Components/WaveController.hpp"
#include "Components/ZombieController.hpp"
#include "Core/BaseShapes.hpp"
#include "Core/BaseShapes.hpp"
#include "Core/BaseShapes.hpp"
#include "Core/BaseShapes.hpp"
#include "Core/BaseShapes.hpp"
#include "Core/WindowManager.hpp"
#include "GameObjects/EntityFactory.hpp"
#include "Scene/Components.hpp"

Game::Game()
{
    _scene = Scene::Scene();
}

void Game::Init()
{
    auto light = _scene.AddEntity();
    light.AddComponent<Scene::LightComponent>(glm::vec4(1.0f), glm::vec3(-5.0f, 100.0f, 75.0f), 1.0f);

    EntityFactory::CreatePlayer(_scene, glm::mat4(0.0f));

    auto waveController = _scene.AddEntity();
    waveController.AddComponent<Scene::WaveComponent>();
    waveController.AddComponent<Scene::ScriptableComponent>().Bind<WaveController>();

    auto floor = _scene.AddEntity();
    auto& transform = floor.AddComponent<Scene::TransformComponent>(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.6f, -5.0f)));
    transform.Transform = glm::scale(transform.Transform, glm::vec3(500.0f, 0.1f, 500.0f));
    floor.AddComponent<Scene::SpriteRendererComponent>(glm::vec4(0.8f, 0.6f, 0.4f, 1.0f));
    auto floorShape = Core::BaseShapes::Cube();
    auto floorMesh = std::make_shared<Core::Mesh>(floorShape.Vertices, floorShape.Indices);
    auto floorShader = std::make_shared<Core::Shader>("../src/Game/Shaders/GroundShader.vert", "../src/Game/Shaders/GroundShader.frag");
    floor.AddComponent<Scene::MeshComponent>(floorMesh, floorShader);
}

void Game::Update(float deltaTime)
{
    if (_isStopped)
    {
        DrawMenu();
    }
    else
    {
        _scene.OnUpdate(deltaTime);
    }
}

void Game::DrawMenu()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

    ImVec2 windowSize = ImGui::GetWindowSize();
    ImVec2 textSize = ImGui::CalcTextSize("Zombie Attack");
    ImVec2 buttonSize = ImVec2(200, 50);

    ImVec2 textPos = ImVec2((windowSize.x - textSize.x) * 0.5f, (windowSize.y - textSize.y) * 0.4f);
    ImVec2 startButtonPos = ImVec2((windowSize.x - buttonSize.x) * 0.5f, (windowSize.y - buttonSize.y) * 0.5f);
    ImVec2 exitButtonPos = ImVec2((windowSize.x - buttonSize.x) * 0.5f, (windowSize.y - buttonSize.y) * 0.6f);

    ImGui::SetCursorPos(textPos);
    ImGui::Text("Zombie Attack");

    ImGui::SetCursorPos(startButtonPos);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 20));
    if (ImGui::Button("Start", buttonSize))
    {
        Start();
    }
    ImGui::PopStyleVar();

    ImGui::SetCursorPos(exitButtonPos);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 20));
    if (ImGui::Button("Exit", buttonSize))
    {
        Core::WindowManager::CloseWindow();
    }
    ImGui::PopStyleVar();

    ImGui::End();
}