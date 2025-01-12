#version 410 core

uniform vec4 spriteColor;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
out vec4 FragColor;

in vec3 Normal;
in vec3 currentPos;

float hash(float n)
{
    return fract(sin(n) * 43758.5453123);
}

float noise(vec2 p)
{
    vec2 i = floor(p);
    vec2 f = fract(p);
    f = f * f * (3.0 - 2.0 * f);
    return mix(mix(hash(i.x + i.y * 57.0), hash(i.x + 1.0 + i.y * 57.0), f.x),
               mix(hash(i.x + (i.y + 1.0) * 57.0), hash(i.x + 1.0 + (i.y + 1.0) * 57.0), f.x), f.y);
}

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

    float noiseValue = noise(currentPos.xz * 0.1);
    vec4 stripeColor1 = spriteColor * 0.8;
    vec4 stripeColor2 = spriteColor * 1.2;
    vec4 grassColor = mix(stripeColor1, stripeColor2, noiseValue);

    FragColor = grassColor * lightColor * (ambient + diff + specular);
}
