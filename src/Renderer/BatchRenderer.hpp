#ifndef BATCH_RENDERER_HPP
#define BATCH_RENDERER_HPP

#include "Core/Camera.hpp"
#include "ECS/Entity.hpp"

#include <vector>

namespace Renderer {
    class BatchRenderer
    {
    public:
        static void DrawBatch(const std::vector<ECS::Entity>& entities, const Core::Camera& camera, const ECS::Entity& lightEntity);
    };
}

#endif //BATCH_RENDERER_HPP
