#version 410 core

uniform vec4 spriteColor;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
out vec4 FragColor;

in vec3 Normal;
in vec3 currentPos;

void main()
{
    float ambient = 0.2f;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - currentPos);

    float diff = max(dot(norm, lightDir), 0.0);

    if (diff > 0.75)
        diff = 1.0;
    else if (diff > 0.5)
        diff = 0.75;
    else if (diff > 0.25)
        diff = 0.5;
    else
        diff = 0.25;

    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - currentPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    if (spec > 0.5)
        spec = 1.0;
    else
        spec = 0.0;

    float specular = specularStrength * spec;

    FragColor = spriteColor * lightColor * (ambient + diff + specular);
}
