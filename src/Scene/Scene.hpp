#pragma once

#ifndef SCENE_HPP
#define SCENE_HPP
#include <vector>

#include "ECS/ComponentManager.h"

namespace ECS {
    class Entity;
}

namespace Scene {
    class Scene
    {
    public:
        ECS::Entity AddEntity();
        std::vector<ECS::Entity> GetEntities();
        ECS::ComponentManager& GetComponentManager() { return _componentManager; }
        void OnUpdate(float deltaTime);
        void RemoveEntity(int id);
    private:
        std::vector<int> _entities;
        ECS::ComponentManager _componentManager;
        friend class ECS::Entity;
    };
}

#endif //SCENE_HPP
