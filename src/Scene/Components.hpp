#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP
#include <glm/glm.hpp>
#include <ranges>

#include "Core/Camera.hpp"
#include "Core/Mesh.hpp"
#include "ECS/Component.hpp"
#include "ECS/ScriptableEntity.hpp"
#include "ECS/Entity.hpp"
#include "Scene.hpp"
#include "Collisions/OrientedBoundingBox.hpp"
#include "Core/Model.hpp"

namespace Scene {
    struct TransformComponent final : ECS::Component
    {
        glm::mat4 Transform{1.0f};

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;

        explicit TransformComponent(const glm::mat4& transform) : Transform(transform) {}

        explicit operator glm::mat4&() { return Transform; }
        explicit operator const glm::mat4&() const { return Transform; }
    };

    struct SpriteRendererComponent final : ECS::Component
    {
        glm::vec4 Color{1.0f, 1.0f, 1.0f, 1.0f};

        SpriteRendererComponent() = default;
        SpriteRendererComponent(const SpriteRendererComponent&) = default;

        explicit SpriteRendererComponent(const glm::vec4& color) : Color(color) {}

        explicit operator glm::vec4&() { return Color; }
        explicit operator const glm::vec4&() const { return Color; }
    };

    struct CameraComponent final : ECS::Component
    {
        Core::Camera Camera;
        bool Primary{true};

        CameraComponent() = delete;
        CameraComponent(const CameraComponent&) = default;

        explicit CameraComponent(const Core::Camera& camera, bool primary = true) : Camera(camera), Primary(primary) {}
    };

    struct LightComponent final : ECS::Component
    {
        glm::vec4 Color{1.0f, 1.0f, 1.0f, 1.0f};
        glm::vec3 Position{0.0f};
        float Intensity{1.0f};

        LightComponent() = default;
        LightComponent(const LightComponent&) = default;

        explicit LightComponent(const glm::vec4& color, const glm::vec3 position, const float intensity) : Color(color), Position(position), Intensity(intensity) {}

        explicit operator glm::vec4&() { return Color; }
        explicit operator const glm::vec4&() const { return Color; }
    };

    struct MeshComponent final : ECS::Component
    {
        std::shared_ptr<Core::Mesh> Mesh{nullptr};
        std::shared_ptr<Core::Shader> Shader{nullptr};

        MeshComponent() = delete;
        MeshComponent(const MeshComponent&) = default;

        explicit MeshComponent(const std::shared_ptr<Core::Mesh>& mesh, const std::shared_ptr<Core::Shader>& shader)
            : Mesh(mesh), Shader(shader) {}
    };

    struct ModelComponent final : ECS::Component
    {
        std::shared_ptr<Core::Model> Model{nullptr};
        std::shared_ptr<Core::Shader> Shader{nullptr};

        ModelComponent() = delete;
        ModelComponent(const ModelComponent&) = default;

        explicit ModelComponent(const std::shared_ptr<Core::Model>& model, const std::shared_ptr<Core::Shader>& shader) : Model(model), Shader(shader) {}
    };

    struct PlayerComponent final : ECS::Component
    {
        PlayerComponent() = default;
        PlayerComponent(const PlayerComponent&) = default;
    };

    struct ZombieComponent final : ECS::Component
    {
        ZombieComponent() = default;
        ZombieComponent(const ZombieComponent&) = default;
    };

    struct BulletComponent final : ECS::Component
    {
        BulletComponent() = default;
        BulletComponent(const BulletComponent&) = default;
    };

    struct DamageComponent final : ECS::Component
    {
        int Damage{10};

        DamageComponent() = default;
        DamageComponent(const DamageComponent&) = default;

        explicit DamageComponent(const int damage) : Damage(damage) {}
    };

    struct DirectionComponent final : ECS::Component
    {
        glm::vec3 Direction{0.0f};

        DirectionComponent() = default;
        DirectionComponent(const DirectionComponent&) = default;

        explicit DirectionComponent(const glm::vec3& direction) : Direction(direction) {}
    };

    struct HealthComponent final : ECS::Component
    {
        int Health{100};

        HealthComponent() = default;
        HealthComponent(const HealthComponent&) = default;

        explicit HealthComponent(const int health) : Health(health) {}
    };

    struct ScriptableComponent final : ECS::Component
    {
        ECS::ScriptableEntity* Instance{nullptr};
        std::function<ECS::ScriptableEntity*()> InstantiateScript;
        std::function<void(ECS::ScriptableEntity*)> DestroyScript;

        template<typename T>
        void Bind()
        {
            InstantiateScript = []() { return static_cast<ECS::ScriptableEntity*>(new T()); };
            DestroyScript = [](ECS::ScriptableEntity* instance) { delete instance; };
        }
    };

    struct CollisionComponent final : ECS::Component
    {
        CollisionComponent() = delete;
        explicit CollisionComponent(const ECS::Entity entity)
        {
            const auto& transform = entity.GetComponent<TransformComponent>().Transform;
            std::vector<std::shared_ptr<Core::Mesh>> meshes;
            if (entity.HasComponent<MeshComponent>())
            {
                meshes.push_back(entity.GetComponent<MeshComponent>().Mesh);
            }
            if (entity.HasComponent<ModelComponent>())
            {
                for (const auto& mesh : entity.GetComponent<ModelComponent>().Model->GetMeshes())
                {
                    meshes.push_back(mesh);
                }
            }
            BoundingBox = Collisions::ComputeOrientedBoundingBox(meshes, transform);
        }
        CollisionComponent(const CollisionComponent&) = default;
        Collisions::OrientedBoundingBox BoundingBox;

        void UpdateBoundingBox(const ECS::Entity entity)
        {
            const auto& transform = entity.GetComponent<TransformComponent>().Transform;
            std::vector<std::shared_ptr<Core::Mesh>> meshes;
            if (entity.HasComponent<MeshComponent>())
            {
                meshes.push_back(entity.GetComponent<MeshComponent>().Mesh);
            }
            if (entity.HasComponent<ModelComponent>())
            {
                for (const auto& mesh : entity.GetComponent<ModelComponent>().Model->GetMeshes())
                {
                    meshes.push_back(mesh);
                }
            }
            BoundingBox = Collisions::ComputeOrientedBoundingBox(meshes, transform);
        }

        ECS::Entity CollisionDetection(ECS::Entity entity)
        {
            auto scene = entity.GetScene();
            auto entities = scene->GetEntities();
            auto collidableEntities = entities | std::views::filter([scene](const ECS::Entity& e) {
                return scene->GetComponentManager().HasComponent<CollisionComponent>(e.GetId());
            });

            for (const auto& collidableEntity : collidableEntities)
            {
                if (collidableEntity.GetId() == entity.GetId())
                {
                    continue;
                }
                auto collidableBoundingBox = collidableEntity.GetComponent<CollisionComponent>().BoundingBox;

                if (AreOBBsOverlapping(BoundingBox, collidableBoundingBox))
                {
                    return collidableEntity;
                }
            }

            return {-1, nullptr};
        }
    };
}

#endif //COMPONENTS_HPP
