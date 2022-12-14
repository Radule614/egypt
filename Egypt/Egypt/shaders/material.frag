#version 330 core

#define NR_POINT_LIGHTS 7

in vertex_out {
	vec3 FragNormal;
    vec3 FragPos;
    vec2 FragTexCoords;
    mat3 TBN;
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
uniform PointLight pointLights[NR_POINT_LIGHTS];

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirectionalLight directionalLight;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
uniform sampler2D texture_normal1;
uniform sampler2D texture_normal2;

uniform vec3 cameraPos;
uniform bool useTexture;
uniform bool useNormalMap;

vec3 calculateDirectionalLight(DirectionalLight light, Material mat, vec3 normal, vec3 viewDir) {
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), mat.shininess);

    vec3 ambient = light.ambient * mat.ambient;
    vec3 diffuse = light.diffuse * diff * mat.diffuse;
    vec3 specular = light.specular * spec * mat.specular;

    return (ambient + diffuse + specular);
}
vec3 calculatePointlight(PointLight light, Material mat, vec3 fragPos, vec3 normal, vec3 viewDir) {
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    
    vec3 halfwayDir = normalize(lightDir+viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), mat.shininess);

    vec3 ambient = light.ambient * mat.ambient;
    vec3 diffuse = light.diffuse * diff * mat.diffuse;
    vec3 specular = light.specular * spec * mat.specular;

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    return (ambient + diffuse + specular);
}

void main() {
    vec3 viewDir = normalize(cameraPos - FragmentIn.FragPos);
    Material mat = material;

    if(useTexture) {
        mat.diffuse = vec3(texture(texture_diffuse1, FragmentIn.FragTexCoords));
        mat.ambient = 0.03 * mat.diffuse;
        mat.specular = vec3(texture(texture_specular1, FragmentIn.FragTexCoords));
        mat.shininess = 128.0;
    }

    vec3 normal = FragmentIn.FragNormal;
    if(useNormalMap){
        normal = vec3(texture(texture_normal1, FragmentIn.FragTexCoords));
        normal = normal * 2.0 - 1.0;  
        normal = normalize(FragmentIn.TBN * normal); 
    }

    vec3 color = calculateDirectionalLight(directionalLight, mat, normal, viewDir);
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        color += calculatePointlight(pointLights[i], mat, FragmentIn.FragPos, normal, viewDir);

    float gamma = 2.2;
    FragColour = vec4(pow(color, vec3(1.0/gamma)), 1.0);
}