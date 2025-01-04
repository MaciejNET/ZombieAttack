#ifndef PLAYERCONTROLLER_HPP
#define PLAYERCONTROLLER_HPP
#include <glm/glm.hpp>

#include "ECS/ScriptableEntity.hpp"
#include "Game/GameObjects/GameItems.hpp"
#include "Game/GameObjects/Inventory.hpp"

class PlayerController final : public ECS::ScriptableEntity
{
    void OnCreate() override;
    void OnUpdate(float deltaTime) override;
    void DrawPlayerData();
    float _speed = 3.0f;
    std::shared_ptr<Inventory> _inventory{};
    bool _itemChanged = false;
    int _coins = 0;
};

#endif //PLAYERCONTROLLER_HPP
