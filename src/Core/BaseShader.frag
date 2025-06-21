#version 410 core

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
out vec4 FragColor;

in vec3 Normal;
in vec3 currentPos;
in vec4 color;

void main()
{
    float ambient = 0.2f;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - currentPos);

    float diff = max(dot(norm, lightDir), 0.0);

    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - currentPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    if (spec > 0.5)
        spec = 1.0;
    else
        spec = 0.0;

    float specular = specularStrength * spec;

    FragColor = color * lightColor * (ambient + diff + specular);
}
