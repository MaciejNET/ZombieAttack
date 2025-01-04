#include "Game.hpp"

#include <glm/ext/matrix_transform.hpp>

#include "Components/PlayerController.hpp"
#include "Components/WaveController.hpp"
#include "Components/ZombieController.hpp"
#include "Core/BaseShapes.hpp"
#include "Core/BaseShapes.hpp"
#include "Core/BaseShapes.hpp"
#include "Core/BaseShapes.hpp"
#include "Core/BaseShapes.hpp"
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
    floor.AddComponent<Scene::SpriteRendererComponent>(glm::vec4(0.93f, 0.51f, 0.93f, 1.0f));
    auto floorShape = Core::BaseShapes::Cube();
    auto floorMesh = std::make_shared<Core::Mesh>(floorShape.Vertices, floorShape.Indices);
    auto floorShader = std::make_shared<Core::Shader>("../src/Core/BaseShader.vert", "../src/Core/BaseShader.frag");
    floor.AddComponent<Scene::MeshComponent>(floorMesh, floorShader);
}

void Game::Update(float deltaTime)
{
    _scene.OnUpdate(deltaTime);
}