#include "VBO.hpp"

#include "Macros.hpp"

namespace Core {
    VBO::VBO(const std::vector<Vertex> &vertices)
    {
        glGenBuffers(1, &_id);
        Bind();
        BufferData(vertices);
    }

    VBO::~VBO()
    {
        glDeleteBuffers(1, &_id);
    }

    void VBO::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, _id);
    }

    void VBO::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VBO::BufferData(const std::vector<Vertex> &vertices) const
    {
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    }

    void VBO::Delete() const
    {
        glDeleteBuffers(1, &_id);
    }
}
