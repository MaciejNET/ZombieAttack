#include "Game.hpp"

#include <glm/ext/matrix_transform.hpp>

#include "Components/PlayerController.hpp"
#include "Components/ZombieController.hpp"
#include "Core/BaseShapes.hpp"
#include "Scene/Components.hpp"

Game::Game()
{
    _scene = Scene::Scene();
}

void Game::Init()
{
    // Create entities
    auto light = _scene.AddEntity();
    light.AddComponent<Scene::LightComponent>(glm::vec4(1.0f), glm::vec3(0.0f, 10.0f, -5.0f), 1.0f);

    auto player = _scene.AddEntity();
    player.AddComponent<Scene::TransformComponent>(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f)));
    player.AddComponent<Scene::SpriteRendererComponent>(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    player.AddComponent<Scene::CameraComponent>(Core::Camera());
    auto cubeShape = Core::BaseShapes::Cube();
    auto mesh = std::make_shared<Core::Mesh>(cubeShape.Vertices, cubeShape.Indices);
    auto model = std::make_shared<Core::Model>("../assets/player.gltf");
    auto shader = std::make_shared<Core::Shader>("../src/Core/BaseShader.vert", "../src/Core/BaseShader.frag");
    player.AddComponent<Scene::MeshComponent>(mesh, shader);
    //player.AddComponent<Scene::ModelComponent>(model, shader);
    player.AddComponent<Scene::ScriptableComponent>().Bind<PlayerController>();
    player.AddComponent<Scene::CollisionComponent>();
    player.AddComponent<Scene::HealthComponent>();
    player.AddComponent<Scene::PlayerComponent>();

    auto zombie1 = _scene.AddEntity();
    zombie1.AddComponent<Scene::ScriptableComponent>().Bind<ZombieController>();
    zombie1.AddComponent<Scene::DamageComponent>();
    zombie1.AddComponent<Scene::HealthComponent>();
    zombie1.AddComponent<Scene::ZombieComponent>();
    zombie1.AddComponent<Scene::DamageComponent>();
    zombie1.AddComponent<Scene::TransformComponent>(glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, 0.0f, -5.0f)));
    zombie1.AddComponent<Scene::SpriteRendererComponent>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    auto cubeShape1 = Core::BaseShapes::Cube();
    auto mesh1 = std::make_shared<Core::Mesh>(cubeShape1.Vertices, cubeShape1.Indices);
    auto shader1 = std::make_shared<Core::Shader>("../src/Core/BaseShader.vert", "../src/Core/BaseShader.frag");
    zombie1.AddComponent<Scene::MeshComponent>(mesh1, shader1);
    zombie1.AddComponent<Scene::CollisionComponent>();

    auto zombie2 = _scene.AddEntity();
    zombie2.AddComponent<Scene::ScriptableComponent>().Bind<ZombieController>();
    zombie2.AddComponent<Scene::DamageComponent>();
    zombie2.AddComponent<Scene::ZombieComponent>();
    zombie2.AddComponent<Scene::HealthComponent>();
    zombie2.AddComponent<Scene::DamageComponent>();
    zombie2.AddComponent<Scene::TransformComponent>(glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 0.0f, -5.0f)));
    zombie2.AddComponent<Scene::SpriteRendererComponent>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    auto cubeShape2 = Core::BaseShapes::Cube();
    auto mesh2 = std::make_shared<Core::Mesh>(cubeShape2.Vertices, cubeShape2.Indices);
    auto shader2 = std::make_shared<Core::Shader>("../src/Core/BaseShader.vert", "../src/Core/BaseShader.frag");
    zombie2.AddComponent<Scene::MeshComponent>(mesh2, shader2);
    zombie2.AddComponent<Scene::CollisionComponent>();

    auto floor = _scene.AddEntity();
    auto& transform = floor.AddComponent<Scene::TransformComponent>(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.6f, -5.0f)));
    transform.Transform = glm::scale(transform.Transform, glm::vec3(50.0f, 0.1f, 50.0f));
    floor.AddComponent<Scene::SpriteRendererComponent>(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    auto floorShape = Core::BaseShapes::Cube();
    auto floorMesh = std::make_shared<Core::Mesh>(floorShape.Vertices, floorShape.Indices);
    auto floorShader = std::make_shared<Core::Shader>("../src/Core/BaseShader.vert", "../src/Core/BaseShader.frag");
    floor.AddComponent<Scene::MeshComponent>(floorMesh, floorShader);
}

void Game::Update(float deltaTime)
{
    _scene.OnUpdate(deltaTime);
}