#pragma once
#include "../ImguiWindow.h"
#include "core/GameObjectManager.h"
#include <string>
#include <memory>

class HierarchyWindow : public ImguiWindow
{
    public:
        HierarchyWindow(const std::vector<std::unique_ptr<wolf::GameObject>>& gameObjects, int selected);

    protected:
        void DrawContent() override;

    private:
        const std::vector<std::unique_ptr<wolf::GameObject>>& m_gameObjects;
        int m_selectedIndex;
};
