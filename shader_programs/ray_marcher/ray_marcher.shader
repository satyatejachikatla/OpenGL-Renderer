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

#define MAX_DIST        100.
#define MAX_STEPS       100
#define SURF_DIST       .01

float GetDist(vec3 p){
	vec4 s = vec4(0.,1.,6.,1.);
	vec4 s2 = vec4(2.1,1.,6.,1.);

	float sphereDist = length(p-s.xyz) - s.w;
	float sphereDist2 = length(p-s2.xyz) - s2.w;
	float planeDist = p.y;

	float d = min(min(sphereDist,planeDist),sphereDist2);

	return d;

}

float RayMarch(vec3 ro,vec3 rd){
	float dO = 0;

	for(int i=0;i<MAX_STEPS;i++){
		vec3 p = ro+rd*dO;
		float dS = GetDist(p);
		dO += dS;
		if(dO > MAX_DIST || dS < SURF_DIST) break;
	}

	return dO;
} 

vec3 GetNormal(vec3 p){
	float d = GetDist(p);
	vec2 e = vec2(0.01,0.);

	vec3 n = d- vec3(
			GetDist(p-e.xyy),
			GetDist(p-e.yxy),
			GetDist(p-e.yyx));

	return normalize(n);
}

float GetLight(vec3 p){
	vec3 lightPosition = vec3(0.,5.,6.);
	float t = u_Time*2.;
	lightPosition.xz = vec2(3.*sin(t),2.*cos(t));
	vec3 l = normalize(lightPosition-p);
	vec3 n = GetNormal(p);

	float diff = clamp(dot(n,l),0.,1.);

	float d = RayMarch(p+n*SURF_DIST*1.2,l);
	if (d<length(lightPosition-p)) diff *= .1;

	return diff;
}


void main()
{
	vec2 fragCoords = v_position.xy;
	vec2 uv = (fragCoords-.5*u_Resolution.xy)/u_Resolution.y;
	vec2 mouse = (u_Mouse-0.5*u_Resolution)/u_Resolution.y;

	float t = u_Time;
/*camera start*/
	float zoom = 1.;
	vec3 ro = vec3(-0.,1.,-0);
	vec3 lookat = vec3(mouse,1.);
	vec3 u_world = vec3(0.,1.,0.);
	vec3 f = normalize(lookat-ro);
	vec3 r = cross(u_world,f);
	vec3 u = cross(f,r);

	vec3 c = ro + f*zoom;
	vec3 i = c + uv.x*r + uv.y*u;

	vec3 rd = normalize(i-ro);
/*camera end*/

	vec3 col = vec3(1.);
	float d = RayMarch(ro,rd);

	vec3 p = ro+rd*d;

	float diff = GetLight(p);
	col = vec3(diff);

	fragColor = vec4(col,1.);
}