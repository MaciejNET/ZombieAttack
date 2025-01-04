#ifndef ZOMBIECONTROLLER_HPP
#define ZOMBIECONTROLLER_HPP
#include "ECS/ScriptableEntity.hpp"

class ZombieController final : public ECS::ScriptableEntity
{
    void OnUpdate(float deltaTime) override;
    void OnDestroy() override;
    float _speed = 1.5f;
    float _attackCooldown = 1.0f;
};

#endif //ZOMBIECONTROLLER_HPP
