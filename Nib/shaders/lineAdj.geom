#version 150

uniform float thickness;
uniform vec2 winSize;

layout(lines_adjacency) in;
layout(triangle_strip, max_vertices=4) out;

in vec4 vColor[];

out vec2 start;
out vec2 end;

void main(void)
{
	// get the four vertices passed to the shader:
	vec2 p0 = gl_in[0].gl_Position.xy * winSize/2;
	vec2 p1 = gl_in[1].gl_Position.xy * winSize/2;
	vec2 p2 = gl_in[2].gl_Position.xy * winSize/2;
	vec2 p3 = gl_in[3].gl_Position.xy * winSize/2;

	// center segment
	vec2 v1 = normalize(p2-p1);
	vec2 n1 = vec2(-v1.y, v1.x);
	
	// previous segment
	vec2 offset_a;
	if(p0 != p1){
		vec2 v0 = normalize(p1-p0);
		vec2 n0 = vec2(-v0.y, v0.x);
		vec2 miter_a = normalize(n0+n1);
		float length_a = thickness/dot(miter_a, n1);
		offset_a = length_a*miter_a;
	}else{
		offset_a = thickness*n1;
	}

	// next segment
	vec2 offset_b;
	if(p2 != p3){
		vec2 v2 = normalize(p3-p2);
		vec2 n2 = vec2(-v2.y, v2.x);
		vec2 miter_b = normalize(n1+n2);
		float length_b = thickness/dot(miter_b, n1);
		offset_b = length_b*miter_b;
	}else{
		offset_b = thickness*n1;
	}

	// setup outputs
	start = p1+winSize/2;
	end = p2+winSize/2;

	// generate the triangle strip
	gl_FrontColor = vColor[1];
	gl_Position = vec4((p1+offset_a)*2/winSize, 0.0, 1.0);
	EmitVertex();

	gl_FrontColor = vColor[1];
	gl_Position = vec4((p1-offset_a)*2/winSize, 0.0, 1.0);
	EmitVertex();

	gl_FrontColor = vColor[2];
	gl_Position = vec4((p2+offset_b)*2/winSize, 0.0, 1.0);
	EmitVertex();

	gl_FrontColor = vColor[2];
	gl_Position = vec4((p2-offset_b)*2/winSize, 0.0, 1.0);
	EmitVertex();

	EndPrimitive();
}
