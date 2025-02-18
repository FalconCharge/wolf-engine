uniform mat4 MVP;  // Model-View-Projection matrix

// Input attributes
in vec2 aPos;      // Position attribute (2D position)
in vec2 aUV;

out vec2 v_uv1;

void main()
{
    gl_Position = MVP * vec4(aPos, 0.0, 1.0); // Set the position of the vertex (2D -> 4D)
    v_uv1 = aUV;           // Pass the texture coordinates to the fragment shader
}
