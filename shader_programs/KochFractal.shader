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

layout(location = 0) out vec4 fragColor;

in vec4 v_position;
in vec3 v_color;

uniform float u_Time;
uniform vec2 u_Resolution;
uniform vec2 u_Mouse;
uniform sampler2D u_TextureChannels[5];

vec2 N(float angle) {
	return vec2(sin(angle),cos(angle));
}

void main()
{
	vec2 fragCoords = v_position.xy;
	vec2 uv = (fragCoords-.5*u_Resolution.xy)/u_Resolution.y;
	vec2 mouse = u_Mouse.xy/u_Resolution.y;

	uv *= 1.25;

	vec3 col = vec3(0);

	uv.x = abs(uv.x);
	uv.y += tan((5./6.)*3.1415)*0.5;
	// tan(a) = y / 0.5 -> tan(a) * 0.5 = y;

	vec2 n = N((5./6.)*3.1415);
	float d= dot(uv-vec2(.5,0),n);
	uv -= n*max(0.,d)*2.;

	//col += smoothstep(.01,.0,abs(d));

	n = N((2./3.)*3.1415);

	float scale = 1.;
	uv.x += .5;
	for(int i =0 ; i < 5 ; i++){
		scale*=3.;
		uv *= 3.;
		uv.x -= 1.5;

		uv.x = abs(uv.x);
		uv.x -= .5;
		uv -= n*min(0.,dot(uv,n))*2.;

	}

	d = length(uv-vec2(clamp(uv.x,-1.,1.),0));
	col += smoothstep(1/u_Resolution.y,.0,d/scale);

	//col.rg = uv;

	//col.rg = uv/scale;

	uv /= scale;
	col += texture(u_TextureChannels[0],uv*2.-u_Time*.03).rgb;

	fragColor = vec4(col,1.0);

}
