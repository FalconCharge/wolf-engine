#include "HierarchyWindow.h"
#include <imgui.h>
#include <memory>
#include <cstring>
#include <iostream>
#include "core/SceneManager.h"

#include "InspectorWindow.h"

#include "src/debugCube.h"

HierarchyWindow::HierarchyWindow(const std::vector<std::unique_ptr<wolf::GameObject>>& gameObjects, int selected)
    : ImguiWindow("Hierarchy"),
     m_gameObjects(gameObjects), m_selectedIndex(selected)
{

}
void HierarchyWindow::WindowSetup(){
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImVec2 viewportPos = viewport->Pos;   // top-left corner
    ImVec2 viewportSize = viewport->Size; // width and height

    // LEFT: Hierarchy
    // Yes we have some magic numbers sorry
    ImVec2 hierarchyPos = ImVec2(viewportPos.x + 1, viewportPos.y + 33);
    ImVec2 hierarchySize = ImVec2(300, viewportSize.y - 300);

    //ImGui::SetNextWindowPos(hierarchyPos, ImGuiCond_Once);
    //ImGui::SetNextWindowSize(hierarchySize, ImGuiCond_Once);
}
void HierarchyWindow::DrawContent()
{

    // Right-click anywhere in the Hierarchy window
if (ImGui::BeginPopupContextWindow(nullptr, ImGuiPopupFlags_MouseButtonRight))
{
    if (ImGui::MenuItem("Create Empty GameObject"))
    {
        auto* scene = wolf::SceneManager::Instance().GetActiveScene();
        if (scene)
        {
            auto* manager = scene->GetGameObjectManager();
            if (manager)
            {
                auto* go = manager->CreateGameObject<DebugCube>();
                if (go)
                    go->SetName("New GameObject");
            }
            else
            {
                std::cerr << "ERROR: Scene has no GameObjectManager\n";
            }
        }
        else
        {
            std::cerr << "ERROR: No active scene!\n";
        }
    }
    ImGui::EndPopup();
}



    for (size_t i = 0; i < m_gameObjects.size(); ++i)
    {
        wolf::GameObject* go = m_gameObjects[i].get();
        if (!go->GetTransform().GetParent()) // Only draw roots
        {
            DrawGameObjectNode(go, (int)i);            
        }
        
    }

}

void HierarchyWindow::DrawGameObjectNode(wolf::GameObject* go, int index)
{
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
    if (index == m_selectedIndex)
        flags |= ImGuiTreeNodeFlags_Selected;

    bool opened = ImGui::TreeNodeEx((void*)(intptr_t)index, flags, go->GetName().c_str());

    if (ImGui::IsItemClicked()) {
        m_selectedIndex = index;
        if (m_inspectorWindow) {
            if (auto inspector = dynamic_cast<InspectorWindow*>(m_inspectorWindow))
            {
                inspector->SetSelectedGameObject(index);
            }
        }
    }

    if (opened)
    {
        for (wolf::Transform* child : go->GetTransform().GetChildren())
        {
            // Find the GameObject that owns this Transform
            wolf::GameObject* childGO = child->GetOwner();


            int childIndex = -1;
            for (size_t i = 0; i < m_gameObjects.size(); ++i)
            {
                if (m_gameObjects[i].get() == childGO)
                {
                    childIndex = (int)i;
                    break;
                }
            }

            DrawGameObjectNode(childGO, childIndex);
        }

        ImGui::TreePop();
    }
}

