# version 330 core 
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

float ambientStrength =0.1f;
vec3 ambient = lightColor * ambientStrength;
void main()
{
    vec3 result = objectColor * ambient;
    FragColor =  vec4 (result,1.0f);
}