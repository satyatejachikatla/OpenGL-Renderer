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

#define S(a,b,t) smoothstep(a,b,t)
#define sat(x)   clamp(x,0.,1.)

float remap01(float a,float b,float t){
	return sat((t-a)/(b-a));
}
float remap(float a,float b,float c,float d,float t){
	return sat((t-a)/(b-a))*(d-c)+c;
}

vec2 within(vec2 uv,vec4 rect){
	return (uv-rect.xy)/(rect.zw-rect.xy);
}

float mod(float x, float y)
{
  return x - y * trunc(x/y);
}

vec4 Eye(vec2 uv,float side,vec2 mouse){

	uv -= .5;
	float d = length(uv);
	vec4 irisCol = vec4(.3,.5,1.,1.);
	vec4 col = mix(vec4(1.),irisCol,S(.1,.7,d)*.5);

	col.rgb *= 1-S(.45,.5,d)*.5*sat(-uv.y-uv.x);

	col.rgb = mix(col.rgb,vec3(0.),S(.3,.28,d));

	irisCol.rgb *= 1 + S(.3,.05,d);
	col.rgb = mix(col.rgb,irisCol.rgb,S(.28,.25,d));

	col.rgb = mix(col.rgb,vec3(0.),S(.16,.14,d));


	float t=u_Time*2.;
	uv.x *= side;

	uv.x += sin(t+uv.y*15.)*.03;
	uv.y += sin(t+uv.x*7.)*.03;

	float highlight = S(.1,.09,length(uv-vec2(-.15,.15)));
	highlight += S(.07,.05,length(uv+vec2(-.08,.08)));
	col.rgb = mix(col.rgb,vec3(1.),sin(highlight));

	col.a = S(.5,.49,d);

	return col;
}

vec4 Mouth(vec2 uv,vec2 mouse){

	uv-= .5;

	uv.y*= 1.5;
	uv.y -= uv.x*uv.x*2.;

	vec4 col = vec4(.5,.18,.05,1.);

	float d= length(uv);
	col.a = S(.5,.48,d);

	float td = length(uv-vec2(0.,.6));
	vec3 toothCol = vec3(1.)*S(.6,.35,d);
	col.rgb = mix(col.rgb,toothCol,S(.4,.37,td));

	td = length(uv+vec2(0.,.5));
	col.rgb = mix(col.rgb,vec3(1.,.5,.5),S(.5,.2,td));

	return col;
}

vec4 Head(vec2 uv,vec2 mouse){

	vec4 col = vec4(.9,.65,.1,1.);

	float d = length(uv);

	col.a = S(0.5,0.49,d);
	float edgeShadow=remap01(.35,.5,d);
	edgeShadow *=edgeShadow;
	col.rgb *= 1.-edgeShadow*.5;

	col.rgb = mix(col.rgb,vec3(.6,.3,.1),S(.47,.48,d));

	float highlight = S(0.41,0.405,d);
	highlight *= remap(.41,-.1,.75,0.,uv.y);
	highlight *= S(.18,.19,length(uv-vec2(.21,.08)));
	col.rgb = mix(col.rgb,vec3(1.),highlight);

	d = length(uv - vec2(.25,-.2));
	float cheek = S(.2,.01,d)*.4;
	cheek *= S(.18,.165,d);
	col.rgb = mix(col.rgb,vec3(1.,.1,.1),cheek);
	return col;
}

vec4 Smiley(vec2 uv,vec2 mouse){

	vec4 col = vec4(0.);
	float side = sign(uv.x);
	uv.x = abs(uv.x);
	vec4 head = Head(uv,mouse);
	vec4 eye = Eye(within(uv,vec4(.03,-.1,.37,.25)),side,mouse);
	vec4 mouth = Mouth(within(uv,vec4(-.3,-.4,.3,-.1)),mouse);

	col = mix(col,head,head.a);
	col = mix(col,eye,eye.a);
	col = mix(col,mouth,mouth.a);

	return col;
}

void main()
{
	vec2 fragCoords = v_position.xy;
	vec2 uv = (fragCoords-.5*u_Resolution.xy)/u_Resolution.y;
	vec2 mouse = (u_Mouse-0.5*u_Resolution)/u_Resolution.y;
	

	fragColor = Smiley(uv,mouse);

}
