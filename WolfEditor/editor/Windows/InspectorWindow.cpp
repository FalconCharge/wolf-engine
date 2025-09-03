#include "InspectorWindow.h"
#include <imgui.h>
#include <memory>
#include <cstring>

#include "glm/glm.hpp"
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>        // quat
#include <glm/gtx/quaternion.hpp>        // toMat4 (quat → mat4)

InspectorWindow::InspectorWindow(int selected)
    : ImguiWindow("Inspector"), m_selectedIndex(selected)
{}

void InspectorWindow::WindowSetup()
{
    // If you want to set the window up a certain way do it here
}

void InspectorWindow::DrawContent()
{
    auto gameObjectManager = wolf::SceneManager::Instance().GetActiveScene()->GetGameObjectManager();
    if (m_selectedIndex >= 0 && m_selectedIndex < (int)gameObjectManager->GetGameObjects().size())
    {
        ImGui::Text("Selected GameObject:");
        wolf::GameObject* go = gameObjectManager->GetGameObjects()[m_selectedIndex].get();

        ImGui::Text("%s", go->GetName().c_str());

        static char buffer[128];
        strcpy_s(buffer, go->GetName().c_str());

        if (ImGui::InputText("Name", buffer, sizeof(buffer)))
        {
            go->SetName(buffer);
        }


        // Pretty complex here: Bacially we want to edit the world transform for easier user experience
        // So We get the world matrix, decompose it, show it in ImGui, then if changed we recompose a new world matrix
        // then convert that back to local space and set the local transform of the GameObject
        ImGui::Text("Transform");

        // Step 1: Decompose WORLD matrix for ImGui display
        glm::mat4 world = go->GetTransform().GetWorldMatrix();

        glm::vec3 pos, scale, skew;
        glm::vec4 perspective;
        glm::quat rotQ;

        glm::decompose(world, scale, rotQ, pos, skew, perspective);
        glm::vec3 rot = glm::degrees(glm::eulerAngles(rotQ));

        bool changed = false;

        changed |= ImGui::DragFloat3("Position (World)", &pos.x, 0.1f);
        changed |= ImGui::DragFloat3("Rotation (World)", &rot.x, 0.5f);
        changed |= ImGui::DragFloat3("Scale (World)", &scale.x, 0.1f);

        if (changed) {
            // Step 3: Rebuild new WORLD matrix from edited values
            glm::mat4 newWorld = glm::translate(glm::mat4(1.0f), pos)
                            * glm::toMat4(glm::quat(glm::radians(rot)))
                            * glm::scale(glm::mat4(1.0f), scale);

            // Step 4: Convert back to LOCAL space (relative to parent)
            glm::mat4 local;
            if (auto* parent = go->GetTransform().GetParent()) {
                glm::mat4 parentWorld = parent->GetWorldMatrix();
                local = glm::inverse(parentWorld) * newWorld;
            } else {
                local = newWorld;
            }


            // Step 5: Update the GameObject’s LOCAL transform
            glm::vec3 lPos, lScale, lSkew;
            glm::vec4 lPerspective;
            glm::quat lRotQ;
            glm::decompose(local, lScale, lRotQ, lPos, lSkew, lPerspective);

            go->GetTransform().SetPosition(lPos);
            go->GetTransform().SetRotation(lRotQ);
            go->GetTransform().SetScale(lScale);
        }
    }
    else
    {
        ImGui::Text("No GameObject selected");
    }
}
