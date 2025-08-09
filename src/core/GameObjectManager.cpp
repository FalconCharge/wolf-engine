#include "core/GameObjectManager.h"
#include <algorithm>

namespace wolf
{
	GameObjectManager::GameObjectManager()
	{

	}
	GameObjectManager::~GameObjectManager()
	{
		// No explicit cleanup needed for unique_ptr, they will be automatically cleaned up
	}

	GameObject* GameObjectManager::CreateGameObject()
	{
		std::unique_ptr<GameObject> gameObject = std::make_unique<GameObject>();
		GameObject* rawPtr = gameObject.get();
		m_gameObjects.push_back(std::move(gameObject));
		return rawPtr;
	}

	void GameObjectManager::DestroyGameObject(GameObject* gameObject)
	{
		// Use explicit iterator type instead of auto
		std::vector<std::unique_ptr<GameObject>>::iterator it = 
			std::remove_if(m_gameObjects.begin(), m_gameObjects.end(),
			[gameObject](const std::unique_ptr<GameObject>& obj) {
				return obj.get() == gameObject;
			});
		
		if (it != m_gameObjects.end())
		{
			m_gameObjects.erase(it, m_gameObjects.end());
		}
	}

	void GameObjectManager::Update(float deltaTime)
	{
		for (std::vector<std::unique_ptr<GameObject>>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
		{
			(*it)->Update(deltaTime);
		}
	}

	void GameObjectManager::Render()
	{
		for (std::vector<std::unique_ptr<GameObject>>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
		{
			(*it)->Render();
		}
	}


	const std::vector<std::unique_ptr<GameObject>>& GameObjectManager::GetGameObjects() const {
    	return m_gameObjects;
	}

}
