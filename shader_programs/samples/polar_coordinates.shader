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

void main()
{
	vec2 fragCoords = v_position.xy;
	vec2 uv = (fragCoords-.5*u_Resolution.xy)/u_Resolution.y;
	vec2 mouse = (u_Mouse-0.5*u_Resolution)/u_Resolution.y;
	mouse.y = -mouse.y;
	vec3 col = vec3(0.);

	uv = translate(uv,mouse);

	//Polar
	vec2 st = vec2(atan(uv.x,uv.y),length(uv));

	uv = vec2(st.x/PI+u_Time*.1+st.y,st.y);

	float x = uv.x*5.;
	float m = min(fract(x),fract(1.-x));

	float c = smoothstep(0.,.1,m*0.3+.2-uv.y);

	col += st.x/PI/2. + .5; 
	fragColor = vec4(vec3(c),1.);
}
