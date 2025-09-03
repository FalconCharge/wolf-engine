#pragma once

#include "glm/glm.hpp"
#include <GLFW/glfw3.h>
#include <array>
#include <iostream>

namespace wolf
{
    class InputManager
    {
    public:
        static InputManager& Instance();

        void Initialize(GLFWwindow* window);
        void Update();

        void SetCursorLocked(bool locked);
        bool IsCursorLocked() const { return m_cursorLocked; }


        // Keyboard
        bool IsKeyDown(int key) const { return m_inputEnabled && m_keys[key]; }
        bool IsKeyJustDown(int key) const { return m_inputEnabled && m_keys[key] && !m_lastKeys[key]; }

        // Keyboard Raw versions (ignore m_inputEnabled)
        bool IsKeyDownRaw(int key) const { return m_keys[key]; }
        bool IsKeyJustDownRaw(int key) const { return m_keys[key] && !m_lastKeys[key]; }

        // Mouse Buttons
        bool IsLMBDown() const { return IsMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT); }
        bool IsRMBDown() const { return IsMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT); }
        bool IsMMBDown() const { return IsMouseButtonDown(GLFW_MOUSE_BUTTON_MIDDLE); }

        // Raw Versions
        bool IsLMBDownRaw() const { return IsMouseButtonDownRaw(GLFW_MOUSE_BUTTON_LEFT); }
        bool IsRMBDownRaw() const { return IsMouseButtonDownRaw(GLFW_MOUSE_BUTTON_RIGHT); }
        bool IsMMBDownRaw() const { return IsMouseButtonDownRaw(GLFW_MOUSE_BUTTON_MIDDLE); }

        // Raw Mouse Buttons (ignore m_inputEnabled)
        bool IsMouseButtonDownRaw(int button) const { return m_mouseButtons[button]; }

        bool IsMouseButtonDown(int button) const
        {
            if (!m_inputEnabled) return false;
            return m_mouseButtons[button];
        }

        // Raw (always valid)
        glm::vec2 GetMousePositionRaw() const { return m_mousePos; }
        glm::vec2 GetMouseDeltaRaw()    const { return m_mouseDelta; }
        glm::vec2 GetMouseScrollRaw()   const { return m_scrollDelta; }

        // Filtered (only valid when input enabled)
        glm::vec2 GetMousePosition() const { return m_inputEnabled ? m_mousePos : glm::vec2(0.0f); }
        glm::vec2 GetMouseDelta()    const { return m_inputEnabled ? m_mouseDelta : glm::vec2(0.0f); }
        glm::vec2 GetMouseScroll()   const { return m_inputEnabled ? m_scrollDelta : glm::vec2(0.0f); }


        // Editor/game integration (Enable/disable input)
        void SetInputEnabled(bool enabled) { m_inputEnabled = enabled; }
        bool IsInputEnabled() const { return m_inputEnabled; }

        void DebugPrintKeysDown() const;

    private:

        InputManager() = default;

        GLFWwindow* m_window = nullptr;
        bool m_inputEnabled = true; // default: always accept input

        // Cursor lock
        bool m_cursorLocked = false;

        // Key states
        std::array<bool, GLFW_KEY_LAST + 1> m_keys{};
        std::array<bool, GLFW_KEY_LAST + 1> m_lastKeys{};

        // Mouse buttons
        std::array<bool, GLFW_MOUSE_BUTTON_LAST + 1> m_mouseButtons{};

        // Mouse pos + delta
        glm::vec2 m_mousePos{0.0f};
        glm::vec2 m_lastMousePos{0.0f};
        glm::vec2 m_mouseDelta{0.0f};

        // Scroll
        glm::vec2 m_scrollDelta{0.0f};
            

    };
}