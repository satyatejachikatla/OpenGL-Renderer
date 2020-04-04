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
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 position;

	vec3 ambient;	
	vec3 diffuse;	
	vec3 specular;	
};

in vec2 v_TexCoord;
in vec4 v_Color;
in float v_TexIndex;

in vec3 v_FragPos;
in vec3 v_Normal;

uniform sampler2D u_Textures[32];
uniform float u_SelectColorf;

uniform vec3 viewPos;    // Camera position
uniform Material material;
uniform Light light;

void main()
{

	highp int index = int(round(v_TexIndex));

	vec4 SelectColorVec = vec4(u_SelectColorf,u_SelectColorf,u_SelectColorf,u_SelectColorf);
	vec4 OneMinusSelectColorVec = vec4(1.0f-u_SelectColorf,1.0f-u_SelectColorf,1.0f-u_SelectColorf,1.0f-u_SelectColorf);

	vec4 texColor = OneMinusSelectColorVec * texture(u_Textures[index],v_TexCoord);
	texColor += SelectColorVec * v_Color;

	//ambient
	vec3  ambient = light.ambient * material.ambient;

	//diffuse
	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(light.position - v_FragPos);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	//specular
	vec3 viewDir = normalize(viewPos - v_FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
	vec3 specular = light.specular * (spec * material.specular);

	vec4 result = vec4(ambient + diffuse + specular,1.0f);

	color = result*texColor;
}