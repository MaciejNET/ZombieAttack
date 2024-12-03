#include "Entity.hpp"
#include "Scene/Scene.hpp"

namespace ECS {
    void Entity::AddToScene()
    {
        if (_scene)
        {
            _scene->AddEntity(this);
        }
    }

}
