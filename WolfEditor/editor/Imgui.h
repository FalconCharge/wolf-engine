#pragma once

#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

#include "ImguiWindow.h"
#include "Windows/HierarchyWindow.h"
#include "Windows/InspectorWindow.h"

#include <vector>
#include <memory>



class Imgui{

    public:
        explicit Imgui(GLFWwindow* window): m_window(window){}

        void Init();
        void Shutdown();
        void NewFrame();
        void Render();
        void AddWindow(std::unique_ptr<ImguiWindow> window);

        std::vector<std::unique_ptr<ImguiWindow>>& GetWindows() { return m_imguiWindows; }

    private:
        GLFWwindow* m_window;
        ImGuiIO* m_io;

        std::vector<std::unique_ptr<ImguiWindow>> m_imguiWindows;

    };