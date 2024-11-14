#ifndef CAMERACONTROLLER_HPP
#define CAMERACONTROLLER_HPP
#include "ECS/ScriptableEntity.hpp"
#include "Scene/Components.hpp"

class CameraController final : public ECS::ScriptableEntity
{
    void OnUpdate(float deltaTime) override;
};

#endif //CAMERACONTROLLER_HPP
