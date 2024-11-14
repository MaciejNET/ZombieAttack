#include "Game.hpp"

#include <glm/ext/matrix_transform.hpp>

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
    auto cameraComponent = new Scene::CameraComponent(Core::Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 2.5f));
    camera->AddComponent(std::unique_ptr<Scene::CameraComponent>(cameraComponent));
    _scene.AddEntity(camera);

    auto light = new ECS::Entity(&_scene);
    auto lightComponent = new Scene::LightComponent(glm::vec4(1.0f), glm::vec3(0.0f, 1.0f, 1.0f), 1.0f);
    light->AddComponent(std::unique_ptr<Scene::LightComponent>(lightComponent));
    _scene.AddEntity(light);

    auto cube = new ECS::Entity(&_scene);
    auto transformComponent = new Scene::TransformComponent();
    transformComponent->Transform = glm::translate(transformComponent->Transform, glm::vec3(0.0f, 0.0f, 3.0f));
    cube->AddComponent(std::unique_ptr<Scene::TransformComponent>(transformComponent));
    auto spriteRendererComponent = new Scene::SpriteRendererComponent(glm::vec4(1.0f, 0.5f, 0.31f, 1.0f));
    cube->AddComponent(std::unique_ptr<Scene::SpriteRendererComponent>(spriteRendererComponent));
    auto cubeShape = Core::BaseShapes::Cube();
    auto mesh = new Core::Mesh(cubeShape.Vertices, cubeShape.Indices);
    auto shader = new Core::Shader("../src/Core/BaseShader.vert", "../src/Core/BaseShader.frag");
    auto meshComponent = new Scene::MeshComponent(*mesh, *shader);
    cube->AddComponent(std::unique_ptr<Scene::MeshComponent>(meshComponent));
    _scene.AddEntity(cube);
}

void Game::Update(float deltaTime)
{
    _scene.OnUpdate(deltaTime);
}