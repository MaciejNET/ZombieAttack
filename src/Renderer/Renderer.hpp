#ifndef RENDERER_HPP
#define RENDERER_HPP
#include "Core/Camera.hpp"
#include "ECS/Entity.hpp"

namespace Renderer {
    class Renderer
    {
    public:
        Renderer() = default;

        static void Draw(const ECS::Entity& entity, const Core::Camera& camera, const ECS::Entity& lightEntity);
    };
}

#endif //RENDERER_HPP
