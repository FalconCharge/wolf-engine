#include <stdio.h>
#include <iostream>
#include "wolf.h"

#include "SampleRunner.h"
#include "sampleClipSpace.h"
#include "sampleClipSpaceColors.h"
#include "sampleOrtho.h"
#include "samplePerspective.h"
#include "sampleWorldTransform.h"

class Game: public wolf::App
{
public:
    Game() : App("Hello Game!!")
    {
        m_sampleRunner.addSample(new SampleClipSpace(this));
        m_sampleRunner.addSample(new SampleClipSpaceColors(this));
        m_sampleRunner.addSample(new SampleOrtho(this));
        m_sampleRunner.addSample(new SamplePerspective(this));
        m_sampleRunner.addSample(new SampleWorldTransform(this));
    }

    ~Game()
    {
    }

    void Update(float dt) override
    {
        if(isKeyDown(' '))
        {
            m_lastDown = true;
        }
        else if(m_lastDown)
        {
            m_sampleRunner.nextSample();
            m_lastDown = false;
        }

        m_sampleRunner.update(dt);
    }

    void Render() override
    {
        m_sampleRunner.render(m_width, m_height);
    }

private:
    SampleRunner m_sampleRunner;
    bool m_lastDown = false;
};