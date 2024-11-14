#pragma once

#ifndef EBO_HPP
#define EBO_HPP
#include <vector>
#include <glad/glad.h>

namespace Core {
    class EBO
    {
    public:
        explicit EBO(const std::vector<unsigned int>& indices);
        ~EBO();
        void Bind() const;
        void Unbind() const;
        void BufferData(const std::vector<unsigned int>& indices) const;
        void Delete() const;
    private:
        GLuint _id{};
    };
}

#endif //EBO_HPP
