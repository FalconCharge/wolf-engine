#include "sampleClipSpace.h"
#include "../samplefw/Grid2D.h"

static const GLfloat gs_squareVertices[] = {
	-1.0f,  -1.0f,
	 1.0f,  -1.0f,
	-1.0f,   1.0f,
	
	-1.0f,   1.0f,
	 1.0f,  -1.0f,
	 1.0f,   1.0f,
};

SampleClipSpace::~SampleClipSpace()
{
	printf("Destroying Clip Space Sample\n");
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteProgram(m_program);
}

void SampleClipSpace::init()
{
    // Only init if not already done
    if(!m_program)
    {
		m_program = wolf::LoadShaders("data/clipSpace.vsh", "data/clipSpace.fsh");

		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);
		
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		
		glBufferData(GL_ARRAY_BUFFER, // Vertex Data
					8 * 6,  // The total size of the buffer, in bytes
					gs_squareVertices, // Pointer to the data to copy over to VRAM
					GL_STATIC_DRAW); // Hint to the driver for how it’ll be used.
		
		// Set attribute pointers
		int iPosAttr = glGetAttribLocation(m_program, "a_position");
		glVertexAttribPointer(iPosAttr, // Attribute location
							2,		// Number of components
							GL_FLOAT, // Type of each component
							GL_FALSE, // Normalize?
							0,		// Stride
							0);		// Offset
		glEnableVertexAttribArray(iPosAttr);
    }

    printf("Successfully initialized Clip Space Sample\n");
}

void SampleClipSpace::update(float dt) 
{
}

void SampleClipSpace::render(int width, int height)
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use shader program.
    glUseProgram(m_program);
    
	glBindVertexArray(m_vao);
    
    // Draw!
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
