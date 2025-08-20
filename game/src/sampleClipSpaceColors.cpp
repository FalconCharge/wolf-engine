#include "sampleClipSpaceColors.h"
#include "Grid2D.h"

static const GLfloat gs_squareVertices[] = {
	-1.0f,  -1.0f,
	 1.0f,  -1.0f,
	-1.0f,   1.0f,
	
	-1.0f,   1.0f,
	 1.0f,  -1.0f,
	 1.0f,   1.0f,
};

static const GLubyte gs_squareColors[] = {
	255,   255, 0, 255, //yellow
	0,     255, 0, 255, //green
	255,     0, 0, 255, //red
	
	0,     0, 255, 255, //blue
	255,   0, 255, 255, //magenta
	0,   255, 255, 255, //cyan
};

SampleClipSpaceColors::~SampleClipSpaceColors()
{
	printf("Destroying Clip Space with Colors Sample\n");
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vboVerts);
	glDeleteBuffers(1, &m_vboColors);
	glDeleteProgram(m_program);
}

void SampleClipSpaceColors::init()
{
    // Only init if not already done
    if(!m_program)
    {
        m_program = wolf::LoadShaders("data/clipSpaceColors.vsh", "data/clipSpaceColors.fsh");

        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        // Create VBO for vertices
        glGenBuffers(1, &m_vboVerts);
        glBindBuffer(GL_ARRAY_BUFFER, m_vboVerts);

        glBufferData(GL_ARRAY_BUFFER, // Vertex Data
                     8 * 6,           // The total size of the buffer, in bytes
                     gs_squareVertices,  // Pointer to the data to copy over to VRAM
                     GL_STATIC_DRAW); // Hint to the driver for how it’ll be used.

        // Create VBO for colors
        glGenBuffers(1, &m_vboColors);
        glBindBuffer(GL_ARRAY_BUFFER, m_vboColors);

        glBufferData(GL_ARRAY_BUFFER, // Vertex Data
                     4 * 6,           // The total size of the buffer, in bytes
                     gs_squareColors, // Pointer to the data to copy over to VRAM
                     GL_STATIC_DRAW); // Hint to the driver for how it’ll be used.

        // Set attribute pointers
        int iPosAttr = glGetAttribLocation(m_program, "a_position");
        int iColAttr = glGetAttribLocation(m_program, "a_color");

        glBindBuffer(GL_ARRAY_BUFFER, m_vboVerts);
        glVertexAttribPointer(iPosAttr, // Attribute location
                              2,        // Number of components
                              GL_FLOAT, // Type of each component
                              GL_FALSE, // Normalize?
                              0,        // Stride
                              0);       // Offset
        glEnableVertexAttribArray(iPosAttr);

        glBindBuffer(GL_ARRAY_BUFFER, m_vboColors);
        glVertexAttribPointer(iColAttr,         // Attribute location
                              4,                // Number of components
                              GL_UNSIGNED_BYTE, // Type of each component
                              GL_TRUE,          // Normalize?
                              0,                // Stride
                              0);               // Offset
        glEnableVertexAttribArray(iColAttr);
    }

    printf("Successfully initialized Clip Space with Colors Sample\n");
}

void SampleClipSpaceColors::update(float dt) 
{
}

void SampleClipSpaceColors::render(int width, int height)
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use shader program.
    glUseProgram(m_program);
    
    glBindVertexArray(m_vao);
    
    // Draw!
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

