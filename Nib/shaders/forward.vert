out vec4 vColor;

void main()
{
    // transform the vertex position
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    // forward the vertex color
	vColor = gl_Color;
}