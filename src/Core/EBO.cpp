#include "EBO.hpp"

#include <glad/glad.h>

namespace Core {
    EBO::EBO(const std::vector<unsigned int> &indices)
    {
        glGenBuffers(1, &_id);
        Bind();
        BufferData(indices);
    }

    EBO::~EBO()
    {
        glDeleteBuffers(1, &_id);
    }

    void EBO::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
    }

    void EBO::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void EBO::BufferData(const std::vector<unsigned int> &indices) const
    {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    }

    void EBO::Delete() const
    {
        glDeleteBuffers(1, &_id);
    }
}
