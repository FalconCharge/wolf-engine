#pragma once
#include "wolf.h"
#include "Sample.h"

class SampleClipSpaceColors: public Sample
{
public:
    SampleClipSpaceColors(wolf::App* pApp) : Sample(pApp,"Full Screen Clip Space with Colors") {}
    ~SampleClipSpaceColors();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    GLuint m_program = 0;
    GLuint m_vboVerts = 0;
    GLuint m_vboColors = 0;
    GLuint m_vao = 0;
};
