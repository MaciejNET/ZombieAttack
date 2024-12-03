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
    auto light = new ECS::Entity(&_scene);
    light->AddComponent<Scene::LightComponent>(glm::vec4(1.0f), glm::vec3(0.0f, 10.0f, -5.0f), 1.0f);
    _scene.AddEntity(light);

    auto player = new ECS::Entity(&_scene);
    player->AddComponent<Scene::TransformComponent>(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f)));
    player->AddComponent<Scene::SpriteRendererComponent>(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    player->AddComponent<Scene::CameraComponent>(Core::Camera());
    auto cubeShape = Core::BaseShapes::Cube();
    auto mesh = new Core::Mesh(cubeShape.Vertices, cubeShape.Indices);
    auto shader = new Core::Shader("../src/Core/BaseShader.vert", "../src/Core/BaseShader.frag");
    player->AddComponent<Scene::MeshComponent>(*mesh, *shader);
    player->AddComponent<Scene::ScriptableComponent>().Bind<PlayerController>();
    player->AddComponent<Scene::CollisionComponent>();
    player->AddComponent<Scene::HealthComponent>();
    player->AddComponent<Scene::PlayerComponent>();
    _scene.AddEntity(player);

    auto zombie1 = new ECS::Entity(&_scene);
    zombie1->AddComponent<Scene::ScriptableComponent>().Bind<ZombieController>();
    zombie1->AddComponent<Scene::DamageComponent>();
    zombie1->AddComponent<Scene::HealthComponent>();
    zombie1->AddComponent<Scene::ZombieComponent>();
    zombie1->AddComponent<Scene::DamageComponent>();
    zombie1->AddComponent<Scene::TransformComponent>(glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, 0.0f, -5.0f)));
    zombie1->AddComponent<Scene::SpriteRendererComponent>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    auto cubeShape1 = Core::BaseShapes::Cube();
    auto mesh1 = new Core::Mesh(cubeShape1.Vertices, cubeShape1.Indices);
    auto shader1 = new Core::Shader("../src/Core/BaseShader.vert", "../src/Core/BaseShader.frag");
    zombie1->AddComponent<Scene::MeshComponent>(*mesh1, *shader1);
    zombie1->AddComponent<Scene::CollisionComponent>();
    _scene.AddEntity(zombie1);

    auto zombie2 = new ECS::Entity(&_scene);
    zombie2->AddComponent<Scene::ScriptableComponent>().Bind<ZombieController>();
    zombie2->AddComponent<Scene::DamageComponent>();
    zombie2->AddComponent<Scene::ZombieComponent>();
    zombie2->AddComponent<Scene::HealthComponent>();
    zombie2->AddComponent<Scene::DamageComponent>();
    zombie2->AddComponent<Scene::TransformComponent>(glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 0.0f, -5.0f)));
    zombie2->AddComponent<Scene::SpriteRendererComponent>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    auto cubeShape2 = Core::BaseShapes::Cube();
    auto mesh2 = new Core::Mesh(cubeShape2.Vertices, cubeShape2.Indices);
    auto shader2 = new Core::Shader("../src/Core/BaseShader.vert", "../src/Core/BaseShader.frag");
    zombie2->AddComponent<Scene::MeshComponent>(*mesh2, *shader2);
    zombie2->AddComponent<Scene::CollisionComponent>();
    _scene.AddEntity(zombie2);

    auto floor = new ECS::Entity(&_scene);
    auto& transform = floor->AddComponent<Scene::TransformComponent>(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.6f, -5.0f)));
    transform.Transform = glm::scale(transform.Transform, glm::vec3(50.0f, 0.1f, 50.0f));
    floor->AddComponent<Scene::SpriteRendererComponent>(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    auto floorShape = Core::BaseShapes::Cube();
    auto floorMesh = new Core::Mesh(floorShape.Vertices, floorShape.Indices);
    auto floorShader = new Core::Shader("../src/Core/BaseShader.vert", "../src/Core/BaseShader.frag");
    floor->AddComponent<Scene::MeshComponent>(*floorMesh, *floorShader);
    _scene.AddEntity(floor);
}

void Game::Update(float deltaTime)
{
    _scene.OnUpdate(deltaTime);
}