#shader vertex
#version 440 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoords;
layout(location = 3) in float texIndex;

out vec2 v_TexCoord;
out vec4 v_Color;
out float v_TexIndex;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP*position;
	v_TexCoord = texCoords;
	v_Color = color;
	v_TexIndex = texIndex;
}

#shader fragment
#version 440 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 v_Color;
in float v_TexIndex;

uniform sampler2D u_Textures[32];
uniform float u_SelectColorf;

void main()
{

	highp int index = int(round(v_TexIndex));

	vec4 SelectColorVec = vec4(u_SelectColorf,u_SelectColorf,u_SelectColorf,u_SelectColorf);
	vec4 OneMinusSelectColorVec = vec4(1.0f-u_SelectColorf,1.0f-u_SelectColorf,1.0f-u_SelectColorf,1.0f-u_SelectColorf);

	vec4 texColor = OneMinusSelectColorVec * texture(u_Textures[index],v_TexCoord);
	texColor += SelectColorVec * v_Color;

    //Checking texture id with index
    //texColor = vec4(float(index),float(index),float(index),float(index));

    //Checking texture id with float index
    //texColor = vec4(v_TexIndex,v_TexIndex,v_TexIndex,v_TexIndex);

	color = texColor;
}