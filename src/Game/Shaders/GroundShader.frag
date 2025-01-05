#version 410 core

uniform vec4 spriteColor;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
out vec4 FragColor;

in vec3 Normal;
in vec3 currentPos;

vec3 mod289(vec3 x) { return x - floor(x * (1.0 / 289.0)) * 289.0; }
vec2 mod289(vec2 x) { return x - floor(x * (1.0 / 289.0)) * 289.0; }
vec3 permute(vec3 x) { return mod289(((x*34.0)+1.0)*x); }

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

float snoise(vec2 v)
{
    const vec4 C = vec4(0.211324865405187, 0.366025403784439, -0.577350269189626, 0.024390243902439);
    vec2 i  = floor(v + dot(v, C.yy) );
    vec2 x0 = v -   i + dot(i, C.xx);
    vec2 i1;
    i1 = (x0.x > x0.y) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);
    vec4 x12 = x0.xyxy + C.xxzz;
    x12.xy -= i1;
    i = mod289(i);
    vec3 p = permute( permute( i.y + vec3(0.0, i1.y, 1.0 )) + i.x + vec3(0.0, i1.x, 1.0 ));
    vec3 m = max(0.5 - vec3(dot(x0,x0), dot(x12.xy,x12.xy), dot(x12.zw,x12.zw)), 0.0);
    m = m*m ;
    m = m*m ;
    vec3 x = 2.0 * fract(p * C.www) - 1.0;
    vec3 h = abs(x) - 0.5;
    vec3 ox = floor(x + 0.5);
    vec3 a0 = x - ox;
    m *= 1.79284291400159 - 0.85373472095314 * ( a0*a0 + h*h );
    vec3 g;
    g.x  = a0.x  * x0.x  + h.x  * x0.y;
    g.yz = a0.yz * x12.xz + h.yz * x12.yw;
    return 130.0 * dot(m, g);
}

float level(vec2 st)
{
    float n = 0.0;
    for (float i = 1.0; i < 6.0; i++)
    {
        float m = pow(2.0, i);
        n += snoise(st * m * 0.5) * (1.0 / m) * 0.75;
    }
    return n * 0.5 + 0.5;
}

vec3 normal(vec2 st)
{
    float d = 0.0001;
    float l0 = level(st);
    float l1 = level(st + vec2(d, 0.0));
    float l2 = level(st + vec2(0.0, d));
    return normalize(vec3(-(l1 - l0), -(l2 - l0), d));
}

vec3 phong(vec2 st, vec3 normal, vec3 lightPos)
{
    vec3 lightDir = normalize(vec3(lightPos - vec3(st, 0.0)));
    float diffuse = max(0.0, dot(normal, lightDir));
    vec3 vReflection = normalize(reflect(-lightDir, normal));
    float specular = pow(max(0.0, dot(normal, vReflection)), 8.0);
    vec3 ambientColor = vec3(0.1,0.0,0.2);
    vec3 diffuseColor = vec3(0.0,0.5,0.2);
    return min(vec3(1.0), ambientColor + diffuseColor * diffuse + specular);
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

    vec2 st = currentPos.xz;
    vec3 col = phong(st, normal(st), lightPos);
    float n = level(st);
    if (n < 0.4) { col = vec3(0.0, 0.0, 0.2); }

    FragColor = vec4(col * lightColor.rgb * (ambient + diff + specular), 1.0);
}