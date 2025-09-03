#pragma once
#include <imgui.h>

class ImguiWindow
{
public:
    ImguiWindow(const char* name)
        : m_Name(name)
    {
        m_IsVisible = true;
    }
    ImguiWindow(const char* name, ImguiWindow* parent, ImGuiWindowFlags flags)
        : m_Name(name), m_Parent(parent), m_Flags(flags)
    {
        m_IsVisible = true;
    }

    virtual ~ImguiWindow() = default;

    // Call this every frame to draw the window
    void Draw()
    {
        if (!m_IsVisible) return;   // Skip if not visible

        WindowSetup();
        ImGui::SetNextWindowDockID(ImGui::GetID("MainDockSpace"), ImGuiCond_FirstUseEver);
        ImGui::Begin(m_Name, nullptr, m_Flags);
        DrawContent();
        ImGui::End();
    }

    const char* GetName() const { return m_Name; }

    bool IsVisible() const { return m_IsVisible; }
    void SetVisible(bool visible) { m_IsVisible = visible; }


protected:
    // Derived classes implement this with their specific ImGui UI
    virtual void DrawContent() = 0;
    virtual void WindowSetup() = 0;

private:
    const char* m_Name;
    ImguiWindow* m_Parent = nullptr;
    ImGuiWindowFlags m_Flags = 0;

    bool m_IsVisible;
};
