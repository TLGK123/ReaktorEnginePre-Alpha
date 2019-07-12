# version 330 core 
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

in vec3 Normal;
in vec3 FragPos;

float ambientStrength =0.1f;

void main()
{
    vec3 ambient = lightColor * ambientStrength;
    vec3 lightDir = normalize(lightPos - FragPos  );
    vec3 normal = normalize(Normal);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 result = (ambient + diff) * objectColor;
    FragColor =  vec4 (result,1.0f);
}