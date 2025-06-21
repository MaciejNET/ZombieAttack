#pragma once

#ifndef MESH_HPP
#define MESH_HPP
#include <functional>

#include "EBO.hpp"
#include "Shader.hpp"
#include "VAO.hpp"
#include <glm/glm.hpp>

namespace Core {
    class Mesh
    {
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
        ~Mesh();
        void Draw(const Shader& shader, const std::vector<std::function<void(const Shader&)>>& setFunctions, bool bindShader = true) const;
        void DrawInstanced(const Shader& shader,
                           const std::vector<std::function<void(const Shader&)>>& setFunctions,
                           const std::vector<glm::mat4>& models,
                           const std::vector<glm::vec4>& colors,
                           bool bindShader = true) const;
        VAO GetVAO() const;
        std::vector<Vertex> GetVertices() const { return _vertices; }
        std::vector<unsigned int> GetIndices() const { return _indices; }

    private:
        std::vector<Vertex> _vertices;
        std::vector<unsigned int> _indices;
        VAO _vao;
        VBO _vbo;
        EBO _ebo;
    };
}

#endif //MESH_HPP
