uniform vec3 u_color;

in vec4 v_color;

out vec4 PixelColor;

void main()
{
    PixelColor = v_color * vec4(u_color, 1.0f);
}