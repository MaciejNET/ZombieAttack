#ifndef RENDERER_HPP
#define RENDERER_HPP
#include "ECS/Entity.hpp"

namespace Renderer {
    class Renderer
    {
    public:
        Renderer() = default;
        void Draw(const ECS::Entity& entity, const ECS::Entity& cameraEntity, const ECS::Entity& lightEntity) const;
    };
}

#endif //RENDERER_HPP
