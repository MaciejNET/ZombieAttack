#ifndef ENTITYFACTORY_HPP
#define ENTITYFACTORY_HPP
#include <glm/glm.hpp>

#include "Scene/Components.hpp"
#include "ECS/Entity.hpp"

class EntityFactory
{
public:
    static ECS::Entity CreatePlayer(Scene::Scene& scene, glm::mat4 transform);
    static ECS::Entity CreateZombie(Scene::Scene& scene, glm::mat4 transform);
    static ECS::Entity CreateBullet(Scene::Scene& scene, glm::mat4 transform, glm::vec3 direction);
    static ECS::Entity CreateCoin(Scene::Scene& scene, glm::mat4 transform);
    static ECS::Entity CreateTrap(Scene::Scene& scene, glm::mat4 transform);
    static ECS::Entity CreateObstacle(Scene::Scene& scene, glm::mat4 transform);
};

#endif //ENTITYFACTORY_HPP
