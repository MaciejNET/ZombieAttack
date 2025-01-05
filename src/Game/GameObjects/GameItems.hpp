#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <utility>

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

struct GameItemData
{
    ItemType Type;
    std::string Name;
    int Count;
};

class GameItem
{
public:
    explicit GameItem(const ItemType type, std::string name) : Type(type), Name(std::move(name)) {};
    virtual ~GameItem() = default;
    ItemType Type;
    std::string Name;
    int Count{0};
    virtual void Use(PlayerCoordinates playerCoordinates, Scene::Scene& scene, float deltaTime) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual GameItemData GetData() const = 0;
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

    Gun(std::string name, const int bulletsPerShot, const float shootInterval, const float shootCooldown,
        const int ammo, const float speed, const bool enableFullAuto)
        : GameItem(ItemType::GUN, std::move(name)),
          BulletsPerShot(bulletsPerShot),
          ShootInterval(shootInterval),
          ShootCooldown(shootCooldown),
          Ammo(ammo),
          Speed(speed),
          EnableFullAuto(enableFullAuto) {};

    void Use(PlayerCoordinates playerCoordinates, Scene::Scene& scene, float deltaTime) override;
    void Update(float deltaTime) override;
    GameItemData GetData() const override { return {Type, Name, Ammo}; }

protected:
    virtual void Shoot(Scene::Scene& scene, PlayerCoordinates playerCoordinates) = 0;
};

class Pistol final : public Gun
{
public:
    Pistol() : Gun("Pistol", 1, 0.5f, 0.5f, std::numeric_limits<int>::max(), 1.0f, false) {};
private:
    void Shoot(Scene::Scene& scene, PlayerCoordinates playerCoordinates) override;
};

class BurstRifle final : public Gun
{
public:
    BurstRifle() : Gun("Burst Rifle", 3, 0.5f, 0.25f, 150, 1.0f, false) {};
private:
    void Shoot(Scene::Scene& scene, PlayerCoordinates playerCoordinates) override;
};

class Shotgun final : public Gun
{
public:
    Shotgun() : Gun("Shotgun", 5, 0.5f, 1.0f, 250, 1.0f, false) {};
private:
    void Shoot(Scene::Scene& scene, PlayerCoordinates playerCoordinates) override;
};

class Rifle final : public Gun
{
public:
    Rifle() : Gun("Rifle", 1, 0.25f, 0.25f, 400, 2.0f, true) {};
private:
    void Shoot(Scene::Scene& scene, PlayerCoordinates playerCoordinates) override;
};

class MiniGun final : public Gun
{
public:
    MiniGun() : Gun("Minigun", 1, 0.1f, 0.1f, 1000, 5.0f, true) {};
private:
    void Shoot(Scene::Scene& scene, PlayerCoordinates playerCoordinates) override;
};

class Trap final : public GameItem
{
public:
    Trap() : GameItem(ItemType::TRAP, "Trap") {};
    void Use(PlayerCoordinates playerCoordinates, Scene::Scene& scene, float deltaTime) override;
    void Update(float deltaTime) override;
    GameItemData GetData() const override { return {Type, Name, Count}; }
};

class Health final : public GameItem
{
public:
    Health() : GameItem(ItemType::HEALTH, "Health Pack") {};
    void Use(PlayerCoordinates playerCoordinates, Scene::Scene& scene, float deltaTime) override;
    void Update(float deltaTime) override;
    GameItemData GetData() const override { return {Type, Name, Count}; }
};

#endif //GAMEOBJECT_HPP
