#pragma once

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <unordered_map>
#include <uuid/uuid.h>
#include <typeindex>
#include <vector>

#include "Component.hpp"

namespace Scene {
    class Scene;
}

namespace ECS {
    class Entity
    {
    public:
        Entity() = default;
        explicit Entity(uuid_t id, Scene::Scene* scene) : _scene(scene) { uuid_copy(_id, id); }
        ~Entity() = default;

        const uuid_t& GetUUID() const { return _id; }

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args)
        {
            T* component = new T(std::forward<Args>(args)...);
            _components[typeid(T)] = std::unique_ptr<Component>(component);
            return *component;
        }

        template<typename T>
        T& GetComponent() const
        {
            const auto it = _components.find(typeid(T));
            if (it != _components.end())
            {
                return *dynamic_cast<T*>(it->second.get());
            }
            throw std::runtime_error("Component not found");
        }

        std::vector<Component*> GetComponents() const
        {
            std::vector<Component*> components;
            for (auto& [type, component] : _components)
            {
                if (Component* castedComponent = component.get())
                {
                    components.push_back(castedComponent);
                }
            }
            return components;
        }

        template<typename T>
        bool HasComponent() const
        {
            return _components.contains(typeid(T));
        }

        template<typename T>
        void RemoveComponent()
        {
            _components.erase(typeid(T));
        }

        Scene::Scene* GetScene() const { return _scene; }
        void AddToScene();
    private:
        uuid_t _id{};
        std::unordered_map<std::type_index, std::unique_ptr<Component>> _components;
        Scene::Scene* _scene;
    };
}

#endif //ENTITY_HPP
