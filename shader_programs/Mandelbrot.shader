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


void main()
{
	vec2 fragCoords = v_position.xy;
	vec2 uv = (fragCoords-.5*u_Resolution.xy)/u_Resolution.y;
	vec2 mouse = vec2(u_Mouse.x-0.5*u_Resolution.x, u_Mouse.y)/u_Resolution.y;

	vec2 z = vec2(0.);
	vec2 c = uv*(1-mouse.x); ///pow(u_Itteration,u_Itteration*0.1);
	c+= vec2(-1.024,0.25);
	const float max_steps = 200;
	const int strength = 10;
	int steps = 0;

	for(float i = 0 ;i < max_steps ; i++) {
		z = vec2(z.x*z.x - z.y*z.y,2.*z.x*z.y) + c;
		steps ++;
		if(length(z) > 2.) break;
	}

	if(steps == max_steps) {
		fragColor = vec4(.0);
		return;
	}

	float f = (steps*strength%256)/256.;
	f = pow(f,1);
	
	vec3 col =texture(u_TextureChannels[0],vec2(f/2.,f/3.)).rgb;//vec3(f);
	fragColor = vec4(col,1.0f);
}
