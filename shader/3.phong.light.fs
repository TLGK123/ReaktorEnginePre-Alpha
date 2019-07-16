# version 330 core 
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;        //纹理坐标

struct Material
{
    //vec3 ambient;      //大多数情况下和漫反射颜色一致
    sampler2D diffuse;   //使用漫反射贴图代替物体漫反射颜色
    sampler2D specular;
    float shininess;
};


struct Light
{
    vec3 position;     // 点光源的 位置信息
    //vec3 direction;   //平行光的方向 光照计算需求一个从片段至光源的光线方向，人们更习惯定义定向光为一个从光源出发的全局方向

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;  //光强的衰弱系数 就是利用 关于距离的一元二次方程的 倒数  1.0/（ a* d^2 + b*d +c）
    float linear;    // 线性系数
    float quadratic; // 平方系统

};

uniform Material material;
uniform Light light;

void main()
{
    float distance = length(light.position - FragPos); //像素点距离光源距离，下面是衰弱计算
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));


    vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoords));
    vec3 lightDir = normalize(light.position - FragPos); //点光源点方向计算
    //vec3 lightDir = normalize(-light.direction);   //平行光点方向
    vec3 normal = normalize(Normal);
    float diff = max(dot(normal , lightDir),0);
    vec3 diffuse = light.diffuse * vec3(texture(material.diffuse,TexCoords)) * diff;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir,reflectDir),0),material.shininess);
    vec3 specular = light.specular * (spec * vec3(texture(material.specular,TexCoords)));

    ambient  *= attenuation; 
    diffuse  *= attenuation;
    specular *= attenuation;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result , 1.0);
}