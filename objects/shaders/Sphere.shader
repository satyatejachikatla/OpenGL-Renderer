#shader vertex
#version 410 core

layout(location = 0) in vec4 position;
layout(location = 4) in vec3 normal;

out vec3 v_FragPos;
out vec3 v_Normal;

uniform mat4 u_VP;
uniform mat4 u_M;


void main()
{

	gl_Position = u_VP*u_M*position;

	v_FragPos = vec3(u_M*position);
	v_Normal  = mat3(transpose(inverse(u_M))) * normal;
}

#shader fragment
#version 410 core

layout(location = 0) out vec4 color;

in vec3 v_FragPos;
in vec3 v_Normal;

void main()
{
	color = vec4(1.0f,1.0f,1.0f,1.0f);
}