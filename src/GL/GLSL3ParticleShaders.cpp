const char *vertex_point_sprite = R"(
#version 150
 
uniform mat4 uModelViewProjection;

in vec4 aPosition;
in vec4 aColor;
 
out vec4 vColor;
 
void main() 
{
	vColor = aColor;
    gl_Position = uModelViewProjection * aPosition;
}
)";
 
const char *fragment_point_sprite = R"(
#version 150
 
in vec4 vColor;
 
out vec4 oFragColor;

void main() 
{
	oFragColor = vColor;
}
)";
