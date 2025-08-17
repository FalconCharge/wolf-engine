#pragma once

#include "core/Transform.h"
#include "core/Component.h"

#include <vector>
#include <string>
#include <memory>

namespace wolf
{
	class GameObject
	{
	public:
		GameObject();
		~GameObject();

		void Update(float deltaTime);
		void Render();

		void AddComponent(Component* component);
		void RemoveComponent(Component* component);

        // Getters
        const std::string& GetName() const { return m_name; }
        const std::string& GetTag() const { return m_tag; }
        Transform& GetTransform() { return m_transform; }
        const int GetID() const { return m_id; }

        void SetParent(GameObject* parent);

        //setters
        void SetName(const std::string& name) { m_name = name; }
        void SetTag(const std::string& tag) { m_tag = tag; }
        void SetTransform(const Transform& transform) { m_transform = transform; }
        void SetID(int id) { m_id = id; }

	private:

        std::string m_name = "null";
        std::string m_tag = "null";
		Transform m_transform;
        std::vector<std::unique_ptr<Component>> m_components;

        int m_id = 0;


	};
}