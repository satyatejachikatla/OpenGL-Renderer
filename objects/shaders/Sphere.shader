#shader vertex
#version 410 core

layout(location = 0) in vec4 position;
layout(location = 2) in vec2 texCoords;
layout(location = 4) in vec3 normal;

out vec3 v_FragPos;
out vec3 v_Normal;
out vec2 v_TexCoord;
out float v_TexIndex;

uniform mat4 u_VP;
uniform mat4 u_M;


void main()
{

	gl_Position = u_VP*u_M*position;

	v_FragPos = vec3(u_M*position);
	v_Normal  = mat3(transpose(inverse(u_M))) * normal;

	v_TexCoord = texCoords;
}

#shader fragment
#version 410 core

layout(location = 0) out vec4 color;

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

in vec3 v_FragPos;
in vec3 v_Normal;
in vec2 v_TexCoord;

uniform vec3 u_ViewPos;

uniform Material u_Material;

uniform DirLight u_DirectionLight[1];
uniform float u_DirectionLightCount;

vec3 CalcDirLight(DirLight light,vec3 normal,vec3 viewDir);

void main()
{
	// Vertex Color Mixing 
	vec4 texColor = texture(u_Material.texture,v_TexCoord);

	// Normal
	vec3 norm = normalize(v_Normal);
	vec3 viewDir = normalize(u_ViewPos - v_FragPos);


	vec3 dirResult;

	// Directional Light
	dirResult = vec3(0.0f,0.0f,0.0f);
	if(u_DirectionLightCount > 0) {
		for(int i=0;i<u_DirectionLightCount;i++){
			dirResult += CalcDirLight(u_DirectionLight[i],norm,viewDir);
		}
	}

	//Combine everything
	vec4 result = vec4(dirResult,1.0f);

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