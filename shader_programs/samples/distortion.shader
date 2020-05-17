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

float band(float d,float start,float end,float blur) {
	float step1 = smoothstep(start-blur ,start+blur,d) ;
	float step2 = smoothstep(end  +blur ,end  -blur,d) ;

	return step1*step2;
}

float rectangle(vec2 coord_system,vec2 bot_lo,vec2 wh,float blur=0.001) {

	float left  = bot_lo.x;
	float right = bot_lo.x + wh.x;

	float bot   = bot_lo.y;
	float top   = bot_lo.y + wh.y;

	float band1 = band(coord_system.x,left,right,blur);
	float band2 = band(coord_system.y,bot,top,blur);

	return band1*band2;
}

void main()
{
	vec2 fragCoords = v_position.xy;
	vec2 uv = (fragCoords-.5*u_Resolution.xy)/u_Resolution.y;
	vec2 mouse = (u_Mouse-0.5*u_Resolution)/u_Resolution.y;
	vec3 col = vec3(0.);

	float shear=0.2;

	uv*=1.;
	mouse *=1.;
	uv-=vec2(-0.75,-0.2);

	//uv.x = abs(uv.x);
	//uv.x+=uv.y;

	vec2 wh= vec2(1.,0.25);
	vec2 mouse_control = vec2(mouse.x,-mouse.y);
	mouse_control = vec2(0.0,0.0);

/* Equation based distortion */
	// //Distort alone uv along x as parabola 
	// float m = (uv.x-0.5)*(uv.x+0.5);
	// //Turn Prabola into a w shape
	// m += -m*m*4.;
	// //Apply distortion
	// uv.y += m;
/* End */


	float t = u_Time;
	//Smoothstep based blurring 
	float blur = 1.4*smoothstep(0.01,0.99,pow(uv.x,2.));

	// Equation based distortion
	//Increase the frequence and attenuate sine to fit in -1to1
	float m = sin(uv.x*8.+t)*0.1;
	uv.y+=m;

	//Simple Rectangle
	float c1 = rectangle(uv,mouse_control,wh,blur);

	col +=  vec3(1.0) * c1;

	fragColor = vec4(col,1.0);

}
