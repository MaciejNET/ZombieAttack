#pragma once

#ifndef VBO_HPP
#define VBO_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

namespace Core {
    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec3 Color;
    };

    class VBO
    {
    public:
        explicit VBO(const std::vector<Vertex> &vertices);
        ~VBO();
        void Bind() const;
        void Unbind() const;
        void BufferData(const std::vector<Vertex> &vertices) const;
        void Delete() const;

    private:
        GLuint _id{};
    };
}

#endif //VBO_HPP
