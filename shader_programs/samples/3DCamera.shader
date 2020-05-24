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

float DistLine(vec3 ro,vec3 rd,vec3 p){
	return length(cross(p-ro,rd))/length(rd);
}

float DrawPoint(vec3 ro,vec3 rd,vec3 p){
	float d = DistLine(ro,rd,p);
	d = smoothstep(.06,0.05,d);
	return d;
}

void main()
{
	vec2 fragCoords = v_position.xy;
	vec2 uv = (fragCoords-.5*u_Resolution.xy)/u_Resolution.y;
	vec2 mouse = (u_Mouse-0.5*u_Resolution)/u_Resolution.y;

	float t = u_Time;

	float zoom = 1.;

	vec3 ro = vec3(3.*sin(t),0.,-3*cos(t));
	vec3 lookat = vec3(0.5,0.5,0.5);
	vec3 u_world = vec3(0.,1.,0.);
	vec3 f = normalize(lookat-ro);
	vec3 r = cross(u_world,f);
	vec3 u = cross(f,r);

	vec3 c = ro + f*zoom;
	vec3 i = c + uv.x*r + uv.y*u;

	vec3 rd = i-ro;

	float d = 0.;

	d += DrawPoint(ro,rd,vec3(0.,0.,0.));
	d += DrawPoint(ro,rd,vec3(0.,1.,0.));
	d += DrawPoint(ro,rd,vec3(1.,1.,0.));
	d += DrawPoint(ro,rd,vec3(1.,0.,0.));
	d += DrawPoint(ro,rd,vec3(0.,0.,1.));
	d += DrawPoint(ro,rd,vec3(0.,1.,1.));
	d += DrawPoint(ro,rd,vec3(1.,1.,1.));
	d += DrawPoint(ro,rd,vec3(1.,0.,1.));

	fragColor = vec4(d);
}


//ffmpeg -video_size 900x500 -framerate 25 -f x11grab -i $DISPLAY.0+100,55 output.mp4
