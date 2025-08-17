#include "samplePerspective.h"
#include "../samplefw/Grid2D.h"

static const GLfloat gs_triangleVertices[] = {
	-1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
};

static const GLubyte gs_triangleColors[] = {
	255,   255, 0, 255, //yellow
	0,     255, 0, 255, //green
	255,     0, 0, 255, //red
};

SamplePerspective::~SamplePerspective()
{
	printf("Destroying Perspective Sample\n");
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vboVerts);
	glDeleteBuffers(1, &m_vboColors);
	glDeleteProgram(m_program);
}

void SamplePerspective::init()
{
    // Only init if not already done
    if(!m_program)
    {
        m_program = wolf::LoadShaders("data/perspective.vsh", "data/perspective.fsh");

        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        // Create VBO for vertices
        glGenBuffers(1, &m_vboVerts);
        glBindBuffer(GL_ARRAY_BUFFER, m_vboVerts);

        glBufferData(GL_ARRAY_BUFFER,  // Vertex Data
                     12 * 3,           // The total size of the buffer, in bytes
                     gs_triangleVertices, // Pointer to the data to copy over to VRAM
                     GL_STATIC_DRAW);  // Hint to the driver for how it’ll be used.

        // Create VBO for colors
        glGenBuffers(1, &m_vboColors);
        glBindBuffer(GL_ARRAY_BUFFER, m_vboColors);

        glBufferData(GL_ARRAY_BUFFER, // Vertex Data
                     4 * 3,           // The total size of the buffer, in bytes
                     gs_triangleColors,  // Pointer to the data to copy over to VRAM
                     GL_STATIC_DRAW); // Hint to the driver for how it’ll be used.

        // Set attribute pointers
        int iPosAttr = glGetAttribLocation(m_program, "a_position");
        int iColAttr = glGetAttribLocation(m_program, "a_color");

        glBindBuffer(GL_ARRAY_BUFFER, m_vboVerts);
        glVertexAttribPointer(iPosAttr, // Attribute location
                              3,        // Number of components
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

    printf("Successfully initialized Perspective Sample\n");
}

void SamplePerspective::update(float dt) 
{
}

void SamplePerspective::render(int width, int height)
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use shader program.
    glUseProgram(m_program);
    
	glm::mat4 mProj = glm::perspective(glm::radians(60.0f), (float)width / (float)height, 0.1f, 1000.0f);
	glm::mat4 mView = glm::lookAt(glm::vec3(0.0f,0.0f,4.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
	
	glUniformMatrix4fv(glGetUniformLocation(m_program,"projection"), 1, GL_FALSE, glm::value_ptr(mProj));
	glUniformMatrix4fv(glGetUniformLocation(m_program,"view"), 1, GL_FALSE, glm::value_ptr(mView));
	
    glBindVertexArray(m_vao);
    
    // Draw!
    glDrawArrays(GL_TRIANGLES, 0, 3);
}


