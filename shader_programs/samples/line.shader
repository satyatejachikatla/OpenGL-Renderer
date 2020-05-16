#shader vertex
#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;

out vec4 v_position;
out vec3 v_color;

uniform mat4 u_P;

void main()
{

	gl_Position = u_P*position;

	v_position = position;
	v_color    = color;

}

#shader fragment
#version 410 core

#define PI 3.1415926535897932384626433832795

layout(location = 0) out vec4 fragColor;

in vec4 v_position;
in vec3 v_color;

uniform float u_Time;
uniform float u_Itteration;
uniform vec2 u_Resolution;
uniform vec2 u_Mouse;
uniform sampler2D u_TextureChannels[5];

vec2 translate(vec2 uv ,vec2 move) {
	return uv - move;
}

float line_x(vec2 coord_system,float blur=0.001){
	float d = smoothstep(blur,0.,abs(coord_system.x));
	return d;
}

float line_y(vec2 coord_system,float blur=0.001){
	float d = smoothstep(blur,0.,abs(coord_system.y));
	return d;
}

vec2 N(float angle) {
	//Angle in rad
	return vec2(sin(angle),cos(angle)); 
}
float normal(vec2 coord_system,float angle,float blur=0.001) {
	
	float d= dot(coord_system,N(angle));
	d = smoothstep(blur,0.,abs(d));

	return d;
}
void main()
{
	vec2 fragCoords = v_position.xy;
	vec2 uv = (fragCoords-.5*u_Resolution.xy)/u_Resolution.y;
	vec2 mouse = (u_Mouse-0.5*u_Resolution)/u_Resolution.y;
	vec3 col = vec3(0.);

	//Simple Line alligned to axis
	float l1 = line_y(translate(uv,mouse),0.005);

	//Line From Origin with rotation
	float l2 = normal(translate(uv,vec2(0.25,0.25)),mouse.x,0.01);

	vec3 col_l1 = vec3(0.,0.,1.) * l1;
	vec3 col_l2 = vec3(1.,0.,0.) * l2;

	// col = mix(col_l1,col,0.3);
	// col = mix(col_l2,col,0.3);

	col += col_l1;
	col += col_l2;

	fragColor = vec4(col,1.0);

}
