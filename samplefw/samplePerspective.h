#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"

class SamplePerspective: public Sample
{
public:
    SamplePerspective(wolf::App* pApp) : Sample(pApp,"Perspective Projection") {}
    ~SamplePerspective();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    GLuint m_program = 0;
    GLuint m_vboVerts = 0;
    GLuint m_vboColors = 0;
    GLuint m_vao = 0;
};

