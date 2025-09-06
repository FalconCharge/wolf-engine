// ------------------------------------------------------------
// Class: Inspector
// Brief: The Inspector Is used with Imgui; And is meant to display the Components attached to a certain GO
//          The values to to change are setup in the GO's not Here
// Author: Ben Harper
// Date: 2025-09-06
// ------------------------------------------------------------
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
