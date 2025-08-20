#include <stdio.h>
#include <iostream>

#include "GameLogic.h"


class Game: public wolf::App
{
public:
    Game() : wolf::App("Hello Game!!")
    {
    }


    void Update(float dt) override
    {
        m_logic.Update(dt, this);
    }

    void Render() override
    {
        m_logic.Render(m_width, m_height);
    }


private:
    GameLogic m_logic;
};