#include "Scene.hpp"
#include "Components.hpp"
#include <ranges>
#include <cassert>

#include "Core/Macros.hpp"

namespace Scene {
    void Scene::AddEntity(ECS::Entity* entity)
    {
        _entities.push_back(entity);
    }

    void Scene::OnUpdate(const float deltaTime)
    {
        for (auto& entity : _entities)
        {
            if (entity->HasComponent<ScriptableComponent>())
            {
                auto scriptableEntity = entity->GetComponent<ScriptableComponent>();
                if (!scriptableEntity.Instance)
                {
                    scriptableEntity.Instance = scriptableEntity.InstantiateScript();
                    scriptableEntity.Instance->_entity = entity;
                    scriptableEntity.Instance->OnCreate();
                }

                scriptableEntity.Instance->OnUpdate(deltaTime);
            }
        }

        auto cameras = _entities | std::ranges::views::filter([](const ECS::Entity* entity) {
            return entity->HasComponent<CameraComponent>();
        });

        ZA_ASSERT(std::ranges::any_of(cameras, [](const ECS::Entity* entity) {
            return entity->GetComponent<CameraComponent>().Primary;
        }), "No primary camera found.");

        ZA_ASSERT(std::ranges::count_if(cameras, [](const ECS::Entity* entity) {
            return entity->GetComponent<CameraComponent>().Primary;
        }) == 1, "More than one primary camera found.");

        auto mainCameraIt = std::ranges::find_if(cameras, [](const ECS::Entity* entity) {
            return entity->GetComponent<CameraComponent>().Primary;
        });

        ECS::Entity* mainCamera = (mainCameraIt != cameras.end()) ? *mainCameraIt : nullptr;

        auto lights = _entities | std::ranges::views::filter([](const ECS::Entity* entity) {
            return entity->HasComponent<LightComponent>();
        });

        const auto mainLight = lights.front();

        for (const auto& entity : _entities)
        {
            _renderer.Draw(*entity, *mainCamera, *mainLight);
        }
    }

    void Scene::RemoveEntity(ECS::Entity* entity)
    {
        std::erase(_entities, entity);
    }
}
