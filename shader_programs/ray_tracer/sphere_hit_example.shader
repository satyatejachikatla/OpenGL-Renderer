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

vec4 hitSphere(vec3 ro,vec3 rd,vec3 S,float r){
	float l = dot(S-ro,rd);
	float d = length(ro-S+l*rd);

	float t = sqrt(r*r - d*d);

	//Return color based on normal
	return t >= 0 ? vec4(abs(S-ro-(l-t)*rd),1.) : vec4(.0) ;
}

void main()
{
	vec2 fragCoords = v_position.xy;
	vec2 uv = (fragCoords-.5*u_Resolution.xy)/u_Resolution.y;
	vec2 mouse = (u_Mouse-0.5*u_Resolution)/u_Resolution.y;

	//uv.x = abs(uv.x);

	float t = u_Time;

	float zoom = 1.;

	vec3 ro = vec3(3.*sin(t),2.,-3*cos(t));
	vec3 lookat = vec3(mouse,0.);
	vec3 u_world = vec3(0.,1.,0.);
	vec3 f = normalize(lookat-ro);
	vec3 r = cross(u_world,f);
	vec3 u = cross(f,r);

	vec3 c = ro + f*zoom;
	vec3 i = c + uv.x*r + uv.y*u;

	vec3 rd = normalize(i-ro);

	vec4 col = vec4(0.);

	vec4 sphere1 = hitSphere(ro,rd,vec3(-2.0,0.0,0.0),1.);
	vec4 sphere2 = hitSphere(ro,rd,vec3(2.0,0.0,0.0),1.);

	col += mix(col,sphere1,sphere1.a);
	col += mix(col,sphere2,sphere2.a);

	fragColor = col;
}


//ffmpeg -video_size 900x500 -framerate 25 -f x11grab -i $DISPLAY.0+100,55 output.mp4
