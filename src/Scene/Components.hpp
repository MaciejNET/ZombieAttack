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
        Core::Mesh Mesh;
        Core::Shader Shader;

        MeshComponent() = delete;
        MeshComponent(const MeshComponent&) = default;

        explicit MeshComponent(const Core::Mesh& mesh, const Core::Shader& shader) : Mesh(mesh), Shader(shader) {}
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
        ECS::Entity* CollisionDetection(ECS::Entity* entity)
        {
            auto scene = entity->GetScene();
            auto& transform = entity->GetComponent<TransformComponent>().Transform;
            auto& mesh = entity->GetComponent<MeshComponent>().Mesh;
            auto entityBoundingBox = ComputeOrientedBoundingBox(mesh, transform);
            auto entities = scene->GetEntities();
            auto collidableEntities = entities | std::views::filter([](const ECS::Entity* entity) {
                return entity->HasComponent<CollisionComponent>();
            });
            for (const auto& collidableEntity : collidableEntities)
            {
                if (collidableEntity == entity)
                {
                    continue;
                }
                auto& collidableTransform = collidableEntity->GetComponent<TransformComponent>().Transform;
                auto& collidableMesh = collidableEntity->GetComponent<MeshComponent>().Mesh;

                auto collidableBoundingBox = ComputeOrientedBoundingBox(collidableMesh, collidableTransform);

                if (AreOBBsOverlapping(entityBoundingBox, collidableBoundingBox))
                {
                    return collidableEntity;
                }
            }

            return nullptr;
        }

    private:
        struct OrientedBoundingBox
        {
            glm::vec3 Center;
            glm::vec3 HalfExtents;
            glm::mat3 Orientation;
        };

        OrientedBoundingBox ComputeOrientedBoundingBox(const Core::Mesh& mesh, const glm::mat4& transform)
        {
            glm::mat3 rotationMatrix = glm::mat3(transform);

            glm::vec3 minBounds = glm::vec3(std::numeric_limits<float>::max());
            glm::vec3 maxBounds = glm::vec3(std::numeric_limits<float>::lowest());

            for (const auto& vertex : mesh.GetVertices())
            {
                minBounds = glm::min(minBounds, vertex.Position);
                maxBounds = glm::max(maxBounds, vertex.Position);
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
