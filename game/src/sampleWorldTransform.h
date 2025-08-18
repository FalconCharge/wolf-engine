#pragma once
#include "wolf.h"
#include "Sample.h"

class SampleWorldTransform: public Sample
{
public:
    SampleWorldTransform(wolf::App* pApp) : Sample(pApp,"3D World Transform") {}
    ~SampleWorldTransform();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    GLuint m_program = 0;
    GLuint m_vboVerts = 0;
    GLuint m_vboColors = 0;
    GLuint m_vao = 0;
    float m_currRot = 0.0f;
};


