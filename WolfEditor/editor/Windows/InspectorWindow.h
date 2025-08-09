#pragma once
#include "../ImguiWindow.h"
#include <vector>
#include <string>
#include "core/GameObjectManager.h"
#include <memory>

class InspectorWindow : public ImguiWindow
{
public:
    InspectorWindow(const std::vector<std::unique_ptr<wolf::GameObject>>& gameObjects, int selected);

protected:
    void DrawContent() override;

private:
    const std::vector<std::unique_ptr<wolf::GameObject>>& m_gameObjects;
    int m_selectedIndex;
};
