#include "core/GameObject.h"

namespace wolf{
	GameObject::GameObject()
	{

    }

	GameObject::~GameObject()
	{
	}

	void GameObject::Update(float deltaTime)
	{
		// for (const auto& component : m_components)
		// {
		// 	component->Update(deltaTime);
		// }

	}

	void GameObject::Render()
	{
		this->Render();
	}


    void GameObject::AddComponent(Component* component)
    {
        //m_components.emplace_back(component);
    }



	void GameObject::RemoveComponent(Component* component)
	{
        // m_components.erase(std::remove_if(m_components.begin(), m_components.end(),
        //     [component](const std::unique_ptr<Component>& obj) {
        //         return obj.get() == component;
        //     }), m_components.end());
	}

	void GameObject::SetParent(GameObject* parent)
	{
		if (parent)
		{
			m_transform.SetParent(&parent->GetTransform());
		}
	}
}