#pragma once

#include "core/GameObject.h"

namespace wolf
{
	class GameObjectManager
	{
	public:
		GameObjectManager();
		~GameObjectManager();

		void Update(float deltaTime);
		void Render();

		GameObject* CreateGameObject();
		void DestroyGameObject(GameObject* gameObject);

	private:
		std::vector<GameObject*> m_gameObjects;
	};
}
