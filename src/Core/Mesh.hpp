#pragma once

#ifndef MESH_HPP
#define MESH_HPP
#include <functional>

#include "EBO.hpp"
#include "Shader.hpp"
#include "VAO.hpp"

namespace Core {
    class Mesh
    {
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
        ~Mesh();
        void Draw(const Shader& shader, const std::vector<std::function<void(const Shader&)>>& setFunctions) const;
        VAO GetVAO() const;

    private:
        VAO _vao;
        VBO _vbo;
        EBO _ebo;
        std::vector<Vertex> _vertices;
        std::vector<unsigned int> _indices;
    };
}

#endif //MESH_HPP
