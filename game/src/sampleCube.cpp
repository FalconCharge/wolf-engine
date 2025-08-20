#include "sampleCube.h"

SampleCube::~SampleCube()
{
}

void SampleCube::init()
{
    m_DebugCube = DebugCube();
}

void SampleCube::update(float dt)
{
    m_DebugCube.Update(dt);
}

void SampleCube::render(int width, int height)
{

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_DebugCube.Render();
}
