#ifndef BULLETCONTROLLER_HPP
#define BULLETCONTROLLER_HPP
#include <glm/vec3.hpp>

#include "ECS/ScriptableEntity.hpp"

class BulletController final : public ECS::ScriptableEntity
{
    void OnCreate() override;
    void OnUpdate(float deltaTime) override;
    float _speed = 30.0f;
    glm::vec3 _initialPosition{};
    float _maxDistance = 25.0f;
    glm::vec3 _direction{};
};

#endif //BULLETCONTROLLER_HPP
