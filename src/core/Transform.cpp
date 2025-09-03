#include "core/Transform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <algorithm>
#include <string>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

namespace wolf{
    // Constructor
    Transform::Transform() : m_Position{0.0f, 0.0f, 0.0f}, m_Rotation{0, 0, 0, 1}, m_Scale{1.0f, 1.0f, 1.0f}, m_Parent(nullptr) {
        m_Dirty = true;
    }

    Transform::~Transform() {
        // Clean up children
        m_Children.clear();
        m_Parent = nullptr;
    }


    void Transform::SetParent(Transform* parent) {
        m_Dirty = true;
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

    glm::mat4 Transform::GetLocalMatrix() {
        if(m_Dirty){
            glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_Position);
            glm::mat4 rotationMat = glm::toMat4(m_Rotation);
            glm::mat4 scaleMat    = glm::scale(glm::mat4(1.0f), m_Scale);

            m_transform = translation * rotationMat * scaleMat;
            m_Dirty = false;
        }
        return m_transform;
    }

    glm::mat4 Transform::GetWorldMatrix() {
        if (m_Parent) {
            return m_Parent->GetWorldMatrix() * GetLocalMatrix();
        }
        return GetLocalMatrix();
    }


    // Setters
    void Transform::SetPosition(const glm::vec3& position) {
        m_Dirty = true;
        m_Position = position;
    }
    void Transform::SetRotation(const glm::quat& rotation) {
        m_Dirty = true;
        m_Rotation = rotation;
    }
    void Transform::SetScale(const glm::vec3& scale) {
        m_Dirty = true;
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

    YAML::Node Transform::Serialize() const {
        YAML::Node node;

        // Position
        node["Position"].push_back(m_Position.x);
        node["Position"].push_back(m_Position.y);
        node["Position"].push_back(m_Position.z);

        // Rotation
        node["Rotation"].push_back(m_Rotation.x);
        node["Rotation"].push_back(m_Rotation.y);
        node["Rotation"].push_back(m_Rotation.z);
        node["Rotation"].push_back(m_Rotation.w);

        // Scale
        node["Scale"].push_back(m_Scale.x);
        node["Scale"].push_back(m_Scale.y);
        node["Scale"].push_back(m_Scale.z);

        return node;
    }


    void Transform::Deserialize(const YAML::Node& node) {
        if (node["Position"] && node["Position"].IsSequence() && node["Position"].size() == 3) {
            m_Position.x = node["Position"][0].as<float>();
            m_Position.y = node["Position"][1].as<float>();
            m_Position.z = node["Position"][2].as<float>();
        }

        if (node["Rotation"] && node["Rotation"].IsSequence() && node["Rotation"].size() == 4) {
            m_Rotation.x = node["Rotation"][0].as<float>();
            m_Rotation.y = node["Rotation"][1].as<float>();
            m_Rotation.z = node["Rotation"][2].as<float>();
            m_Rotation.w = node["Rotation"][3].as<float>();
        }

        if (node["Scale"] && node["Scale"].IsSequence() && node["Scale"].size() == 3) {
            m_Scale.x = node["Scale"][0].as<float>();
            m_Scale.y = node["Scale"][1].as<float>();
            m_Scale.z = node["Scale"][2].as<float>();
        }
    }
}