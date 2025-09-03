#include <stdio.h>
#include <iostream>

#include "GameLogic.h"
#include "core/InputManager.h"


class Game: public wolf::App
{
public:
    Game() : wolf::App("Hello Game!!")
    {
        // Sets up the Input Manager when using game executable
        wolf::InputManager::Instance().Initialize(this->getWindow());
        wolf::InputManager::Instance().SetInputEnabled(true); // Enable input for the game
        // TODO: should never shut off input for the game
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