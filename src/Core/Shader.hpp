#pragma once

#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Core {
    class Shader
    {
    public:
        Shader(const char* vertexPath, const char* fragmentPath);
        ~Shader();
        void Use() const;
        void SetVec3(const char* name, const glm::vec3& value) const;
        void SetVec4(const char* name, const glm::vec4& value) const;
        void SetMat4(const char* name, const glm::mat4& value) const;

    private:
        GLuint _id{};
    };
}

#endif //SHADER_HPP
