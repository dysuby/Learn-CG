#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;

uniform float ambientStrength;
uniform float diffStrength;
uniform float specularStrength;
uniform int shininess;

uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

void main() {
    // ambient
    // 根据作业要求引入ambient因子
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    // 标准化
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    // 计算漫反射分量（根据作业要求引入diffuse因子
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diffStrength * diff * lightColor;

    // specular
    // 计算视线方向向量
    vec3 viewDir = normalize(viewPos - FragPos);
    // 计算反射变量
    vec3 reflectDir = reflect(-lightDir, norm);
    // 计算镜面分量（根据作业要求添加反光度因子
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // 根据作业要求添加specular因子
    vec3 specular = specularStrength * spec * lightColor;  

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
} 