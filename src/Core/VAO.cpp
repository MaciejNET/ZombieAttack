//
// Created by Maciej Deroń on 11/10/2024.
//

#include "VAO.hpp"

namespace Core {
    VAO::VAO()
    {
        glGenVertexArrays(1, &_id);
    }

    VAO::~VAO()
    {
        glDeleteVertexArrays(1, &_id);
    }

    void VAO::LinkVBO(const VBO &VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset) const
    {
        VBO.Bind();
        glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(layout);
        VBO.Unbind();
    }
    void VAO::Bind() const
    {
        glBindVertexArray(_id);
    }

    void VAO::Unbind() const
    {
        glBindVertexArray(0);
    }

    void VAO::Delete() const
    {
        glDeleteVertexArrays(1, &_id);
    }
}