#pragma once
#include "../ImguiWindow.h"
#include <vector>
#include <string>
#include "core/SceneManager.h"
#include <memory>

class InspectorWindow : public ImguiWindow
{
public:
    InspectorWindow(int selected);
    void SetSelectedGameObject(int index) { m_selectedIndex = index; }

protected:
    void DrawContent() override;
    void WindowSetup() override;

private:
    int m_selectedIndex;
};
