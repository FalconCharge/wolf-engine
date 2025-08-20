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

			// Find a game object by its name
			GameObject* FindGameObjectByName(const std::string& name);

			// return a ref to the list of game objects
			const std::vector<std::unique_ptr<GameObject>>& GetGameObjects() const;

		private:

			std::vector<std::unique_ptr<GameObject>> m_gameObjects;

		};
	}
