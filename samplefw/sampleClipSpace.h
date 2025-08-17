#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"

class SampleClipSpace: public Sample
{
public:
    SampleClipSpace(wolf::App* pApp) : Sample(pApp,"Full Screen Clip Space") {}
    ~SampleClipSpace();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    GLuint m_program = 0;
    GLuint m_vbo = 0;
    GLuint m_vao = 0;
};