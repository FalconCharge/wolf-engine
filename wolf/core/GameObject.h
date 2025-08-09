#pragma once

#include "core/Transform.h"
#include "core/Component.h"

#include <vector>

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

	private:
		Transform m_transform;
		std::vector<Component*> m_components;
	};
}