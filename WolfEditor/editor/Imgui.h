#pragma once

#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "ImguiWindow.h"

#include "core/GameObjectManager.h"

#include <vector>
#include <memory>

#include "render/TextureManager.h"
#include "render/RenderTarget.h"



class Imgui{

    public:
        explicit Imgui(GLFWwindow* window): m_window(window){}

        void Init(wolf::GameObjectManager* gameObjectManager, wolf::RenderTarget* gameview);
        void Shutdown();
        void NewFrame();
        void Render();
        void AddWindow(ImguiWindow* window);
        ImguiWindow* FindWindow(const std::string& name) const;

        std::vector<ImguiWindow*>& GetWindows() { return m_imguiWindows; }

        wolf::Texture* m_gameViewTex;


    private:
        GLFWwindow* m_window;
        ImGuiIO* m_io;

        std::vector<ImguiWindow*> m_imguiWindows;
        wolf::RenderTarget* m_gameViewFramebuffer;

        // Methods
        void DrawMainMenuBar();
        void DrawDockSpace();

    };