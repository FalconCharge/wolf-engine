#include "editorCamera.h"

EditorCamera::EditorCamera(float fov, float aspect, float nearClip, float farClip)
    : Camera(nullptr), m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_Up(glm::vec3(0.0f, 1.0f, 0.0f)),
      m_Yaw(-90.0f), m_Pitch(0.0f), m_Speed(5.0f), m_Sensitivity(0.1f)
{
    SetPosition(glm::vec3(0.0f, 0.0f, 10.0f));
    SetAspect(aspect);
}