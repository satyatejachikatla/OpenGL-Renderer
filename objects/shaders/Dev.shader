#shader vertex
#version 410 core
#define PI 3.1415926535897932384626433832795

layout(location = 0) in vec4 position;
layout(location = 2) in vec2 texCoords;
layout(location = 4) in vec3 normal;

out vec3 v_FragPos;
out vec3 v_Normal;
out vec2 v_TexCoord;
out float v_TexIndex;

uniform float up_down_theta;
uniform float height_limiter;

uniform mat4 u_VP;
uniform mat4 u_M;


void main()
{

	vec4 n_position = position;
	n_position.y = sin(up_down_theta+PI/2*((int(n_position.x+n_position.z))%4))*height_limiter; 

	gl_Position = u_VP*u_M*n_position;

	v_TexCoord = texCoords;
}

#shader fragment
#version 410 core

layout(location = 0) out vec4 color;
in vec2 v_TexCoord;

struct Material {

	/* Vertex Color related */
	float selectColor;

	/* Texture Related */
	sampler2D texture;
	float shininess;

	bool isSpecularMap;
	sampler2D specularMap;
};

uniform Material u_Material;

void main()
{
	// Vertex Color Mixing 
	vec4 texColor = texture(u_Material.texture,v_TexCoord);

	color = texColor;
}
