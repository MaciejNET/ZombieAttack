#include "ZombieController.hpp"

#include <iostream>
#include <glm/ext/matrix_transform.hpp>

#include "Game/GameObjects/EntityFactory.hpp"
#include "Scene/Components.hpp"

void ZombieController::OnUpdate(float deltaTime)
{
    _attackCooldown -= deltaTime;
    auto& transform = GetComponent<Scene::TransformComponent>().Transform;
    auto scene = _entity.GetScene();
    auto entities = scene->GetEntities();
    auto player = (entities | std::ranges::views::filter([](const ECS::Entity entity) {
        return entity.HasComponent<Scene::PlayerComponent>();
    })).front();

    if (player.GetId() > 0)
    {
        auto& playerTransform = player.GetComponent<Scene::TransformComponent>().Transform;
        auto playerPosition = glm::vec3(playerTransform[3]);
        auto zombiePosition = glm::vec3(transform[3]);
        auto direction = playerPosition - zombiePosition;
        auto distance = glm::length(direction);

        auto collision = GetComponent<Scene::CollisionComponent>();
        if (distance > 0.1f)
        {
            auto velocity = glm::normalize(direction) * _speed * deltaTime;
            transform = glm::translate(transform, velocity);
            const auto& entity = collision.CollisionDetection(_entity);

            if (entity.GetId() != -1)
            {
                if (entity.HasComponent<Scene::CoinComponent>())
                {
                    return;
                }
                if (entity.HasComponent<Scene::PlayerComponent>() && _attackCooldown <= 0.0f)
                {
                    auto& playerHealth = entity.GetComponent<Scene::HealthComponent>();
                    auto& damage = _entity.GetComponent<Scene::DamageComponent>().Damage;
                    playerHealth.Health -= damage;
                    _attackCooldown = 1.0f;
                }
                transform = glm::translate(transform, -velocity);
            }
        }
    }
}

void ZombieController::OnDestroy()
{
    EntityFactory::CreateCoin(*_entity.GetScene(), GetComponent<Scene::TransformComponent>().Transform);
    const auto scene = _entity.GetScene();
    auto entities = scene->GetEntities();
    const auto waveController = (entities | std::ranges::views::filter([](const ECS::Entity entity) {
        return entity.HasComponent<Scene::WaveComponent>();
    })).front();

    auto& waveComponent = waveController.GetComponent<Scene::WaveComponent>();
    waveComponent.ZombiesLeft--;
}
