// ComponentManager.h
#ifndef ZOMBIEATTACK_COMPONENTMANAGER_H
#define ZOMBIEATTACK_COMPONENTMANAGER_H

#include <unordered_map>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <stdexcept>
#include "Component.hpp"

namespace ECS {
    class ComponentManager {
    public:
        template<typename T, typename... Args>
        T& AddComponent(const int entityId, Args&&... args)
        {
            static_assert(std::is_base_of_v<Component, T>, "T must be derived from Component");
            auto& components = _components[typeid(T)];
            components[entityId] = std::make_unique<T>(std::forward<Args>(args)...);
            return *static_cast<T*>(components[entityId].get());
        }

        template<typename T>
        void RemoveComponent(const int entityId)
        {
            auto it = _components.find(typeid(T));
            if (it != _components.end())
            {
                it->second.erase(entityId);
            }
        }

        void RemoveAllComponents(const int entityId)
        {
            for (auto& [type, components] : _components)
            {
                components.erase(entityId);
            }
        }

        template<typename T>
        bool HasComponent(const int entityId) const
        {
            const auto it = _components.find(typeid(T));
            if (it == _components.end())
            {
                return false;
            }
            const auto& components = it->second;
            return components.find(entityId) != components.end();
        }

        template<typename T>
        T& GetComponent(const int entityId)
        {
            auto& components = _components.at(typeid(T));
            auto compIt = components.find(entityId);
            if (compIt == components.end())
            {
                throw std::runtime_error("Component not found");
            }
            return *static_cast<T*>(compIt->second.get());
        }

    private:
        std::unordered_map<std::type_index, std::unordered_map<int, std::unique_ptr<Component>>> _components;
    };
} // namespace ECS

#endif // ZOMBIEATTACK_COMPONENTMANAGER_H