// ComponentManager.h
#ifndef ZOMBIEATTACK_COMPONENTMANAGER_H
#define ZOMBIEATTACK_COMPONENTMANAGER_H

#include <unordered_map>
#include <vector>
#include <typeindex>
#include <typeinfo>
#include <stdexcept>
#include <memory>
#include "Component.hpp"

namespace ECS {
    class ComponentManager {
    public:
        template<typename T, typename... Args>
        T& AddComponent(const int entityId, Args&&... args)
        {
            static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
            auto& components = _components[typeid(T)];
            if (entityId >= components.size())
            {
                components.resize(entityId + 1);
            }
            components[entityId] = std::make_unique<T>(std::forward<Args>(args)...);
            return *static_cast<T*>(components[entityId].get());
        }

        template<typename T>
        void RemoveComponent(const int entityId)
        {
            auto& components = _components[typeid(T)];
            if (entityId < components.size())
            {
                components[entityId].reset();
            }
        }

        void RemoveAllComponents(const int entityId)
        {
            for (auto& [type, components] : _components)
            {
                if (entityId < components.size())
                {
                    components[entityId].reset();
                }
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
            return entityId < components.size() && components[entityId] != nullptr;
        }

        template<typename T>
        T& GetComponent(const int entityId)
        {
            auto& components = _components.at(typeid(T));
            if (entityId >= components.size() || !components[entityId])
            {
                throw std::runtime_error("Component not found");
            }
            return *static_cast<T*>(components[entityId].get());
        }

    private:
        std::unordered_map<std::type_index, std::vector<std::unique_ptr<Component>>> _components;
    };
} // namespace ECS

#endif // ZOMBIEATTACK_COMPONENTMANAGER_H