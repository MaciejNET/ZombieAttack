#ifndef ENTITYFACTORY_HPP
#define ENTITYFACTORY_HPP
#include <glm/glm.hpp>
#include <memory>

#include "Scene/Components.hpp"
#include "ECS/Entity.hpp"
#include "Core/Mesh.hpp"
#include "Core/Shader.hpp"
#include "Core/Model.hpp"

class EntityFactory
{
public:
    static ECS::Entity CreatePlayer(Scene::Scene& scene, glm::mat4 transform);
    static ECS::Entity CreateZombie(Scene::Scene& scene, glm::mat4 transform);
    static ECS::Entity CreateBullet(Scene::Scene& scene, glm::mat4 transform, glm::vec3 direction);
    static ECS::Entity CreateCoin(Scene::Scene& scene, glm::mat4 transform);
    static ECS::Entity CreateTrap(Scene::Scene& scene, glm::mat4 transform);
    static ECS::Entity CreateObstacle(Scene::Scene& scene, glm::mat4 transform);
    static void InitResources();

private:
    static std::shared_ptr<Core::Mesh> _cubeMesh;
    static std::shared_ptr<Core::Mesh> _sphereMesh;
    static std::shared_ptr<Core::Shader> _baseShader;
    static std::shared_ptr<Core::Model> _playerModel;
    static std::shared_ptr<Core::Model> _zombieModel;
    static std::shared_ptr<Core::Model> _coinModel;
    static std::shared_ptr<Core::Model> _pistolModel;
    static std::shared_ptr<Core::Model> _burstRifleModel;
    static std::shared_ptr<Core::Model> _shotgunModel;
    static std::shared_ptr<Core::Model> _rifleModel;
    static std::shared_ptr<Core::Model> _minigunModel;
};

#endif //ENTITYFACTORY_HPP
