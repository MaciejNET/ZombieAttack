#include "Mesh.hpp"

#include "Macros.hpp"
#include <glm/glm.hpp>

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

    void Mesh::Draw(const Shader& shader, const std::vector<std::function<void(const Shader&)>>& setFunctions, bool bindShader) const
    {
        if (bindShader)
        {
            shader.Use();
        }
        _vao.Bind();
        for (const auto& setFunction : setFunctions) {
            setFunction(shader);
        }
        glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, nullptr);
        _vao.Unbind();
    }

    void Mesh::DrawInstanced(const Shader& shader,
                             const std::vector<std::function<void(const Shader&)>>& setFunctions,
                             const std::vector<glm::mat4>& models,
                             const std::vector<glm::vec4>& colors,
                             const bool bindShader) const
    {
        ZA_ASSERT(models.size() == colors.size(), "Models and colors size mismatch");

        if (bindShader)
        {
            shader.Use();
        }

        _vao.Bind();

        GLuint buffers[2];
        glGenBuffers(2, buffers);

        glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
        glBufferData(GL_ARRAY_BUFFER, models.size() * sizeof(glm::mat4), models.data(), GL_DYNAMIC_DRAW);
        for (unsigned int i = 0; i < 4; ++i)
        {
            glVertexAttribPointer(2 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), reinterpret_cast<void*>(sizeof(glm::vec4) * i));
            glEnableVertexAttribArray(2 + i);
            glVertexAttribDivisor(2 + i, 1);
        }

        glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
        glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec4), colors.data(), GL_DYNAMIC_DRAW);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), nullptr);
        glEnableVertexAttribArray(6);
        glVertexAttribDivisor(6, 1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        for (const auto& setFunction : setFunctions)
        {
            setFunction(shader);
        }

        glDrawElementsInstanced(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, nullptr, models.size());

        glDeleteBuffers(2, buffers);

        _vao.Unbind();
    }

    VAO Mesh::GetVAO() const
    {
        return _vao;
    }

}
