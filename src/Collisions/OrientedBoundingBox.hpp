#ifndef ORIENTEDBOUNDINGBOX_HPP
#define ORIENTEDBOUNDINGBOX_HPP

#include <vector>
#include <glm/glm.hpp>

#include "Core/Mesh.hpp"

namespace Collisions {
    struct OrientedBoundingBox
    {
        glm::vec3 Center;
        glm::vec3 HalfExtents;
        glm::mat3 Orientation;
    };

    OrientedBoundingBox ComputeOrientedBoundingBox(const std::vector<std::shared_ptr<Core::Mesh>> &meshes, const glm::mat4& transform);
    bool AreOBBsOverlapping(const OrientedBoundingBox& a, const OrientedBoundingBox& b);
    bool IsOverlappingOnAxis(const OrientedBoundingBox& a, const OrientedBoundingBox& b, const glm::vec3& axis);
    void ProjectOntoAxis(const OrientedBoundingBox& obb, const glm::vec3& axis, float& min, float& max);
}

#endif //ORIENTEDBOUNDINGBOX_HPP
