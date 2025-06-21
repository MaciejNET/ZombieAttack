#include "Renderer.hpp"

#include <glad/glad.h>

#include "Core/Macros.hpp"
#include "Scene/Components.hpp"


namespace Renderer {
    void Renderer::Draw(const ECS::Entity& entity, const Core::Camera& camera, const ECS::Entity& lightEntity)
    {
        ZA_ASSERT(lightEntity.HasComponent<Scene::LightComponent>(), "Light entity must have a LightComponent");

        if (entity.HasComponent<Scene::TransformComponent>() &&
            (entity.HasComponent<Scene::MeshComponent>() || entity.HasComponent<Scene::ModelComponent>()) &&
            entity.HasComponent<Scene::SpriteRendererComponent>())
        {
            const auto& transform = entity.GetComponent<Scene::TransformComponent>();
            const auto& spriteRenderer = entity.GetComponent<Scene::SpriteRendererComponent>();
            const auto& light = lightEntity.GetComponent<Scene::LightComponent>();
            const std::vector<std::function<void(const Core::Shader&)>> setFunctions = {
                [&](const Core::Shader& shader) { shader.SetMat4("view", camera.GetViewMatrix()); },
                [&](const Core::Shader& shader) { shader.SetMat4("projection", camera.GetProjectionMatrix()); },
                [&](const Core::Shader& shader) { shader.SetVec4("lightColor", light.Color); },
                [&](const Core::Shader& shader) { shader.SetVec3("lightPos", light.Position); },
                [&](const Core::Shader& shader) { shader.SetVec3("viewPos", camera.GetPosition()); }
            };

            if (entity.HasComponent<Scene::MeshComponent>())
            {
                const auto& mesh = entity.GetComponent<Scene::MeshComponent>();
                mesh.Mesh->DrawInstanced(*mesh.Shader, setFunctions, { transform.Transform }, { spriteRenderer.Color });
                return;
            }

            if (entity.HasComponent<Scene::ModelComponent>())
            {
                const auto& model = entity.GetComponent<Scene::ModelComponent>();
                model.Model->DrawInstanced(*model.Shader, setFunctions, { transform.Transform }, { spriteRenderer.Color });
                return;
            }
        }
    }
}
