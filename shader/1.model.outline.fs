#version 330 core
out vec4 FragColor;

int vec2 TexCoords;

uniform sampler2D texturediff;

void main()
{
   // FragColor = texture(texturediff, TexCoords);
   FragColor = vec4(vec3(0,0,0),1);
}