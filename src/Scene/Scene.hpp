#pragma once

#ifndef SCENE_HPP
#define SCENE_HPP
#include <vector>

#include "ECS/Entity.hpp"
#include "Renderer/Renderer.hpp"

namespace Scene {
    struct AABB
    {
        glm::vec3 Min;
        glm::vec3 Max;
    };

    class Scene
    {
    public:
        std::vector<ECS::Entity*> GetEntities() const { return _entities; }
        void AddEntity(ECS::Entity* entity);
        void OnUpdate(float deltaTime);
        void RemoveEntity(ECS::Entity* entity);
    private:
        std::vector<ECS::Entity*> _entities;
        Renderer::Renderer _renderer;
    };
}

#endif //SCENE_HPP
