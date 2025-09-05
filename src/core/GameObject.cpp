#include "core/GameObject.h"
#include <iostream>
namespace wolf{
	GameObject::GameObject() : m_Name(""), m_transform()
	{
		m_transform.SetOwner(this);
    }

	GameObject::~GameObject()
	{
	}

	void GameObject::Update(float deltaTime)
	{
		for(auto& comp : m_Components){
			comp->Update(deltaTime);
		}

	}

	void GameObject::Render()
	{

	}

	void GameObject::SetParent(GameObject* parent)
	{
		if (parent)
		{
			m_transform.SetParent(&parent->GetTransform());
		}else{
			// Remove the parent
			m_transform.SetParent(nullptr);
		}
	}

	YAML::Node GameObject::Serialize() const
	{
		YAML::Node node;

		node["Type"] = typeid(*this).name();

		node["Name"] = m_Name;
		node["Tag"] = m_tag;
		node["ID"] = m_id;
		// Note: Transform serialization can be added here if needed
		YAML::Node transformNode;
		transformNode = m_transform.Serialize(); // Assuming Transform has a Serialize method
		
		node["Transform"] = transformNode;

		return node;
	}

	void GameObject::Deserialize(const YAML::Node& node)
	{
		if (node["Name"])
			m_Name = node["Name"].as<std::string>();
		if (node["Tag"])
			m_tag = node["Tag"].as<std::string>();
		if (node["ID"])
			m_id = node["ID"].as<int>();

		if (node["Transform"])
			m_transform.Deserialize(node["Transform"]); // Assuming Transform has a Deserialize method

		Init();		
	}
}