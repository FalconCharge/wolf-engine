#pragma once

#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

#include "ImguiWindow.h"

#include "core/GameObjectManager.h"

#include <vector>
#include <memory>



class Imgui{

    public:
        explicit Imgui(GLFWwindow* window): m_window(window){}

        void Init(wolf::GameObjectManager* gameObjectManager);
        void Shutdown();
        void NewFrame();
        void Render();
        void AddWindow(ImguiWindow* window);
        ImguiWindow* FindWindow(const std::string& name) const;

        std::vector<ImguiWindow*>& GetWindows() { return m_imguiWindows; }

    private:
        GLFWwindow* m_window;
        ImGuiIO* m_io;

        std::vector<ImguiWindow*> m_imguiWindows;

        // Methods
        void DrawMainMenuBar();
        void DrawDockSpace();

    };