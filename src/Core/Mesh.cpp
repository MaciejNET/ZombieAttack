#include "Mesh.hpp"

#include "Macros.hpp"

namespace Core {
    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
        : _vertices(std::move(vertices)), _indices(std::move(indices)), _vao(), _vbo(_vertices), _ebo(_indices)
    {
         _vao.Bind();
         _vbo.Bind();
         _vbo.BufferData(_vertices);
         _ebo.Bind();
         _ebo.BufferData(_indices);
         _vao.LinkAttrib(_vbo, 0, 3, GL_FLOAT, sizeof(Vertex), nullptr);
         _vao.LinkAttrib(_vbo, 1, 3, GL_FLOAT, sizeof(Vertex), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
         _vao.Unbind();
         _vbo.Unbind();
         _ebo.Unbind();
    }

    Mesh::~Mesh()
    {
        _vao.Delete();
        _vbo.Delete();
        _ebo.Delete();
    }

    void Mesh::Draw(const Shader& shader, const std::vector<std::function<void(const Shader&)>>& setFunctions) const
    {
        shader.Use();
        _vao.Bind();
        for (const auto& setFunction : setFunctions) {
            setFunction(shader);
        }
        glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, nullptr);
        _vao.Unbind();
    }

    VAO Mesh::GetVAO() const
    {
        return _vao;
    }

}
