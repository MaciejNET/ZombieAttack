#include "Renderer.hpp"

#include <glad/glad.h>

#include "Core/Macros.hpp"
#include "Scene/Components.hpp"
#include "Scene/Scene.hpp"

namespace Renderer {
    void Renderer::Draw(const ECS::Entity& entity, const Core::Camera& camera, const ECS::Entity& lightEntity) const
    {
        ZA_ASSERT(lightEntity.HasComponent<Scene::LightComponent>(), "Light entity must have a LightComponent");

        if (entity.HasComponent<Scene::TransformComponent>() &&
            entity.HasComponent<Scene::MeshComponent>() &&
            entity.HasComponent<Scene::SpriteRendererComponent>())
        {
            const auto& transform = entity.GetComponent<Scene::TransformComponent>();
            const auto& mesh = entity.GetComponent<Scene::MeshComponent>();
            const auto& spriteRenderer = entity.GetComponent<Scene::SpriteRendererComponent>();
            const auto& light = lightEntity.GetComponent<Scene::LightComponent>();
            const std::vector<std::function<void(const Core::Shader&)>> setFunctions = {
                [&](const Core::Shader& shader) { shader.SetMat4("view", camera.GetViewMatrix()); },
                [&](const Core::Shader& shader) { shader.SetMat4("projection", camera.GetProjectionMatrix()); },
                [&](const Core::Shader& shader) { shader.SetMat4("model", transform.Transform); },
                [&](const Core::Shader& shader) { shader.SetVec4("spriteColor", spriteRenderer.Color); },
                [&](const Core::Shader& shader) { shader.SetVec4("lightColor", light.Color); },
                [&](const Core::Shader& shader) { shader.SetVec3("lightPos", light.Position); },
                [&](const Core::Shader& shader) { shader.SetVec3("viewPos", camera.GetPosition()); }
            };

            mesh.Mesh.Draw(mesh.Shader, setFunctions);
        }
    }
}
