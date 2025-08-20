#pragma once

namespace wolf
{
    class InputManager
    {
    public:
        InputManager();
        ~InputManager();

        void Update();
        bool IsKeyPressed(int key) const;
        bool IsMouseButtonPressed(int button) const;

        void SetMousePosition(float x, float y);
        void GetMousePosition(float& x, float& y) const;

    private:

        float m_mouseX;
        float m_mouseY;
    };
}