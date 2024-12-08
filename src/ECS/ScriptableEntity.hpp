#pragma once

#ifndef SCRIPTABLEENTITY_HPP
#define SCRIPTABLEENTITY_HPP
#include "Entity.hpp"

namespace ECS {
    class ScriptableEntity
    {
    public:
        virtual ~ScriptableEntity() = default;
        template<typename T>
        T& GetComponent()
        {
            return _entity.GetComponent<T>();
        }

    protected:
        virtual void OnCreate() {}
        virtual void OnDestroy() {}
        virtual void OnUpdate(float deltaTime) {}
        Entity _entity;

    private:
        friend class Scene::Scene;
    };
}

#endif //SCRIPTABLEENTITY_HPP
