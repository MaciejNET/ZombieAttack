#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in mat4 instanceModel;
layout(location = 6) in vec4 instanceColor;

uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 currentPos;
out vec4 color;

void main()
{
    currentPos = vec3(instanceModel * vec4(position, 1.0));
    gl_Position = projection * view * instanceModel * vec4(position, 1.0);
    Normal = mat3(transpose(inverse(instanceModel))) * normal;
    color = instanceColor;
}