#pragma once

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Scene/Scene.hpp"

namespace ECS {
    class Entity
    {
    public:
        Entity() = default;
        Entity(int id, Scene::Scene* scene);
        ~Entity() = default;

        int GetId() const { return _id; }

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args)
        {
            return _scene->_componentManager.AddComponent<T>(_id, std::forward<Args>(args)...);
        }

        template<typename T>
        T& GetComponent() const
        {
            return _scene->_componentManager.GetComponent<T>(_id);
        }

        template<typename T>
        bool HasComponent() const
        {
            return _scene->_componentManager.HasComponent<T>(_id);
        }

        template<typename T>
        void RemoveComponent() const
        {
            _scene->_componentManager.RemoveComponent<T>(_id);
        }

        Scene::Scene* GetScene() const { return _scene; }
        void AddToScene() const;

    private:
        int _id{-1};
        Scene::Scene* _scene{nullptr};
    };
}

#endif // ENTITY_HPP