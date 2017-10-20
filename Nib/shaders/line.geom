#version 150

uniform float thickness;
uniform vec2 winSize;

layout(lines) in;
layout(triangle_strip, max_vertices=4) out;

in vec4 vColor[];

out vec2 start;
out vec2 end;

void main(void)
{
	// get the vertices passed to the shader:
	vec2 p0 = gl_in[0].gl_Position.xy * winSize/2;
	vec2 p1 = gl_in[1].gl_Position.xy * winSize/2;

	// center segment
	vec2 v1 = normalize(p1-p0);
	vec2 n1 = vec2(-v1.y, v1.x);
	
	// setup outputs
	start = p0+winSize/2;
	end = p1+winSize/2;
	
	// calculate output points
	vec2 out0 = p0+(-v1+n1)*thickness;
	vec2 out1 = p0+(-v1-n1)*thickness;
	vec2 out2 = p1+(v1+n1)*thickness;
	vec2 out3 = p1+(v1-n1)*thickness;

	// generate the triangle strip
	gl_FrontColor = vColor[0];
	gl_Position = vec4(out0*2/winSize, 0.0, 1.0);
	EmitVertex();

	gl_FrontColor = vColor[0];
	gl_Position = vec4(out1*2/winSize, 0.0, 1.0);
	EmitVertex();

	gl_FrontColor = vColor[1];
	gl_Position = vec4(out2*2/winSize, 0.0, 1.0);
	EmitVertex();

	gl_FrontColor = vColor[1];
	gl_Position = vec4(out3*2/winSize, 0.0, 1.0);
	EmitVertex();

	EndPrimitive();
}
