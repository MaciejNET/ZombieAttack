#pragma once

#ifndef BASESHAPES_HPP
#define BASESHAPES_HPP
#include <vector>

#include "VBO.hpp"

namespace Core {
    struct Shape
    {
        std::vector<Vertex> Vertices;
        std::vector<unsigned int> Indices;
    };

    class BaseShapes
    {
    public:
        static Shape Cube()
        {
            return {
                // Vertices
                {
                    // Positions                // Normals       // Colors
                    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f, 0.0f}},  // Bottom-left
                    {{ 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f}},  // Bottom-right
                    {{ 1.0f,  1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},  // Top-right
                    {{-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},  // Top-left
                    {{-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f,  1.0f}, {1.0f, 0.0f, 1.0f}},  // Bottom-left (front)
                    {{ 1.0f, -1.0f,  1.0f}, {0.0f, 0.0f,  1.0f}, {0.0f, 1.0f, 1.0f}},  // Bottom-right (front)
                    {{ 1.0f,  1.0f,  1.0f}, {0.0f, 0.0f,  1.0f}, {1.0f, 1.0f, 1.0f}},  // Top-right (front)
                    {{-1.0f,  1.0f,  1.0f}, {0.0f, 0.0f,  1.0f}, {0.5f, 0.5f, 0.5f}}   // Top-left (front)
                },
                // Indices
                {
                    0, 1, 2, 2, 3, 0,  // Back face
                    4, 5, 6, 6, 7, 4,  // Front face
                    0, 1, 5, 5, 4, 0,  // Bottom face
                    2, 3, 7, 7, 6, 2,  // Top face
                    0, 3, 7, 7, 4, 0,  // Left face
                    1, 2, 6, 6, 5, 1   // Right face
                }
            };
        }

        static Shape Sphere()
        {
            // Simplified sphere with minimal vertices and indices for demonstration
            return {
                // Vertices
                {
                    // Positions                // Normals       // Colors
                    {{ 0.0f,  0.0f,  1.0f}, {0.0f,  0.0f,  1.0f}, {1.0f, 0.0f, 0.0f}},  // Top
                    {{ 0.0f,  1.0f,  0.0f}, {0.0f,  1.0f,  0.0f}, {0.0f, 1.0f, 0.0f}},  // Front
                    {{ 1.0f,  0.0f,  0.0f}, {1.0f,  0.0f,  0.0f}, {0.0f, 0.0f, 1.0f}},  // Right
                    {{ 0.0f, -1.0f,  0.0f}, {0.0f, -1.0f,  0.0f}, {1.0f, 1.0f, 0.0f}},  // Back
                    {{-1.0f,  0.0f,  0.0f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 1.0f}},  // Left
                    {{ 0.0f,  0.0f, -1.0f}, {0.0f,  0.0f, -1.0f}, {0.0f, 1.0f, 1.0f}}   // Bottom
                },
                // Indices
                {
                    0, 1, 2,  // Top front-right
                    0, 2, 3,  // Top right-back
                    0, 3, 4,  // Top back-left
                    0, 4, 1,  // Top left-front
                    5, 1, 2,  // Bottom front-right
                    5, 2, 3,  // Bottom right-back
                    5, 3, 4,  // Bottom back-left
                    5, 4, 1   // Bottom left-front
                }
            };
        }
    };
}

#endif //BASESHAPES_HPP