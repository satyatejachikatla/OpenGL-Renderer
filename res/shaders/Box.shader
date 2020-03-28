#shader vertex
#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoords;

out vec2 v_TexCoord;
out vec3 v_Color;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP*position;
	v_TexCoord = texCoords;
}

#shader fragment
#version 410 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_Color;

uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture,v_TexCoord) + vec4(v_Color,0.0f);
	color = texColor;
}