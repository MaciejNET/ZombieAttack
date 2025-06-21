#include "BatchRenderer.hpp"

#include "Scene/Components.hpp"
#include "Core/Macros.hpp"

#include <algorithm>
#include <glm/glm.hpp>

namespace Renderer {
    void BatchRenderer::DrawBatch(const std::vector<ECS::Entity>& entities, const Core::Camera& camera, const ECS::Entity& lightEntity)
    {
        ZA_ASSERT(lightEntity.HasComponent<Scene::LightComponent>(), "Light entity must have a LightComponent");

        std::vector<ECS::Entity> drawable;
        drawable.reserve(entities.size());
        for (const auto& entity : entities)
        {
            if (entity.HasComponent<Scene::TransformComponent>() &&
                (entity.HasComponent<Scene::MeshComponent>() || entity.HasComponent<Scene::ModelComponent>()) &&
                entity.HasComponent<Scene::SpriteRendererComponent>())
            {
                drawable.push_back(entity);
            }
        }

        std::sort(drawable.begin(), drawable.end(), [](const ECS::Entity& a, const ECS::Entity& b){
            const Core::Shader* shaderA = nullptr;
            const Core::Shader* shaderB = nullptr;
            if (a.HasComponent<Scene::MeshComponent>())
                shaderA = a.GetComponent<Scene::MeshComponent>().Shader.get();
            else if (a.HasComponent<Scene::ModelComponent>())
                shaderA = a.GetComponent<Scene::ModelComponent>().Shader.get();
            if (b.HasComponent<Scene::MeshComponent>())
                shaderB = b.GetComponent<Scene::MeshComponent>().Shader.get();
            else if (b.HasComponent<Scene::ModelComponent>())
                shaderB = b.GetComponent<Scene::ModelComponent>().Shader.get();
            if (shaderA == shaderB)
            {
                const void* meshA = nullptr;
                const void* meshB = nullptr;
                if (a.HasComponent<Scene::MeshComponent>())
                    meshA = a.GetComponent<Scene::MeshComponent>().Mesh.get();
                if (b.HasComponent<Scene::MeshComponent>())
                    meshB = b.GetComponent<Scene::MeshComponent>().Mesh.get();
                return meshA < meshB;
            }
            return shaderA < shaderB;
        });

        const auto& light = lightEntity.GetComponent<Scene::LightComponent>();
        Core::Shader* currentShader = nullptr;

        size_t index = 0;
        while (index < drawable.size())
        {
            const auto& entity = drawable[index];
            bool hasMesh = entity.HasComponent<Scene::MeshComponent>();
            std::shared_ptr<Core::Shader> shader;
            std::shared_ptr<Core::Mesh> mesh;
            std::shared_ptr<Core::Model> model;
            if (hasMesh)
            {
                const auto& comp = entity.GetComponent<Scene::MeshComponent>();
                shader = comp.Shader;
                mesh = comp.Mesh;
            }
            else
            {
                const auto& comp = entity.GetComponent<Scene::ModelComponent>();
                shader = comp.Shader;
                model = comp.Model;
            }

            if (shader.get() != currentShader)
            {
                currentShader = shader.get();
                currentShader->Use();
            }

            const std::vector<std::function<void(const Core::Shader&)>> setFunctions = {
                [&](const Core::Shader& s) { s.SetMat4("view", camera.GetViewMatrix()); },
                [&](const Core::Shader& s) { s.SetMat4("projection", camera.GetProjectionMatrix()); },
                [&](const Core::Shader& s) { s.SetVec4("lightColor", light.Color); },
                [&](const Core::Shader& s) { s.SetVec3("lightPos", light.Position); },
                [&](const Core::Shader& s) { s.SetVec3("viewPos", camera.GetPosition()); }
            };

            if (hasMesh)
            {
                std::vector<glm::mat4> models;
                std::vector<glm::vec4> colors;
                size_t j = index;
                while (j < drawable.size())
                {
                    const auto& other = drawable[j];
                    if (other.HasComponent<Scene::MeshComponent>() &&
                        other.GetComponent<Scene::MeshComponent>().Shader == shader &&
                        other.GetComponent<Scene::MeshComponent>().Mesh == mesh)
                    {
                        models.push_back(other.GetComponent<Scene::TransformComponent>().Transform);
                        colors.push_back(other.GetComponent<Scene::SpriteRendererComponent>().Color);
                        ++j;
                    }
                    else
                    {
                        break;
                    }
                }
                mesh->DrawInstanced(*shader, setFunctions, models, colors, false);
                index = j;
            }
            else
            {
                const auto& transform = entity.GetComponent<Scene::TransformComponent>();
                const auto& spriteRenderer = entity.GetComponent<Scene::SpriteRendererComponent>();
                model->DrawInstanced(*shader, setFunctions, { transform.Transform }, { spriteRenderer.Color }, false);
                ++index;
            }
        }
    }
}
