uniform mat4 projection;
uniform mat4 view;
in vec4 a_position;
in vec4 a_color;
out vec4 v_color;

void main()
{
    gl_Position = projection * view * a_position;
	v_color = a_color;
}
