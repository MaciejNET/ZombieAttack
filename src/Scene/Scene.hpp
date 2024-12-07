#pragma once

#ifndef SCENE_HPP
#define SCENE_HPP
#include <vector>

#include "ECS/Entity.hpp"
#include "Renderer/Renderer.hpp"

namespace Scene {
    class Scene
    {
    public:
        std::vector<ECS::Entity> GetEntities() const { return _entities; }
        void AddEntity(const ECS::Entity& entity);
        void AddComponent(const uuid_t& id, const ECS::Component& component);
        void OnUpdate(float deltaTime);
        void RemoveEntity(uuid_t id);
    private:
        std::vector<ECS::Entity> _entities;
        std::unordered_map<uuid_t, std::unordered_map<std::type_index, std::unique_ptr<ECS::Component>>> _components;
        Renderer::Renderer _renderer;
    };
}

#endif //SCENE_HPP
