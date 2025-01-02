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
        CollisionComponent() = default;
        CollisionComponent(const CollisionComponent&) = default;
        ECS::Entity CollisionDetection(ECS::Entity entity)
        {
            auto scene = entity.GetScene();
            auto& transform = entity.GetComponent<TransformComponent>().Transform;
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
            auto entityBoundingBox = ComputeOrientedBoundingBox(meshes, transform);
            auto entities = scene->GetEntities();
            auto collidableEntities = entities | std::views::filter([scene](const ECS::Entity& entity) {
                return scene->GetComponentManager().HasComponent<CollisionComponent>(entity.GetId());
            });

            for (const auto& collidableEntity : collidableEntities)
            {
                if (collidableEntity.GetId() == entity.GetId())
                {
                    continue;
                }
                auto& collidableTransform = collidableEntity.GetComponent<TransformComponent>().Transform;
                std::vector<std::shared_ptr<Core::Mesh>> collidableMeshes;
                if (collidableEntity.HasComponent<MeshComponent>())
                {
                    collidableMeshes.push_back(collidableEntity.GetComponent<MeshComponent>().Mesh);
                }
                if (collidableEntity.HasComponent<ModelComponent>())
                {
                    for (const auto& mesh : collidableEntity.GetComponent<ModelComponent>().Model->GetMeshes())
                    {
                        collidableMeshes.push_back(mesh);
                    }
                }

                auto collidableBoundingBox = ComputeOrientedBoundingBox(collidableMeshes, collidableTransform);

                if (AreOBBsOverlapping(entityBoundingBox, collidableBoundingBox))
                {
                    return collidableEntity;
                }
            }

            return {-1, nullptr};
        }

    private:
        struct OrientedBoundingBox
        {
            glm::vec3 Center;
            glm::vec3 HalfExtents;
            glm::mat3 Orientation;
        };

        OrientedBoundingBox ComputeOrientedBoundingBox(std::vector<std::shared_ptr<Core::Mesh>> meshes, const glm::mat4& transform)
        {
            glm::mat3 rotationMatrix = glm::mat3(transform);

            glm::vec3 minBounds = glm::vec3(std::numeric_limits<float>::max());
            glm::vec3 maxBounds = glm::vec3(std::numeric_limits<float>::lowest());

            for (const auto& mesh : meshes)
            {
                for (const auto& vertex : mesh->GetVertices())
                {
                    minBounds = glm::min(minBounds, vertex.Position);
                    maxBounds = glm::max(maxBounds, vertex.Position);
                }
            }

            glm::vec3 center = (minBounds + maxBounds) * 0.5f;
            glm::vec3 halfExtents = (maxBounds - minBounds) * 0.5f;

            return OrientedBoundingBox {
                transform * glm::vec4(center, 1.0f),
                halfExtents,
                rotationMatrix
            };
        }

        bool AreOBBsOverlapping(const OrientedBoundingBox& a, const OrientedBoundingBox& b) {
            glm::vec3 axes[15];
            int axisCount = 0;

            for (int i = 0; i < 3; ++i) {
                axes[axisCount++] = a.Orientation[i];
                axes[axisCount++] = b.Orientation[i];
            }

            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    axes[axisCount++] = glm::cross(a.Orientation[i], b.Orientation[j]);
                }
            }

            for (int i = 0; i < axisCount; ++i) {
                if (!IsOverlappingOnAxis(a, b, axes[i])) {
                    return false;
                }
            }

            return true;
        }

        bool IsOverlappingOnAxis(const OrientedBoundingBox& a, const OrientedBoundingBox& b, const glm::vec3& axis)
        {
            float aMin, aMax, bMin, bMax;
            ProjectOntoAxis(a, axis, aMin, aMax);
            ProjectOntoAxis(b, axis, bMin, bMax);

            return aMax >= bMin && bMax >= aMin;
        }

        void ProjectOntoAxis(const OrientedBoundingBox& obb, const glm::vec3& axis, float& min, float& max)
        {
            glm::vec3 corners[8] = {
                obb.Center + obb.Orientation[0] * obb.HalfExtents.x +
                             obb.Orientation[1] * obb.HalfExtents.y +
                             obb.Orientation[2] * obb.HalfExtents.z,

                obb.Center + obb.Orientation[0] * obb.HalfExtents.x +
                             obb.Orientation[1] * obb.HalfExtents.y -
                             obb.Orientation[2] * obb.HalfExtents.z,

                obb.Center + obb.Orientation[0] * obb.HalfExtents.x -
                             obb.Orientation[1] * obb.HalfExtents.y +
                             obb.Orientation[2] * obb.HalfExtents.z,

                obb.Center + obb.Orientation[0] * obb.HalfExtents.x -
                             obb.Orientation[1] * obb.HalfExtents.y -
                             obb.Orientation[2] * obb.HalfExtents.z,

                obb.Center - obb.Orientation[0] * obb.HalfExtents.x +
                             obb.Orientation[1] * obb.HalfExtents.y +
                             obb.Orientation[2] * obb.HalfExtents.z,

                obb.Center - obb.Orientation[0] * obb.HalfExtents.x +
                             obb.Orientation[1] * obb.HalfExtents.y -
                             obb.Orientation[2] * obb.HalfExtents.z,

                obb.Center - obb.Orientation[0] * obb.HalfExtents.x -
                             obb.Orientation[1] * obb.HalfExtents.y +
                             obb.Orientation[2] * obb.HalfExtents.z,

                obb.Center - obb.Orientation[0] * obb.HalfExtents.x -
                             obb.Orientation[1] * obb.HalfExtents.y -
                             obb.Orientation[2] * obb.HalfExtents.z
            };

            min = max = glm::dot(corners[0], axis);
            for (int i = 1; i < 8; ++i)
            {
                float projection = glm::dot(corners[i], axis);
                min = glm::min(min, projection);
                max = glm::max(max, projection);
            }
        }
    };
}

#endif //COMPONENTS_HPP
