#pragma once
#include "../ImguiWindow.h"
#include "core/GameObjectManager.h"
#include <string>
#include <memory>


class HierarchyWindow : public ImguiWindow
{
    public:
        HierarchyWindow(const std::vector<std::unique_ptr<wolf::GameObject>>& gameObjects, int selected);

        void SetInspectorWindow(ImguiWindow* inspectorWindow) { m_inspectorWindow = inspectorWindow; }

    protected:
        void DrawContent() override;
        void WindowSetup() override;

    private:
        // Members
        const std::vector<std::unique_ptr<wolf::GameObject>>& m_gameObjects;
        int m_selectedIndex;
        ImguiWindow* m_inspectorWindow = nullptr;

        // Methods
        void DrawGameObjectNode(wolf::GameObject* go, int index);
};
