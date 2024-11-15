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
                    {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}},
                    {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}},
                    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}},
                    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}},
                    {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}},
                    {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}},

                    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}},
                    {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}},
                    {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}},
                    {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}},
                    {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}},
                    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}},

                    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},
                    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
                    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
                    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
                    {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},
                    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},

                    {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}},
                    {{-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}},
                    {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}},
                    {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}},
                    {{-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}},
                    {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}},

                    {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
                    {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
                    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}},
                    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}},
                    {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}},
                    {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},

                    {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}},
                    {{ 0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}},
                    {{ 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}},
                    {{ 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}},
                    {{-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}},
                    {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}}
                },
                // Indices
                {
                    0, 1, 2,
                    3, 4, 5,

                    6, 7, 8,
                    9, 10, 11,

                    12, 13, 14,
                    15, 16, 17,

                    18, 19, 20,
                    21, 22, 23,

                    24, 25, 26,
                    27, 28, 29,

                    30, 31, 32,
                    33, 34, 35
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