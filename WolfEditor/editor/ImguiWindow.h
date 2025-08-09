#pragma once
#include <imgui.h>

class ImguiWindow
{
public:
    ImguiWindow(const char* name)
        : m_Name(name)
    {}

    virtual ~ImguiWindow() = default;

    // Call this every frame to draw the window
    void Draw()
    {
        ImGui::Begin(m_Name);
        DrawContent();
        ImGui::End();
    }

protected:
    // Derived classes implement this with their specific ImGui UI
    virtual void DrawContent() = 0;

private:
    const char* m_Name;
};
