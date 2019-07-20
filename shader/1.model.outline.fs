#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texturediff;

void main()
{
   // FragColor = texture(texturediff, TexCoords);
   FragColor = vec4(vec3(1,1,1),1);
}