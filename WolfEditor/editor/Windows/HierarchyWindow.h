#pragma once
#include "../ImguiWindow.h"
#include "core/GameObjectManager.h"
#include <string>
#include <memory>


class HierarchyWindow : public ImguiWindow
{
    public:
        HierarchyWindow(int selected);

        void SetInspectorWindow(ImguiWindow* inspectorWindow) { m_inspectorWindow = inspectorWindow; }

    protected:
        void DrawContent() override;
        void WindowSetup() override;

    private:
        // Members
        int m_selectedIndex;
        ImguiWindow* m_inspectorWindow = nullptr;


        // Methods
        void DrawGameObjectNode(wolf::GameObject* go, int index);
};
