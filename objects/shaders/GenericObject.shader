#shader vertex
#version 440 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoords;
layout(location = 3) in float texIndex;
layout(location = 4) in vec3 normal;

out vec2 v_TexCoord;
out vec4 v_Color;
out float v_TexIndex;

out vec3 v_FragPos;
out vec3 v_Normal;


uniform mat4 u_VP;
uniform mat4 u_M;

void main()
{
	gl_Position = u_VP*u_M*position;

	v_FragPos = vec3(u_M*position);
	v_Normal  = mat3(transpose(inverse(u_M))) * normal;

	v_TexCoord = texCoords;
	v_Color = color;
	v_TexIndex = texIndex;
}

#shader fragment
#version 440 core

layout(location = 0) out vec4 color;


#define MAX_LIGHTS 5

struct Material {

	/* Vertex Color related */
	float selectColor;

	/* Texture Related */
	sampler2D texture;
	float shininess;

	bool isSpecularMap;
	sampler2D specularMap;
};

struct DirLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

};

struct PointLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 attenuationQuadraticEquation;
};

struct SpotLight {
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 attenuationQuadraticEquation;

	float cutOff;
	float outerCutOff;
};


in vec2 v_TexCoord;
in vec4 v_Color;
in float v_TexIndex;

in vec3 v_FragPos;
in vec3 v_Normal;

// Camera position
uniform vec3 u_ViewPos;

// Material and Light Properties    
uniform Material   u_Material;
uniform DirLight   u_DirectionLight[MAX_LIGHTS];
uniform PointLight u_PointLight[MAX_LIGHTS];
uniform SpotLight  u_SpotLight[MAX_LIGHTS];

uniform float   u_DirectionLightCount;
uniform float   u_PointLightCount;
uniform float   u_SpotLightCount;

vec3 CalcDirLight(DirLight light,vec3 normal,vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal , vec3 fragPos , vec3 viewDir);
vec3 CalcSpotLight(SpotLight light,vec3 normal,vec3 fragPos,vec3 viewDir);

void main()
{

	// Vertex Color Mixing 
	vec4 SelectColorVec = vec4(1.0f,1.0f,1.0f,1.0f) * u_Material.selectColor;
	vec4 OneMinusSelectColorVec = vec4(1.0f,1.0f,1.0f,1.0f) - SelectColorVec;

	vec4 texColor = OneMinusSelectColorVec * texture(u_Material.texture,v_TexCoord);
	texColor += SelectColorVec * v_Color;


	// Normal
	vec3 norm = normalize(v_Normal);
	vec3 viewDir = normalize(u_ViewPos - v_FragPos);


	vec3 dirResult,pointResult,spotResult;

	// Directional Light
	dirResult = vec3(0.0f,0.0f,0.0f);
	if(u_DirectionLightCount > 0) {
		for(int i=0;i<u_DirectionLightCount;i++){
			dirResult += CalcDirLight(u_DirectionLight[i],norm,viewDir);
		}
	}

	// Point Light
	pointResult = vec3(0.0f,0.0f,0.0f);
	if(u_PointLightCount > 0) {
		for(int i=0;i<u_PointLightCount;i++){
			pointResult += CalcPointLight(u_PointLight[i],norm,v_FragPos,viewDir);
		}
	}

	// Spot Light
	spotResult = vec3(0.0f,0.0f,0.0f);
	if(u_SpotLightCount > 0) {
		for(int i=0;i<u_SpotLightCount;i++){
			spotResult += CalcSpotLight(u_SpotLight[i],norm,v_FragPos,viewDir);
		}
	}

	//Combine everything
	vec4 result = vec4((dirResult + pointResult + spotResult)/(u_DirectionLightCount+u_PointLightCount+u_SpotLightCount),1.0f);

	color = result * texColor;
}

vec3 CalcDirLight(DirLight light,vec3 normal,vec3 viewDir){
	// ambient
	vec3  ambient = light.ambient;

	// diffuse
	vec3 norm = normal;
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = light.diffuse * diff;

	// specular
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f),u_Material.shininess);
	vec3 specular;
	if(u_Material.isSpecularMap)
		specular = light.specular * (spec *vec3(texture(u_Material.specularMap,v_TexCoord)));
	else
		specular = light.specular * spec;

	//Combine everything
	vec3 result = ambient + diffuse + specular;

	return result;
}
vec3 CalcPointLight(PointLight light, vec3 normal , vec3 fragPos , vec3 viewDir){
	// ambient
	vec3  ambient = light.ambient;

	// diffuse
	vec3 norm = normal;
	vec3 lightDir = normalize(light.position-fragPos);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = light.diffuse * diff;

	// specular
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f),u_Material.shininess);
	vec3 specular;
	if(u_Material.isSpecularMap)
		specular = light.specular * (spec *vec3(texture(u_Material.specularMap,v_TexCoord)));
	else
		specular = light.specular * spec;

	// Attenuation
	float d = length(light.position-fragPos);
	float attenuation = light.attenuationQuadraticEquation.x*d*d+
						light.attenuationQuadraticEquation.y*d+
						light.attenuationQuadraticEquation.z;
	attenuation = 1.0f/attenuation;

	//Combine everything
	vec3 result = (ambient + diffuse + specular)*attenuation;

	return result;
}
vec3 CalcSpotLight(SpotLight light,vec3 normal,vec3 fragPos,vec3 viewDir){

	// ambient
	vec3  ambient = light.ambient;

	// diffuse
	vec3 norm = normal;
	vec3 lightDir = normalize(light.position-fragPos);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = light.diffuse * diff;

	// specular
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f),u_Material.shininess);
	vec3 specular;
	if(u_Material.isSpecularMap)
		specular = light.specular * (spec *vec3(texture(u_Material.specularMap,v_TexCoord)));
	else
		specular = light.specular * spec;

	//Cone calculation
	float theta = dot(lightDir,normalize(-light.direction));
	float epsilon = light.cutOff -light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff)/epsilon,0.0f,1.0f);

	// Attenuation
	float d = length(light.position-fragPos);
	float attenuation = light.attenuationQuadraticEquation.x*d*d+
						light.attenuationQuadraticEquation.y*d+
						light.attenuationQuadraticEquation.z;
	attenuation = 1.0f/attenuation;

	//Combine everything
	vec3 result = (ambient + diffuse*intensity + specular*intensity)*attenuation;

	return result;

}