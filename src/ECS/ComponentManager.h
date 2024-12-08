// ComponentManager.h
#ifndef ZOMBIEATTACK_COMPONENTMANAGER_H
#define ZOMBIEATTACK_COMPONENTMANAGER_H

#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <stdexcept>
#include "Component.hpp"

namespace ECS {
    class ComponentManager {
    public:
        template<typename T, typename... Args>
        T& AddComponent(const int entityId, Args&&... args) {
            static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
            T component(std::forward<Args>(args)...);
            _components[entityId].emplace(typeid(T), std::make_unique<T>(std::move(component)));
            return dynamic_cast<T&>(*_components[entityId][typeid(T)]);
        }

        template<typename T>
        void RemoveComponent(const int entityId) {
            _components[entityId].erase(typeid(T));
        }

        void RemoveAllComponents(const int entityId) {
            _components.erase(entityId);
        }

        template<typename T>
        bool HasComponent(const int entityId) const {
            if (const auto entityIt = _components.find(entityId); entityIt != _components.end()) {
                return entityIt->second.contains(typeid(T));
            }
            return false;
        }

        template<typename T>
        T& GetComponent(const int entityId) {
            if (const auto entityIt = _components.find(entityId); entityIt != _components.end()) {
                if (const auto componentIt = entityIt->second.find(typeid(T)); componentIt != entityIt->second.end()) {
                    return dynamic_cast<T&>(*(componentIt->second));
                }
            }
            throw std::runtime_error("Component not found");
        }

    private:
        std::unordered_map<int, std::unordered_map<std::type_index, std::unique_ptr<Component>>> _components;
    };
} // namespace ECS

#endif // ZOMBIEATTACK_COMPONENTMANAGER_Hsa