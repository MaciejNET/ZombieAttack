#include "BulletController.hpp"

#include <iostream>
#include <glm/ext/matrix_transform.hpp>

#include "Scene/Components.hpp"

void BulletController::OnCreate()
{
    _initialPosition = GetComponent<Scene::TransformComponent>().Transform[3];
}


void BulletController::OnUpdate(float deltaTime)
{
    auto& transform = GetComponent<Scene::TransformComponent>().Transform;
    auto& collision = GetComponent<Scene::CollisionComponent>();
    auto& direction = GetComponent<Scene::DirectionComponent>().Direction;

    auto velocity = glm::normalize(direction) * _speed * deltaTime;
    transform = glm::translate(transform, velocity);

    glm::vec3 currentPosition = transform[3];
    float distanceTraveled = glm::distance(_initialPosition, currentPosition);
    if (distanceTraveled > _maxDistance)
    {
        auto scene = _entity->GetScene();
        scene->RemoveEntity(_entity);
        return;
    }

    if (const auto& entity = collision.CollisionDetection(_entity))
    {
        auto scene = _entity->GetScene();
        if (entity->HasComponent<Scene::ZombieComponent>())
        {
            auto& zombieHealth = entity->GetComponent<Scene::HealthComponent>();
            auto& damage = _entity->GetComponent<Scene::DamageComponent>().Damage;
            zombieHealth.Health -= damage;
            if (zombieHealth.Health <= 0)
            {
                scene->RemoveEntity(entity);
            }
        }
        if (entity->HasComponent<Scene::PlayerComponent>())
        {
            return;
        }
        scene->RemoveEntity(_entity);
    }
}
