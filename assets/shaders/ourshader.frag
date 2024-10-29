#version 330 core
out vec4 FragColor;

struct Material {    
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;

    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

#define MAX_DIR_LIGHTS 20
#define MAX_POINT_LIGHTS 20
#define MAX_SPOT_LIGHTS 20

uniform int NbrDirLights;
uniform int NbrPointLights;
uniform int NbrSpotLights;

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;

uniform vec3 color;
  
uniform vec3 viewPos;
uniform DirLight dirLights[MAX_DIR_LIGHTS];
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform Material material;

// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

float near = 0.1f; 
float far = 1000.0f; 
  
float LinearizeDepth(float depth) 
{
    return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));	
}

float LogisticDepth(float depth, float steepness = 0.5f, float offset = 5.f)
{
    float zVal = LinearizeDepth(depth);
    return (1 / (1 + exp(-steepness * (zVal - offset))));
}

void main()
{
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // == =====================================================
    // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
    // For each phase, a calculate function is defined that calculates the corresponding color
    // per lamp. In the main() function we take all the calculated colors and sum them up for
    // this fragment's final color.
    // == =====================================================
    vec3 result = vec3(0,0,0);
    // phase 1: directional lighting
    for(int i = 0; i < NbrDirLights; i++)
        result += CalcDirLight(dirLights[i], norm, viewDir);
    // phase 2: point lights
    for(int i = 0; i < NbrPointLights; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    
    // phase 3: spot light
    for(int i = 0; i < NbrSpotLights; i++)
        result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);
    
    if(texture(material.diffuse, TexCoords).a < 0.1)
        discard;
    if(texture(material.specular, TexCoords).a < 0.1)
        discard;

    FragColor = vec4(result, 1.0);

    //float depth = LogisticDepth(gl_FragCoord.z); // divide by far for demonstration
    //FragColor = vec4(result, 1.0) * (1.0f - depth) + vec4(depth * vec3(0.85f, 0.85f, 0.90f), 1.0);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    if(texture(material.diffuse, TexCoords).a < 0.1)
        discard;
    if(texture(material.specular, TexCoords).a < 0.1)
        discard;

    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distanceToFrag = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distanceToFrag + light.quadratic * (distanceToFrag * distanceToFrag));    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    if(texture(material.diffuse, TexCoords).a < 0.1)
        discard;
    if(texture(material.specular, TexCoords).a < 0.1)
        discard;

    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distanceToFrag = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distanceToFrag + light.quadratic * (distanceToFrag * distanceToFrag));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    if(texture(material.diffuse, TexCoords).a < 0.1)
        discard;
    if(texture(material.specular, TexCoords).a < 0.1)
        discard;

    return (ambient + diffuse + specular);
}