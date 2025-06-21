#include "OrientedBoundingBox.hpp"
#include <memory>

namespace Collisions {
    OrientedBoundingBox ComputeOrientedBoundingBox(const std::vector<std::shared_ptr<Core::Mesh>>& meshes, const glm::mat4& transform)
    {
        glm::mat3 rotationMatrix = glm::mat3(transform);

        glm::vec3 minBounds = glm::vec3(std::numeric_limits<float>::max());
        glm::vec3 maxBounds = glm::vec3(std::numeric_limits<float>::lowest());

        for (const auto& mesh : meshes)
        {
            for (const auto& vertex : mesh->GetVertices())
            {
                minBounds = glm::min(minBounds, vertex.Position);
                maxBounds = glm::max(maxBounds, vertex.Position);
            }
        }

        glm::vec3 center = (minBounds + maxBounds) * 0.5f;
        glm::vec3 halfExtents = (maxBounds - minBounds) * 0.5f;

        return OrientedBoundingBox {
            transform * glm::vec4(center, 1.0f),
            halfExtents,
            rotationMatrix
        };
    }

    bool AreOBBsOverlapping(const OrientedBoundingBox& a, const OrientedBoundingBox& b)
    {
        glm::vec3 axes[15];
        int axisCount = 0;

        for (int i = 0; i < 3; ++i)
        {
            axes[axisCount++] = a.Orientation[i];
            axes[axisCount++] = b.Orientation[i];
        }

        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                axes[axisCount++] = glm::cross(a.Orientation[i], b.Orientation[j]);
            }
        }

        for (int i = 0; i < axisCount; ++i)
        {
            if (!IsOverlappingOnAxis(a, b, axes[i]))
            {
                return false;
            }
        }

        return true;
    }

    bool IsOverlappingOnAxis(const OrientedBoundingBox& a, const OrientedBoundingBox& b, const glm::vec3& axis)
    {
        float aMin, aMax, bMin, bMax;
        ProjectOntoAxis(a, axis, aMin, aMax);
        ProjectOntoAxis(b, axis, bMin, bMax);

        return aMax >= bMin && bMax >= aMin;
    }

    void ProjectOntoAxis(const OrientedBoundingBox& obb, const glm::vec3& axis, float& min, float& max)
        {
            glm::vec3 corners[8] = {
                obb.Center + obb.Orientation[0] * obb.HalfExtents.x +
                             obb.Orientation[1] * obb.HalfExtents.y +
                             obb.Orientation[2] * obb.HalfExtents.z,

                obb.Center + obb.Orientation[0] * obb.HalfExtents.x +
                             obb.Orientation[1] * obb.HalfExtents.y -
                             obb.Orientation[2] * obb.HalfExtents.z,

                obb.Center + obb.Orientation[0] * obb.HalfExtents.x -
                             obb.Orientation[1] * obb.HalfExtents.y +
                             obb.Orientation[2] * obb.HalfExtents.z,

                obb.Center + obb.Orientation[0] * obb.HalfExtents.x -
                             obb.Orientation[1] * obb.HalfExtents.y -
                             obb.Orientation[2] * obb.HalfExtents.z,

                obb.Center - obb.Orientation[0] * obb.HalfExtents.x +
                             obb.Orientation[1] * obb.HalfExtents.y +
                             obb.Orientation[2] * obb.HalfExtents.z,

                obb.Center - obb.Orientation[0] * obb.HalfExtents.x +
                             obb.Orientation[1] * obb.HalfExtents.y -
                             obb.Orientation[2] * obb.HalfExtents.z,

                obb.Center - obb.Orientation[0] * obb.HalfExtents.x -
                             obb.Orientation[1] * obb.HalfExtents.y +
                             obb.Orientation[2] * obb.HalfExtents.z,

                obb.Center - obb.Orientation[0] * obb.HalfExtents.x -
                             obb.Orientation[1] * obb.HalfExtents.y -
                             obb.Orientation[2] * obb.HalfExtents.z
            };

            min = max = glm::dot(corners[0], axis);
            for (int i = 1; i < 8; ++i)
            {
                float projection = glm::dot(corners[i], axis);
                min = glm::min(min, projection);
                max = glm::max(max, projection);
            }
        }
}
