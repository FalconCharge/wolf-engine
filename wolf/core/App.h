// ------------------------------------------------------------
// File: App.h
// Class: App
// Brief: Core Application class for wolf engine
//        Where the engine runs
// Author: Ben Harper
// Date: 2025-09-06
// ------------------------------------------------------------




#pragma once
#define GLEW_NO_GLU
#include "Types.h"
#include <string>

#include "EngineStats.h"

namespace wolf
{
    class App
    {
    public:
        App(const std::string &name);
        virtual ~App();

        virtual void Run();
        virtual void Update(float dt) = 0;
        virtual void Render() = 0;


        GLFWwindow* getWindow() const { return m_pWindow; }

    protected:
        int m_width = 0;
        int m_height = 0;

    private:
        void _init();
        void _internalUpdate(float dt);

        GLFWwindow *m_pWindow = nullptr;
        std::string m_name;

    };
}