#pragma once

#include "Sample.h"
#include "debugCube.h"

class SampleCube : public Sample
{
public:
    SampleCube(wolf::App* pApp) : Sample(pApp,"Sample Cube") {}
    ~SampleCube();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:

    DebugCube m_DebugCube;

};
