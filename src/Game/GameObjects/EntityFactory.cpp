#include "EntityFactory.hpp"

#include <iostream>

#include "Core/BaseShapes.hpp"
#include "Game/Components/BulletController.hpp"
#include "Game/Components/PlayerController.hpp"
#include "Game/Components/ZombieController.hpp"
#include "Scene/Components.hpp"

ECS::Entity EntityFactory::CreatePlayer(Scene::Scene& scene, glm::mat4 transform)
{
    auto player = scene.AddEntity();
    player.AddComponent<Scene::TransformComponent>(transform);
    player.AddComponent<Scene::SpriteRendererComponent>(glm::vec4(0.8627f, 0.0784f, 0.2353f, 1.0f));
    player.AddComponent<Scene::CameraComponent>(Core::Camera());
    auto cubeShape = Core::BaseShapes::Cube();
    auto mesh = std::make_shared<Core::Mesh>(cubeShape.Vertices, cubeShape.Indices);
    auto shader = std::make_shared<Core::Shader>("../src/Core/BaseShader.vert", "../src/Core/BaseShader.frag");
    player.AddComponent<Scene::MeshComponent>(mesh, shader);
    player.AddComponent<Scene::ScriptableComponent>().Bind<PlayerController>();
    player.AddComponent<Scene::CollisionComponent>(player);
    player.AddComponent<Scene::HealthComponent>();
    player.AddComponent<Scene::PlayerComponent>();

    return player;
}

ECS::Entity EntityFactory::CreateZombie(Scene::Scene& scene, glm::mat4 transform)
{
    auto zombie = scene.AddEntity();
    zombie.AddComponent<Scene::ScriptableComponent>().Bind<ZombieController>();
    zombie.AddComponent<Scene::DamageComponent>();
    zombie.AddComponent<Scene::HealthComponent>();
    zombie.AddComponent<Scene::ZombieComponent>();
    zombie.AddComponent<Scene::DamageComponent>();
    zombie.AddComponent<Scene::TransformComponent>(transform);
    zombie.AddComponent<Scene::SpriteRendererComponent>(glm::vec4(0.1961f, 0.8039f, 0.1961f, 1.0f));
    auto cubeShape = Core::BaseShapes::Cube();
    auto mesh = std::make_shared<Core::Mesh>(cubeShape.Vertices, cubeShape.Indices);
    auto shader = std::make_shared<Core::Shader>("../../src/Core/BaseShader.vert", "../../src/Core/BaseShader.frag");
    zombie.AddComponent<Scene::MeshComponent>(mesh, shader);
    zombie.AddComponent<Scene::CollisionComponent>(zombie);

    return zombie;
}

ECS::Entity EntityFactory::CreateBullet(Scene::Scene& scene, glm::mat4 transform, glm::vec3 direction)
{
    auto bullet = scene.AddEntity();
    bullet.AddComponent<Scene::TransformComponent>(transform);
    bullet.AddComponent<Scene::SpriteRendererComponent>(glm::vec4(0.8235f, 0.4118f, 0.1176f, 1.0f));
    auto bulletShape = Core::BaseShapes::Sphere();
    auto bulletMesh = std::make_shared<Core::Mesh>(bulletShape.Vertices, bulletShape.Indices);
    auto bulletShader = std::make_shared<Core::Shader>("../src/Core/BaseShader.vert", "../src/Core/BaseShader.frag");
    bullet.AddComponent<Scene::MeshComponent>(bulletMesh, bulletShader);
    bullet.AddComponent<Scene::DirectionComponent>(direction);
    bullet.AddComponent<Scene::ScriptableComponent>().Bind<BulletController>();
    bullet.AddComponent<Scene::CollisionComponent>(bullet);
    bullet.AddComponent<Scene::DamageComponent>();

    return bullet;
}

ECS::Entity EntityFactory::CreateCoin(Scene::Scene& scene, glm::mat4 transform)
{
    auto coin = scene.AddEntity();
    coin.AddComponent<Scene::TransformComponent>(transform);
    coin.AddComponent<Scene::SpriteRendererComponent>(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    auto coinShape = Core::BaseShapes::Sphere();
    auto coinMesh = std::make_shared<Core::Mesh>(coinShape.Vertices, coinShape.Indices);
    auto coinShader = std::make_shared<Core::Shader>("../../src/Core/BaseShader.vert", "../../src/Core/BaseShader.frag");
    coin.AddComponent<Scene::MeshComponent>(coinMesh, coinShader);
    coin.AddComponent<Scene::CollisionComponent>(coin);

    return coin;
}

ECS::Entity EntityFactory::CreateTrap(Scene::Scene& scene, glm::mat4 transform)
{
    auto trap = scene.AddEntity();
    trap.AddComponent<Scene::TransformComponent>(transform);
    trap.AddComponent<Scene::SpriteRendererComponent>(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    auto trapShape = Core::BaseShapes::Cube();
    auto trapMesh = std::make_shared<Core::Mesh>(trapShape.Vertices, trapShape.Indices);
    auto trapShader = std::make_shared<Core::Shader>("../../src/Core/BaseShader.vert", "../../src/Core/BaseShader.frag");
    trap.AddComponent<Scene::MeshComponent>(trapMesh, trapShader);
    trap.AddComponent<Scene::CollisionComponent>(trap);

    return trap;
}

ECS::Entity EntityFactory::CreateObstacle(Scene::Scene& scene, glm::mat4 transform)
{
    auto obstacle = scene.AddEntity();
    obstacle.AddComponent<Scene::TransformComponent>(transform);
    obstacle.AddComponent<Scene::SpriteRendererComponent>(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
    auto obstacleShape = Core::BaseShapes::Cube();
    auto obstacleMesh = std::make_shared<Core::Mesh>(obstacleShape.Vertices, obstacleShape.Indices);
    auto obstacleShader = std::make_shared<Core::Shader>("../../src/Core/BaseShader.vert", "../../src/Core/BaseShader.frag");
    obstacle.AddComponent<Scene::MeshComponent>(obstacleMesh, obstacleShader);
    obstacle.AddComponent<Scene::CollisionComponent>(obstacle);

    return obstacle;
}

