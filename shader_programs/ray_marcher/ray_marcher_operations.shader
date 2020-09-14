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
#define MAX_STEPS       1000.
#define SURF_DIST       .1

mat2 Rot(float a) {
	float s = sin(a);
	float c = cos(a);
	return mat2(c,-s,s,c);
}

float smin(float a,float b,float k) {
	float h = clamp(0.5 + 0.5*(b-a)/k,0.,1.);
	return mix(b,a,h) - k*h*(1.-h);
}

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
	return length(max(abs(p) -s,0.) );
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
	vec3 sp1 = p-vec3(0.,2.,0.);
	vec3 sp2 = p-vec3(.5,2.,0.);
	vec3 bp = p-vec3(.0,2.,.0);

	//Transformations
	bp.xz  *= Rot(u_Time);

	//bp.yz  *= Rot(u_Time);
	
	//sp1 *= vec3(sin(u_Time),1.,cos(u_Time));


	// Sphere Example
	float sd1 =  length(sp1) - 1.;
	float sd2 =  length(sp2) - 1.;

	//Plane Example
	float pd = p.y;

	// Box Example
	float bd = dbox(bp,vec3(1.));

	float d = pd;
	float special_d = mix(sd1,bd,sin(u_Time)*0.5 +0.5);
	d = min(d,special_d);
	//d = smin(d,sd2,0.5);

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
	vec3 lightPosition = vec3(2.,5.,6.);
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

	//mouse = 3. *vec2(mouse.x,-mouse.y) ;

	//float t = u_Time;
	float t = 1;
/*camera start*/
	float zoom = 1.;
	vec3 ro = vec3(5*sin(t),4.,5*cos(t));
	vec3 lookat = vec3(0.0,1.,0.0);
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

//./shader_programs/ray_marcher/ray_marcher_operations.shader