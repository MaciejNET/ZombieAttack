#ifndef RENDERER_HPP
#define RENDERER_HPP
#include "ECS/Entity.hpp"

namespace Renderer {
    class Renderer
    {
    public:
        Renderer() = default;
        void Draw(const ECS::Entity& entity, const ECS::Entity& cameraEntity, const ECS::Entity& lightEntity) const;
        void SetClearColor(float r, float g, float b, float a) const;
        void Clear() const;
    };
}

#endif //RENDERER_HPP
