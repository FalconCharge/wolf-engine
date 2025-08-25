#include "core/Transform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <algorithm>
#include <string>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

namespace wolf{
    // Constructor
    Transform::Transform() : m_Position{0.0f, 0.0f, 0.0f}, m_Rotation{0, 0, 0, 1}, m_Scale{1.0f, 1.0f, 1.0f}, m_Parent(nullptr) {}

    Transform::~Transform() {
        // Clean up children
        m_Children.clear();
        m_Parent = nullptr;
    }


    void Transform::SetParent(Transform* parent) {
        // Remove from old parent
        if (m_Parent) {
            auto& siblings = m_Parent->m_Children;
            siblings.erase(std::remove(siblings.begin(), siblings.end(), this), siblings.end());
        }

        m_Parent = parent;

        // Add to new parent
        if (m_Parent) {
            m_Parent->m_Children.push_back(this);
        }
    }

    Transform* Transform::GetParent() const {
        return m_Parent;
    }
    std::vector<Transform*> const& Transform::GetChildren() const {
        return m_Children;
    }  

    glm::mat4 Transform::GetLocalMatrix() const {
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_Position);
        glm::mat4 rotationMat = glm::toMat4(m_Rotation);
        glm::mat4 scaleMat    = glm::scale(glm::mat4(1.0f), m_Scale);

        return translation * rotationMat * scaleMat;
    }

    glm::mat4 Transform::GetWorldMatrix() const {
        if (m_Parent) {
            return m_Parent->GetWorldMatrix() * GetLocalMatrix();
        }
        return GetLocalMatrix();
    }


    // Setters
    void Transform::SetPosition(const glm::vec3& position) {
        m_Position = position;
    }
    void Transform::SetRotation(const glm::quat& rotation) {
        m_Rotation = rotation;
    }
    void Transform::SetScale(const glm::vec3& scale) {
        m_Scale = scale;
    }

    // Getters
    const glm::vec3& Transform::GetPosition() const { 
        return m_Position; 
    }

    const glm::quat& Transform::GetRotation() const {
        return m_Rotation;
    }

    const glm::vec3& Transform::GetScale() const {
        return m_Scale;
    }

    // Getters for world positions
    glm::vec3 Transform::GetWorldPosition() const {
        if (m_Parent) {
            // Apply parent's rotation & scale to our local position
            return m_Parent->GetWorldPosition() +
                   m_Parent->GetWorldRotation() * (m_Parent->GetWorldScale() * m_Position);
        }
        return m_Position;
    }

    glm::quat Transform::GetWorldRotation() const {
        if (m_Parent) {
            return m_Parent->GetWorldRotation() + m_Rotation;
        }
        return m_Rotation;
    }


    glm::vec3 Transform::GetWorldScale() const {
        if (m_Parent) {
            return m_Parent->GetWorldScale() * m_Scale;
        }
        return m_Scale;
    }

    

    void Transform::DebugString() const {
        std::cout << "Transform Debug Info:\n";
        std::cout << "Children Count: " << m_Children.size() << "\n";
        std::cout << "Position: " << m_Position.x << ", " << m_Position.y << ", " << m_Position.z << "\n";
        std::cout << "Rotation: " << m_Rotation.x << ", " << m_Rotation.y << ", " << m_Rotation.z << ", " << m_Rotation.w << "\n";
        std::cout << "Scale: " << m_Scale.x << ", " << m_Scale.y << ", " << m_Scale.z << "\n";
        std::cout << "World Position: " << GetWorldPosition().x << ", " << GetWorldPosition().y << ", " << GetWorldPosition().z << "\n";
        std::cout << "World Rotation: " << GetWorldRotation().x << ", " << GetWorldRotation().y << ", " << GetWorldRotation().z << ", " << GetWorldRotation().w << "\n";
        std::cout << "World Scale: " << GetWorldScale().x << ", " << GetWorldScale().y << ", " << GetWorldScale().z << "\n";
        std::cout << std::endl;
    }
}