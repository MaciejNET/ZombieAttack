#include "Game.hpp"

#include <glm/ext/matrix_transform.hpp>

#include "Components/CameraController.hpp"
#include "Core/BaseShapes.hpp"
#include "Scene/Components.hpp"

Game::Game()
{
    _scene = Scene::Scene();
}

void Game::Init()
{
    // Create entities
    auto camera = new ECS::Entity(&_scene);
    camera->AddComponent<Scene::CameraComponent>(Core::Camera());
    camera->AddComponent<Scene::ScriptableComponent>().Bind<CameraController>();
    _scene.AddEntity(camera);

    auto light = new ECS::Entity(&_scene);
    light->AddComponent<Scene::LightComponent>(glm::vec4(1.0f), glm::vec3(0.0f), 1.0f);
    _scene.AddEntity(light);

    auto cube = new ECS::Entity(&_scene);
    cube->AddComponent<Scene::TransformComponent>(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f)));
    cube->AddComponent<Scene::SpriteRendererComponent>(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    auto cubeShape = Core::BaseShapes::Cube();
    auto mesh = new Core::Mesh(cubeShape.Vertices, cubeShape.Indices);
    auto shader = new Core::Shader("../src/Core/BaseShader.vert", "../src/Core/BaseShader.frag");
    cube->AddComponent<Scene::MeshComponent>(*mesh, *shader);
    _scene.AddEntity(cube);
}

void Game::Update(float deltaTime)
{
    _scene.OnUpdate(deltaTime);
}