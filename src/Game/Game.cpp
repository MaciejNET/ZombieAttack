#include "Game.hpp"

#include <glm/ext/matrix_transform.hpp>

#include "Components/PlayerController.hpp"
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
    light->AddComponent<Scene::LightComponent>(glm::vec4(1.0f), glm::vec3(5.0f), 1.0f);
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
    _scene.AddEntity(player);

    auto cube1 = new ECS::Entity(&_scene);
    cube1->AddComponent<Scene::TransformComponent>(glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, 0.0f, -5.0f)));
    cube1->AddComponent<Scene::SpriteRendererComponent>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    auto cubeShape1 = Core::BaseShapes::Cube();
    auto mesh1 = new Core::Mesh(cubeShape1.Vertices, cubeShape1.Indices);
    auto shader1 = new Core::Shader("../src/Core/BaseShader.vert", "../src/Core/BaseShader.frag");
    cube1->AddComponent<Scene::MeshComponent>(*mesh1, *shader1);
    cube1->AddComponent<Scene::CollisionComponent>();
    _scene.AddEntity(cube1);

    auto cube2 = new ECS::Entity(&_scene);
    cube2->AddComponent<Scene::TransformComponent>(glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 0.0f, -5.0f)));
    cube2->AddComponent<Scene::SpriteRendererComponent>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    auto cubeShape2 = Core::BaseShapes::Cube();
    auto mesh2 = new Core::Mesh(cubeShape2.Vertices, cubeShape2.Indices);
    auto shader2 = new Core::Shader("../src/Core/BaseShader.vert", "../src/Core/BaseShader.frag");
    cube2->AddComponent<Scene::MeshComponent>(*mesh2, *shader2);
    cube2->AddComponent<Scene::CollisionComponent>();
    _scene.AddEntity(cube2);

    auto floor = new ECS::Entity(&_scene);
    auto& transform = floor->AddComponent<Scene::TransformComponent>(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.6f, 0.0f)));
    transform.Transform = glm::scale(transform.Transform, glm::vec3(10.0f, 0.1f, 10.0f));
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