#version 330 core

in vertex_out {
	vec3 FragNormal;
    vec3 FragPos;
} FragmentIn;

out vec4 FragColour;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
uniform Material material;

struct PointLight {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
#define NR_POINT_LIGHTS 3
uniform PointLight pointLights[NR_POINT_LIGHTS];

struct DirectionalLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirectionalLight directionalLight; 

uniform vec3 cameraPos;

vec3 calculateDirectionalLight(DirectionalLight light, Material mat, vec3 normal, vec3 viewDir) {
    vec3 ambient  = light.ambient * mat.ambient;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse  = light.diffuse * (diff * mat.diffuse);

    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat.shininess);
    vec3 specular = light.specular * (spec * mat.specular);

    return (ambient + diffuse + specular);
}

vec3 calculatePointlight(PointLight light, Material mat, vec3 normal, vec3 fragPos, vec3 viewDir){
    vec3 ambient  = light.ambient * mat.ambient;
  	
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse  = light.diffuse * (diff * mat.diffuse);
    
    
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat.shininess);
    vec3 specular = light.specular * (spec * mat.specular);

    
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    return (ambient + diffuse + specular);
}

void main() {
    vec3 viewDir = normalize(cameraPos - FragmentIn.FragPos);

    vec3 color = calculateDirectionalLight(directionalLight, material, FragmentIn.FragNormal, viewDir);

    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        color += calculatePointlight(pointLights[i], material, FragmentIn.FragNormal, FragmentIn.FragPos, viewDir);

    FragColour = vec4(color, 1.0);
}