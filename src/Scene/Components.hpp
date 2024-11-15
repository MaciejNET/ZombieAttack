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
            auto entityBoundingBox = ComputeBoundingBox(mesh, transform);
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

                auto collidableBoundingBox = ComputeBoundingBox(collidableMesh, collidableTransform);

                if (AreBoundingBoxesOverlapping(entityBoundingBox, collidableBoundingBox))
                {
                    return collidableEntity;
                }
            }

            return nullptr;
        }

    private:
        struct BoundingBox
        {
            glm::vec3 Min;
            glm::vec3 Max;
        };

        BoundingBox ComputeBoundingBox(const Core::Mesh& mesh, const glm::mat4& transform)
        {
            auto vertices = mesh.GetVertices();

            glm::vec3 minBounds = glm::vec3(std::numeric_limits<float>::max());
            glm::vec3 maxBounds = glm::vec3(std::numeric_limits<float>::lowest());

            for (const auto& vertex : vertices)
            {
                glm::vec3 worldPosition = glm::vec3(transform * glm::vec4(vertex.Position, 1.0f));
                minBounds = glm::min(minBounds, worldPosition);
                maxBounds = glm::max(maxBounds, worldPosition);
            }

            return BoundingBox{minBounds, maxBounds};
        }

        bool AreBoundingBoxesOverlapping(const BoundingBox& a, const BoundingBox& b)
        {
            return (a.Max.x >= b.Min.x && a.Min.x <= b.Max.x) &&
                   (a.Max.y >= b.Min.y && a.Min.y <= b.Max.y) &&
                   (a.Max.z >= b.Min.z && a.Min.z <= b.Max.z);
        }
    };
}

#endif //COMPONENTS_HPP
