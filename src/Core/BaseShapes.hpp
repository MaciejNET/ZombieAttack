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
            const int segments = 36;
            const int rings = 18;
            const float radius = 0.5f;

            std::vector<Vertex> vertices;
            std::vector<unsigned int> indices;

            for (int i = 0; i <= rings; ++i)
            {
                for (int j = 0; j <= segments; ++j)
                {
                    float y = cos((M_PI / rings) * i);
                    float x = cos((2.0f * M_PI / segments) * j) * sin((M_PI / rings) * i);
                    float z = sin((2.0f * M_PI / segments) * j) * sin((M_PI / rings) * i);

                    vertices.push_back({
                        {radius * x, radius * y, radius * z},  // Position
                        {x, y, z}                              // Normal
                    });
                }
            }

            for (int i = 0; i < rings; ++i)
            {
                for (int j = 0; j < segments; ++j)
                {
                    indices.push_back(i * (segments + 1) + j);
                    indices.push_back((i + 1) * (segments + 1) + j);
                    indices.push_back((i + 1) * (segments + 1) + j + 1);

                    indices.push_back(i * (segments + 1) + j);
                    indices.push_back((i + 1) * (segments + 1) + j + 1);
                    indices.push_back(i * (segments + 1) + j + 1);
                }
            }

            return {vertices, indices};
        }
    };
}

#endif //BASESHAPES_HPP