#pragma once

#ifndef VAO_HPP
#define VAO_HPP

#include <glad/glad.h>
#include <src/Core/VBO.hpp>

namespace Core {
    class VAO
    {
    public:
        VAO();
        ~VAO();
        void LinkVBO(const VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) const;
        void Bind() const;
        void Unbind() const;
        void Delete() const;
    private:
        GLuint _id{};
    };
}

#endif //VAO_HPP
