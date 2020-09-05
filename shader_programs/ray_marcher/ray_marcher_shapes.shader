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

float sdCapsule(vec3 p,vec3 a,vec3 b ,float r) {
	vec3 ab = b-a;
	vec3 ap = p-a;

	float t = dot(ab,ap)/dot(ab,ab);
	t = clamp(t,0.,1.);

	vec3 c = a + t*ab;
	return length(p-c) - r;

}

float sdTorus(vec3 p,vec2 r) {
	float x = length(p.xz) - r.x;

	return length(vec2(x,p.y)) - r.y;

}

float dbox(vec3 p,vec3 s){
	return length(max(abs(p) -s,0) );
}

float sdCylinder(vec3 p,vec3 a,vec3 b ,float r) {
	vec3 ab = b-a;
	vec3 ap = p-a;

	float t = dot(ab,ap)/dot(ab,ab);
	//t = clamp(t,0.,1.);

	vec3 c = a + t*ab;

	float x = length(p-c)-r;
	float y = (abs(t-.5)-.5)*length(ab);
	float e = length(max(vec2(x,y),0.));

	float i = min(max(x,y),0);

	return e + i;

}

float GetDist(vec3 p) {
	vec4 s = vec4(0.,1.,6.,1.);

	// Sphere Example
	float sphereDist = length(p-s.xyz) - s.w;
	float planeDist = p.y;

	// Capsule Example
	float cd = sdCapsule(p,vec3(0.,1.,6.),vec3(1.,2.,2.),.2);

	// Torus Example
	float td = sdTorus(p-vec3(.0,.5,6.),vec2(1.5,.25));

	// Box Example
	float bd = dbox(p-vec3(-2.5,.5,6.),vec3(.75));

	// Cylinder Example

	float cyld = sdCylinder(p-vec3(.5,.5,.5),vec3(0.,.3,.0),vec3(1.,2.,2.),.1);

	float d;
	d = min(cd,planeDist);
	d = min(d,sphereDist);
	d = min(d,td);
	d = min(d,bd);
	d = min(d,cyld);

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
	vec2 mouse = (u_Mouse-.5*u_Resolution)/u_Resolution.y;

	mouse = 3. *vec2(mouse.x,-mouse.y) ;


	float t = u_Time;
/*camera start*/
	float zoom = 1.;
	vec3 ro = vec3(-1.,2.,-1);
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

//./shader_programs/ray_marcher/ray_marcher_shapes.shader