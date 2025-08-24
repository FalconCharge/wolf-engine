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

	// Generic factory method for any GameObject type
	// template <typename T, typename... Args>
	// T* CreateGameObject(Args&&... args)
	// {
	// 	static_assert(std::is_base_of<GameObject, T>::value, 
	// 					"T must inherit from GameObject");

	// 	auto obj = std::make_unique<T>(std::forward<Args>(args)...);
	// 	T* rawPtr = obj.get();
	// 	m_gameObjects.push_back(std::move(obj));
	// 	return rawPtr;
	// }

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

	GameObject* GameObjectManager::FindGameObjectByName(const std::string& name)
	{
		for (const auto& gameObject : m_gameObjects)
		{
			if (gameObject->GetName() == name)
			{
				return gameObject.get();
			}
		}
		return nullptr;
	}

	void GameObjectManager::Update(float deltaTime)
	{
		for (std::vector<std::unique_ptr<GameObject>>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
		{
			(*it)->Update(deltaTime);
			// Ensure the transform's world matrix is updated if it has no parent
			if (!(*it)->GetTransform().GetParent()) {
				(*it)->GetTransform().GetWorldMatrix();
			}

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
