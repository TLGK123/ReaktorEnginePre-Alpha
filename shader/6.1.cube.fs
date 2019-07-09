#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{
     vec3 I = normalize(Position - cameraPos);
     vec3 R = reflect(I,normalize(Normal));
     vec4 reflectColor = vec4(texture(skybox,R).rgb,1.0);

    float ratio = 1.00 / 1.52;
      R = refract(I, normalize(Normal), ratio);
    vec4 refractColor = vec4(texture(skybox, R).rgb, 1.0);
    
    float s = 0.2;   //反射强度
     FragColor  =  reflectColor *s  + refractColor * (1- s);
}