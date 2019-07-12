# version 330 core 
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;

float ambientStrength =0.1f;  //太阳光强度
float specularStrength = 0.5; //镜面反射强度

void main()
{
    vec3 ambient = lightColor * ambientStrength;
    vec3 lightDir = normalize(lightPos - FragPos  );
    vec3 normal = normalize(Normal);
    float diff = max(dot(normal, lightDir), 0.0);
 
    vec3 viewDir = normalize(viewPos -FragPos);
    vec3 reflectDir = reflect(-lightDir,normal);
    
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diff +specular) * objectColor;
    FragColor =  vec4 (result,1.0f);
}