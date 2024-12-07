#include "Scene.hpp"
#include "Components.hpp"
#include <ranges>
#include <cassert>

#include "Core/Macros.hpp"
#include "Events/EventBus.hpp"

namespace Scene {
    void Scene::AddEntity(const ECS::Entity& entity)
    {
        _entities.push_back(entity);
    }

    void Scene::AddComponent(const unsigned char (&)[16], const ECS::Component &component)
    {

    }

    void Scene::OnUpdate(const float deltaTime)
    {
        for (const auto& entity : _entities)
        {
            if (entity.HasComponent<ScriptableComponent>())
            {
                auto& scriptableEntity = entity->GetComponent<ScriptableComponent>();
                if (!scriptableEntity.Instance)
                {
                    uuid_t id{};
                    uuid_copy(id, entity.GetUUID());
                    scriptableEntity.Instance = scriptableEntity.InstantiateScript();
                    scriptableEntity.Instance->_entity = ECS::Entity(id, this);
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
        ZA_ASSERT(mainCamera, "No primary camera found.");
        auto& camera = mainCamera->GetComponent<CameraComponent>().Camera;

        auto lights = _entities | std::ranges::views::filter([](const ECS::Entity* entity) {
            return entity->HasComponent<LightComponent>();
        });

        const auto mainLight = lights.front();

        for (const auto& entity : _entities)
        {
            _renderer.Draw(*entity, camera, *mainLight);
        }
    }

    void Scene::RemoveEntity(uuid_t id)
    {
        auto entity = _entities | std::ranges::views::filter([id](const ECS::Entity& entity) {
            return uuid_compare(entity.GetUUID(), id);
        });

        //remove entity
    }
}
