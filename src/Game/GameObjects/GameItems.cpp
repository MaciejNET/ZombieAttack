#include <iostream>
#include <Game/GameObjects/GameItems.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "EntityFactory.hpp"

void Gun::Use(const PlayerCoordinates playerCoordinates, Scene::Scene& scene, const float deltaTime)
{
    if (EnableFullAuto)
    {
        ShootCooldown -= deltaTime;
        if (ShootCooldown <= 0.0f && Ammo > 0)
        {
            Shoot(scene, playerCoordinates);
            ShootCooldown = ShootInterval;
            Ammo -= BulletsPerShot;
            std::cout << "Ammo: " << Ammo << std::endl;
        }
    }
    else
    {
        if (ShootCooldown <= 0.0f && Ammo > 0)
        {
            Shoot(scene, playerCoordinates);
            ShootCooldown = ShootInterval;
            Ammo -= BulletsPerShot;
            std::cout << "Ammo: " << Ammo << std::endl;
        }
    }
}

void Gun::Update(const float deltaTime)
{
    ShootCooldown -= deltaTime;
}

void Pistol::Shoot(Scene::Scene& scene, const PlayerCoordinates playerCoordinates)
{
    auto bulletTransform = glm::translate(playerCoordinates.Transform, playerCoordinates.Direction);
    bulletTransform = glm::scale(bulletTransform, glm::vec3(0.25f));

    EntityFactory::CreateBullet(scene, bulletTransform, playerCoordinates.Direction);
}

void BurstRifle::Shoot(Scene::Scene& scene, const PlayerCoordinates playerCoordinates)
{
    for (int i = 0; i < 3; ++i)
    {
        glm::vec3 offset = playerCoordinates.Direction * (static_cast<float>(i) * 1.2f);
        auto bulletTransform = glm::translate(playerCoordinates.Transform, offset);
        bulletTransform = glm::scale(bulletTransform, glm::vec3(0.25f));

        EntityFactory::CreateBullet(scene, bulletTransform, playerCoordinates.Direction);
    }
}

void Shotgun::Shoot(Scene::Scene& scene, const PlayerCoordinates playerCoordinates)
{
    for (int i = 0; i < 5; ++i)
    {
        const float angle = glm::radians(-25.0f + static_cast<float>(i) * 5.0f);
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
        auto newDirection = -abs(playerCoordinates.Direction * angle);

        glm::vec3 horizontalOffset = glm::vec3(static_cast<float>(i) * 0.5f - 1.0f, 0.0f, 0.0f);
        auto bulletTransform = glm::translate(playerCoordinates.Transform, playerCoordinates.Direction);
        bulletTransform = glm::translate(bulletTransform, horizontalOffset + newDirection);
        bulletTransform = glm::scale(bulletTransform, glm::vec3(0.25f));

        EntityFactory::CreateBullet(scene, bulletTransform, newDirection);
    }
}

void Rifle::Shoot(Scene::Scene& scene, const PlayerCoordinates playerCoordinates)
{
    auto bulletTransform = glm::translate(playerCoordinates.Transform, playerCoordinates.Direction);
    bulletTransform = glm::scale(bulletTransform, glm::vec3(0.25f));

    EntityFactory::CreateBullet(scene, bulletTransform, playerCoordinates.Direction);
}

void MiniGun::Shoot(Scene::Scene& scene, const PlayerCoordinates playerCoordinates)
{
    auto bulletTransform = glm::translate(playerCoordinates.Transform, playerCoordinates.Direction);
    bulletTransform = glm::scale(bulletTransform, glm::vec3(0.25f));

    EntityFactory::CreateBullet(scene, bulletTransform, playerCoordinates.Direction);
}

void Trap::Use(const PlayerCoordinates playerCoordinates, Scene::Scene& scene, float deltaTime)
{

}

void Trap::Update(const float deltaTime)
{

}

void Health::Use(const PlayerCoordinates playerCoordinates, Scene::Scene& scene, float deltaTime)
{

}

void Health::Update(const float deltaTime)
{

}