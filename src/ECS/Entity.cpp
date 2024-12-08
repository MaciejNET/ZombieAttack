#include "Entity.hpp"

namespace ECS {
    Entity::Entity(const int id, Scene::Scene* scene) : _id(id), _scene(scene) { }

    void Entity::AddToScene() const
    {
        if (_scene)
        {
            _scene->AddEntity();
        }
    }
}