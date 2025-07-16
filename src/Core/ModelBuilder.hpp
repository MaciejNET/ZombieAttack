#pragma once

#ifndef MODELBUILDER_HPP
#define MODELBUILDER_HPP

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Model.hpp"
#include "BaseShapes.hpp"

namespace Core {
    struct MeshTransform
    {
        Shape Shape;
        glm::mat4 Transform{1.0f};
    };

    class ModelBuilder
    {
    public:
        static std::shared_ptr<Model> FromShapes(const std::vector<MeshTransform>& parts)
        {
            std::vector<Vertex> vertices;
            std::vector<unsigned int> indices;
            unsigned int indexOffset = 0;

            for (const auto& part : parts)
            {
                for (const auto& vertex : part.Shape.Vertices)
                {
                    glm::vec3 pos = glm::vec3(part.Transform * glm::vec4(vertex.Position, 1.0f));
                    glm::vec3 normal = glm::normalize(glm::mat3(part.Transform) * vertex.Normal);
                    vertices.push_back({ pos, normal });
                }

                for (auto idx : part.Shape.Indices)
                {
                    indices.push_back(idx + indexOffset);
                }
                indexOffset += part.Shape.Vertices.size();
            }

            auto mesh = std::make_shared<Mesh>(vertices, indices);
            return std::make_shared<Model>(std::vector<std::shared_ptr<Mesh>>{ mesh });
        }
    };
}

#endif //MODELBUILDER_HPP

