#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"

class SampleOrtho: public Sample
{
public:
    SampleOrtho(wolf::App* pApp) : Sample(pApp,"Orthographic Projection") {}
    ~SampleOrtho();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    GLuint m_program = 0;
    GLuint m_vboVerts = 0;
    GLuint m_vboColors = 0;
    GLuint m_vao = 0;
};
