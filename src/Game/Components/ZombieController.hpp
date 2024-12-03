#ifndef ZOMBIECONTROLLER_HPP
#define ZOMBIECONTROLLER_HPP
#include "ECS/ScriptableEntity.hpp"

class ZombieController final : public ECS::ScriptableEntity
{
    void OnUpdate(float deltaTime) override;
    float _speed = 1.5f;
};

#endif //ZOMBIECONTROLLER_HPP
