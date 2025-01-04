#include "Scene.hpp"
#include "Components.hpp"
#include <ranges>
#include <cassert>

#include "Core/Macros.hpp"
#include "ECS/IdGenerator.h"
#include "Events/EventBus.hpp"
#include "ECS/Entity.hpp"
#include "Renderer/Renderer.hpp"

namespace Scene {
    ECS::Entity Scene::AddEntity()
    {
        auto id = ECS::IdGenerator::GetNextId();
        _entities.push_back(id);
        return {id, this};
    }

    std::vector<ECS::Entity> Scene::GetEntities()
    {
        std::vector<ECS::Entity> entities;
        for (const auto& entityId : _entities)
        {
            entities.emplace_back(entityId, this);
        }
        return entities;
    }

    void Scene::OnUpdate(const float deltaTime)
    {
        for (const auto& entityId : _entities)
        {
            ECS::Entity entity(entityId, this);
            if (entity.HasComponent<CollisionComponent>())
            {
                entity.GetComponent<CollisionComponent>().UpdateBoundingBox(entity);
            }
            if (entity.HasComponent<ScriptableComponent>())
            {
                auto& scriptableEntity = entity.GetComponent<ScriptableComponent>();
                if (!scriptableEntity.Instance)
                {
                    scriptableEntity.Instance = scriptableEntity.InstantiateScript();
                    scriptableEntity.Instance->_entity = entity;
                    scriptableEntity.Instance->OnCreate();
                }

                scriptableEntity.Instance->OnUpdate(deltaTime);
            }
        }

        auto cameras = _entities | std::ranges::views::filter([this](const int entityId) {
            return _componentManager.HasComponent<CameraComponent>(entityId);
        });

        ZA_ASSERT(std::ranges::any_of(cameras, [this](const int entityId) {
            return _componentManager.GetComponent<CameraComponent>(entityId).Primary;
        }), "No primary camera found.");

        ZA_ASSERT(std::ranges::count_if(cameras, [this](const int entityId) {
            return _componentManager.GetComponent<CameraComponent>(entityId).Primary;
        }) == 1, "More than one primary camera found.");

        auto mainCameraIt = std::ranges::find_if(cameras, [this](const int entityId) {
            return _componentManager.GetComponent<CameraComponent>(entityId).Primary;
        });

        const ECS::Entity* mainCamera = (mainCameraIt != cameras.end()) ? new ECS::Entity(*mainCameraIt, this) : nullptr;
        ZA_ASSERT(mainCamera, "No primary camera found.");
        const auto& camera = mainCamera->GetComponent<CameraComponent>().Camera;

        const auto firstLightIt = std::ranges::find_if(_entities, [this](const int entityId) {
            return _componentManager.HasComponent<LightComponent>(entityId);
        });

        if (firstLightIt == std::ranges::end(_entities))
        {
            throw std::runtime_error("No light found.");
        }

        int firstLight = *firstLightIt;
        const ECS::Entity mainLight(firstLight, this);
        for (const auto& entityId : _entities)
        {
            ECS::Entity entity(entityId, this);
            Renderer::Renderer::Draw(entity, camera, mainLight);
        }
    }

    void Scene::RemoveEntity(const int id)
    {
        if (std::ranges::find(_entities, id) == _entities.end())
        {
            return;
        }
        const auto entity = ECS::Entity(id, this);
        if (entity.HasComponent<ScriptableComponent>())
        {
            auto& scriptableEntity = entity.GetComponent<ScriptableComponent>();
            scriptableEntity.Instance->OnDestroy();
            scriptableEntity.DestroyScript(scriptableEntity.Instance);
        }
        std::erase(_entities, id);
        _componentManager.RemoveAllComponents(id);
    }
}
