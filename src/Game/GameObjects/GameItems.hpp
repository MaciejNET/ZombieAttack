#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "Scene/Scene.hpp"

enum class ItemType
{
    GUN,
    TRAP,
    HEALTH
};

struct PlayerCoordinates
{
    glm::mat4 Transform;
    glm::vec3 Direction;
};

class GameItem
{
public:
    explicit GameItem(const ItemType type) : Type(type) {};
    virtual ~GameItem() = default;
    ItemType Type;
    virtual void Use(PlayerCoordinates playerCoordinates, Scene::Scene& scene, float deltaTime) = 0;
    virtual void Update(float deltaTime) = 0;
};

class Gun : public GameItem
{
public:
    int BulletsPerShot{1};
    float ShootInterval{0.0f};
    float ShootCooldown{0.0f};
    int Ammo{100};
    float Speed{1.0f};
    bool EnableFullAuto{false};

    Gun(const int bulletsPerShot, const float shootInterval, const float shootCooldown,
        const int ammo, const float speed, const bool enableFullAuto)
        : GameItem(ItemType::GUN),
          BulletsPerShot(bulletsPerShot),
          ShootInterval(shootInterval),
          ShootCooldown(shootCooldown),
          Ammo(ammo),
          Speed(speed),
          EnableFullAuto(enableFullAuto) {};

    void Use(PlayerCoordinates playerCoordinates, Scene::Scene& scene, float deltaTime) override;
    void Update(float deltaTime) override;

protected:
    virtual void Shoot(Scene::Scene& scene, PlayerCoordinates playerCoordinates) = 0;
};

class Pistol final : public Gun
{
public:
    Pistol() : Gun(1, 0.5f, 0.5f, std::numeric_limits<int>::max(), 1.0f, false) {};
private:
    void Shoot(Scene::Scene& scene, PlayerCoordinates playerCoordinates) override;
};

class BurstRifle final : public Gun
{
public:
    BurstRifle() : Gun(3, 0.5f, 0.25f, 100, 1.0f, false) {};
private:
    void Shoot(Scene::Scene& scene, PlayerCoordinates playerCoordinates) override;
};

class Shotgun final : public Gun
{
public:
    Shotgun() : Gun(5, 0.5f, 1.0f, 150, 1.0f, false) {};
private:
    void Shoot(Scene::Scene& scene, PlayerCoordinates playerCoordinates) override;
};

class Rifle final : public Gun
{
public:
    Rifle() : Gun(1, 0.25f, 0.25f, 250, 2.0f, true) {};
private:
    void Shoot(Scene::Scene& scene, PlayerCoordinates playerCoordinates) override;
};

class MiniGun final : public Gun
{
public:
    MiniGun() : Gun(1, 0.1f, 0.1f, 1000, 5.0f, true) {};
private:
    void Shoot(Scene::Scene& scene, PlayerCoordinates playerCoordinates) override;
};

class Trap final : public GameItem
{
public:
    Trap() : GameItem(ItemType::TRAP) {};
    void Use(PlayerCoordinates playerCoordinates, Scene::Scene& scene, float deltaTime) override;
    void Update(float deltaTime) override;
};

class Health final : public GameItem
{
public:
    Health() : GameItem(ItemType::HEALTH) {};
    void Use(PlayerCoordinates playerCoordinates, Scene::Scene& scene, float deltaTime) override;
    void Update(float deltaTime) override;
};

#endif //GAMEOBJECT_HPP
