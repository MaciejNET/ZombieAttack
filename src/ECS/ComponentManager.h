#ifndef ZOMBIEATTACK_COMPONENTMANAGER_H
#define ZOMBIEATTACK_COMPONENTMANAGER_H

#include <unordered_map>
#include <typeindex>
#include "Component.hpp"

namespace ECS {
    class ComponentManager
    {
    public:
        template<typename T, typename... Args>
        T& AddComponent(int entityId, Args&&... args)
        {
            T component(std::forward<Args>(args)...);
            _components[entityId].insert(component);
            return component;
        }
    private:
        std::unordered_map<int, std::unordered_map<std::type_index, Component>> _components;
    };

} // ECS

#endif //ZOMBIEATTACK_COMPONENTMANAGER_H
