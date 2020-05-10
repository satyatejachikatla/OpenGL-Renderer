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

#define CIRCLE_FRACT_THRESH 0.86

void main()
{
	vec2 fragCoords = v_position.xy;
	vec2 uv = (fragCoords-.5*u_Resolution.xy)/u_Resolution.y;
	vec2 mouse = vec2(u_Mouse.x-0.5*u_Resolution.x, u_Mouse.y)/u_Resolution.y;
	vec3 col = vec3(0.);

	float d;

	//Lines//
	d = smoothstep(0.03,0.02,abs(abs(uv.x)-0.5));
	col += d;

	const float radius=0.4;
	const float glow_extra = 0.2;

	// Eye Center white //
	d = length(uv);
	col += smoothstep(radius+glow_extra,0.001,d)*(abs(sin(u_Time*2.)))*0.5;

	// Cicle //
	float adjust_size = 0.002;
	d = length(uv);
	col += ceil(smoothstep(radius,0.,clamp(d,0.,1.)));
	col -= ceil(smoothstep(radius-adjust_size,0.,clamp(d,0.,1.)));


	// Eye //
	d = length(uv.xy);
	d = fract(mix(0.,1000.,smoothstep(radius,0.,d)));

	if(d >= CIRCLE_FRACT_THRESH-abs(sin(u_Time*2.))*CIRCLE_FRACT_THRESH)
		col.r += smoothstep(0.,0.001,d);

	

	fragColor = vec4(col,1.0);

}
