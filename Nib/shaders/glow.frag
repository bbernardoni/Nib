uniform float thickness;

in vec2 start;
in vec2 end;

float distToLine(vec2 test)
{
	float dx = end.x - start.x;
	float dy = end.y - start.y;
	float sdx = test.x - start.x;
	float sdy = test.y - start.y;
	float edx = test.x - end.x;
	float edy = test.y - end.y;
	
	// beyond start
	if(-dy*sdy > dx*sdx){
		return sqrt(sdy*sdy + sdx*sdx);
	}
	// beyond end
	if(dy*edy > -dx*edx){
		return sqrt(edy*edy + edx*edx);
	}
	return abs(dy*test.x - dx*test.y + end.x*start.y - end.y*start.x) / sqrt(dy*dy + dx*dx);
}

void main()
{
	vec4 pixel = gl_Color;
	vec4 pos = gl_FragCoord;

	float dist = distToLine(pos.xy);

	if(dist > thickness){
		pixel.a = 0.0;
	} else {
		float intencity = dist / thickness;
		pixel.a = mix(1.0, 0.0, intencity);
	}

    gl_FragColor = pixel;
}