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
                    // Front face
                    {{-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f, 1.0f}},
                    {{ 1.0f, -1.0f,  1.0f}, {0.0f, 0.0f, 1.0f}},
                    {{ 1.0f,  1.0f,  1.0f}, {0.0f, 0.0f, 1.0f}},
                    {{-1.0f,  1.0f,  1.0f}, {0.0f, 0.0f, 1.0f}},

                    // Back face
                    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}},
                    {{ 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}},
                    {{ 1.0f,  1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}},
                    {{-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}},

                    // Left face
                    {{-1.0f, -1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}},
                    {{-1.0f, -1.0f,  1.0f}, {-1.0f, 0.0f, 0.0f}},
                    {{-1.0f,  1.0f,  1.0f}, {-1.0f, 0.0f, 0.0f}},
                    {{-1.0f,  1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}},

                    // Right face
                    {{ 1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}},
                    {{ 1.0f, -1.0f,  1.0f}, {1.0f, 0.0f, 0.0f}},
                    {{ 1.0f,  1.0f,  1.0f}, {1.0f, 0.0f, 0.0f}},
                    {{ 1.0f,  1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}},

                    // Top face
                    {{-1.0f,  1.0f,  1.0f}, {0.0f, 1.0f, 0.0f}},
                    {{ 1.0f,  1.0f,  1.0f}, {0.0f, 1.0f, 0.0f}},
                    {{ 1.0f,  1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}},
                    {{-1.0f,  1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}},

                    // Bottom face
                    {{-1.0f, -1.0f,  1.0f}, {0.0f, -1.0f, 0.0f}},
                    {{ 1.0f, -1.0f,  1.0f}, {0.0f, -1.0f, 0.0f}},
                    {{ 1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}},
                    {{-1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}}
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
                    {{ 0.0f,  0.0f,  1.0f}, {0.0f,  0.0f,  1.0f}},  // Top
                    {{ 0.0f,  1.0f,  0.0f}, {0.0f,  1.0f,  0.0f}},  // Front
                    {{ 1.0f,  0.0f,  0.0f}, {1.0f,  0.0f,  0.0f}},  // Right
                    {{ 0.0f, -1.0f,  0.0f}, {0.0f, -1.0f,  0.0f}},  // Back
                    {{-1.0f,  0.0f,  0.0f}, {-1.0f,  0.0f,  0.0f}},  // Left
                    {{ 0.0f,  0.0f, -1.0f}, {0.0f,  0.0f, -1.0f}}   // Bottom
                },
                // Indices
                {
                    0, 1, 2, 2, 3, 0,         // Front face
                    4, 5, 6, 6, 7, 4,         // Back face
                    8, 9, 10, 10, 11, 8,      // Left face
                    12, 13, 14, 14, 15, 12,   // Right face
                    16, 17, 18, 18, 19, 16,   // Top face
                    20, 21, 22, 22, 23, 20    // Bottom face
                }
            };
        }
    };
}

#endif //BASESHAPES_HPP