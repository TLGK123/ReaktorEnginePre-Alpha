#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 texcoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = view * model * vec4(pos,1);
    mat4 worldNormal = view * model * vec4(normal,1);
    vec3 worldNormal2 = normalize(worldNormal.xyz);
    
    gl_Position.z =  -0.5;
    TexCoords = texcoords;
}
