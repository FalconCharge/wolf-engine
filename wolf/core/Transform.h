#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>
#include <memory>
#include <algorithm> // for std::remove

#include <yaml-cpp/yaml.h>

namespace wolf {

class GameObject; // Forward declaration

class Transform {
public:
    Transform();
    ~Transform();

    // --- Parent/Child system ---
    void SetParent(Transform* parent);
    Transform* GetParent() const;
    const std::vector<Transform*>& GetChildren() const;

	void SetOwner(GameObject* owner) {
		m_Owner = owner;
	}
	GameObject* GetOwner() const {
		return m_Owner;
	}

    // --- Matrices ---
    glm::mat4 GetLocalMatrix();
    glm::mat4 GetWorldMatrix();

    // --- Local space getters ---
    const glm::vec3& GetPosition() const;
    const glm::quat& GetRotation() const;
    const glm::vec3& GetScale() const;

    // --- World space getters ---
    glm::vec3 GetWorldPosition() const;
    glm::quat GetWorldRotation() const;
    glm::vec3 GetWorldScale() const;

    // --- Local space setters ---
    void SetPosition(const glm::vec3& position);
    void SetRotation(const glm::quat& rotation);
    void SetScale(const glm::vec3& scale);

    // Debug helper
    void DebugString() const;

    // Serialization
    YAML::Node Serialize() const;
    void Deserialize(const YAML::Node& node);

private:
    glm::vec3 m_Position {0.0f, 0.0f, 0.0f};
    glm::vec3 m_Scale    {1.0f, 1.0f, 1.0f};
    glm::quat m_Rotation {0, 0, 0, 1};

    Transform* m_Parent = nullptr;
    std::vector<Transform*> m_Children;
    GameObject* m_Owner = nullptr;

    bool m_Dirty;
    glm::mat4 m_transform;
};

} // namespace wolf
