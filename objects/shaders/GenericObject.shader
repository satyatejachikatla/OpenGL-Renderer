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

struct Material {

	/* Vertex Color related */
	float selectColor;

	/* Texture Related */
	sampler2D texture;
	float shininess;

	bool isSpecularMap;
	sampler2D specularMap;
};

struct Light {
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 attenuationQuadraticEquation;
};

in vec2 v_TexCoord;
in vec4 v_Color;
in float v_TexIndex;

in vec3 v_FragPos;
in vec3 v_Normal;

// Camera position
uniform vec3 u_ViewPos;

// Material and Light Properties    
uniform Material u_Material;
uniform Light u_Light;

void main()
{

	// Vertex Color Mixing 
	vec4 SelectColorVec = vec4(1.0f,1.0f,1.0f,1.0f) * u_Material.selectColor;
	vec4 OneMinusSelectColorVec = vec4(1.0f,1.0f,1.0f,1.0f) - SelectColorVec;

	vec4 texColor = OneMinusSelectColorVec * texture(u_Material.texture,v_TexCoord);
	texColor += SelectColorVec * v_Color;

	// ambient
	vec3  ambient = u_Light.ambient;

	// diffuse
	vec3 norm = normalize(v_Normal);
	//vec3 lightDir = normalize(u_Light.position - v_FragPos);
	vec3 lightDir = normalize(-u_Light.direction);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = u_Light.diffuse * diff;

	// specular
	vec3 viewDir = normalize(u_ViewPos - v_FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f),u_Material.shininess);
	vec3 specular;
	if(u_Material.isSpecularMap)
		specular = u_Light.specular * (spec *vec3(texture(u_Material.specularMap,v_TexCoord)));
	else
		specular = u_Light.specular * spec;

	//Combine everything
	vec4 result = vec4(ambient + diffuse + specular,1.0f);

	color = result * texColor;
}