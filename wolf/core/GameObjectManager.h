	#pragma once

	#include "core/GameObject.h"
	#include "objects/debugCube.h"
	#include <iostream>

	namespace wolf
	{
		class GameObjectManager
		{
		public:
			GameObjectManager();
			~GameObjectManager();

			void Update(float deltaTime);
			void Render();
			
			template <typename T, typename... Args>
			T* CreateGameObject(Args&&... args)
			{
				static_assert(std::is_base_of<GameObject, T>::value,
							"T must inherit from GameObject");

				auto obj = std::make_unique<T>(std::forward<Args>(args)...);
				if (obj->GetName().empty()) obj->SetName("GameObject_" + std::to_string(m_nextId++));
				
				T* rawPtr = obj.get();
				m_gameObjects.push_back(std::move(obj));
				return rawPtr;
			}

			void DestroyGameObject(GameObject* gameObject);

			// Find a game object by its name
			GameObject* FindGameObjectByName(const std::string& name);

			// return a ref to the list of game objects
			const std::vector<std::unique_ptr<GameObject>>& GetGameObjects() const;

			void GameObjectManager::DebugPrint() const;

			YAML::Node Serialize() const;
			void Deserialize(const YAML::Node& node);

		private:

			std::vector<std::unique_ptr<GameObject>> m_gameObjects;

			// ID's for the GOs'
			std::size_t m_nextId = 0; 

		};
	}
