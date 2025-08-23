#pragma once

#include "Sample.h"
#include "debugCube.h"

#include "core/GameObjectManager.h"

class SampleCube : public Sample
{
public:
    SampleCube(wolf::App* pApp) : Sample(pApp,"Sample Cube") {}
    SampleCube(wolf::GameObjectManager* gom) : Sample(nullptr, "Sample Cube"){
        m_gom = gom;
    }
    ~SampleCube();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

    wolf::GameObjectManager* GetGOM(){return m_gom;}

private:

    DebugCube m_DebugCube;
    wolf::GameObjectManager* m_gom = nullptr;

};
