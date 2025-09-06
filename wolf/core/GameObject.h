#pragma once

#include "core/Transform.h"
#include "core/Component.h"

#include <yaml-cpp/yaml.h>

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

        virtual void Init(){};
		virtual void Update(float deltaTime);
		virtual void Render();
        virtual std::string GetType() const {return "GameObject";}

        template<typename T, typename... Args>
        std::shared_ptr<T> AddComponent(Args&&... args) {
            auto comp = std::make_shared<T>(std::forward<Args>(args)...);
            comp->SetGameObjectOwner(this);
            m_Components.push_back(comp); // vector now holds shared_ptr<Component>
            return comp;
        }


        template<typename T>
        std::shared_ptr<T> GetComponent() {
            for (auto& c : m_Components) {
                if (auto casted = std::dynamic_pointer_cast<T>(c))
                    return casted;
            }
            return nullptr;
        }


        // Getters
        const std::string& GetName() const { return m_Name; }
        const std::string& GetTag() const { return m_tag; }
        Transform& GetTransform() { return m_transform; }
        const int GetID() const { return m_id; }
        std::vector<std::shared_ptr<Component>>& GetComponents() {return m_Components;}

        void SetParent(GameObject* parent);

        //setters
        void SetName(const std::string& name) { m_Name = name; }
        void SetTag(const std::string& tag) { m_tag = tag; }
        void SetTransform(const Transform& transform) { m_transform = transform; }
        void SetID(int id) { m_id = id; }


        // Serialization
        YAML::Node Serialize() const;
        void Deserialize(const YAML::Node& node);

	private:

        std::string m_Name = "null";
        std::string m_tag = "null";
		Transform m_transform;
        std::vector<std::shared_ptr<Component>> m_Components;

        int m_id = 0;


	};
}