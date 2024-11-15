#ifndef PLAYERCONTROLLER_HPP
#define PLAYERCONTROLLER_HPP
#include "ECS/ScriptableEntity.hpp"

class PlayerController final : public ECS::ScriptableEntity
{
    void OnCreate() override;
    void OnUpdate(float deltaTime) override;
    float _speed = 3.0f;
};

#endif //PLAYERCONTROLLER_HPP
