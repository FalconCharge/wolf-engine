in vec2 vUV;
out vec4 FragColor;

uniform sampler2D u_albedoTex;

void main()
{
    FragColor = texture(u_albedoTex, vUV);
}

