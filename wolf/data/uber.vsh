in vec4 aPos;
in vec2 aUV;
in vec3 aNormal;

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

out vec2 vUV;

void main()
{
    //vUV = aUV;  // pass UVs to fragment shader
    vUV = aUV;
    gl_Position = projection * view * world * aPos;

        // Debug: override position with UVs in clip space
    //gl_Position = vec4(aUV * 2.0 - 1.0, 0.0, 1.0);
}
