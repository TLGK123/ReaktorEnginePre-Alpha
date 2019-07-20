#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float outLine;
vec4 viewN;
vec3 viewormal;

void main()
{
    gl_Position = view * model * vec4(pos,1);
    viewN = view * model * vec4(normal,1);
    viewormal = viewN.xyz;
    viewormal.z =  -0.5;
    gl_Position = gl_Position + vec4(normalize(viewormal.xyz),0) * outLine;
    gl_Position = projection * gl_Position;
    TexCoords = texcoords;
}
