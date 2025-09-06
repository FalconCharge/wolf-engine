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
		std::cout << "Deleting Game Object Manager " << std::endl;
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

	GameObject* GameObjectManager::FindGameObjectByName(const std::string& name)
	{
		for (const auto& gameObject : m_gameObjects)
		{
			if (gameObject->GetName() == name)
			{
				return gameObject.get();
			}
		}
		std::cout << "ERROR: Could not find Game Object" << std::endl;
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
	 void GameObjectManager::Shutdown(){
		// Clear the vector, releasing all unique_ptrs
		m_gameObjects.clear();
	}

	void GameObjectManager::Render(glm::mat4 view, glm::mat4 proj)
	{
		for (std::vector<std::unique_ptr<GameObject>>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
		{
			(*it)->Render(view, proj);
		}
	}


	const std::vector<std::unique_ptr<GameObject>>& GameObjectManager::GetGameObjects() const {
    	return m_gameObjects;
	}

	void wolf::GameObjectManager::DebugPrint() const
	{
		std::cout << "=== GameObjectManager Debug ===\n";
		std::cout << "Total GameObjects: " << m_gameObjects.size() << "\n";

		for (size_t i = 0; i < m_gameObjects.size(); ++i)
		{
			const auto& obj = m_gameObjects[i];
			if (!obj) continue;

			std::cout << "[" << i << "] " 
					<< obj->GetName() 
					<< " @ " << obj.get();

			if (obj->GetTransform().GetParent())
			 	std::cout << " (Child of " << obj->GetTransform().GetParent()->GetOwner()->GetName() << ")";
			
			std::cout << "\n";
		}
		std::cout << "===============================\n";
	}


	YAML::Node GameObjectManager::Serialize() const {
		YAML::Node node;
		for (const auto& gameObject : m_gameObjects) {
			node["GameObjects"].push_back(gameObject->Serialize());
		}
		return node;
	}

	void GameObjectManager::Deserialize(const YAML::Node& node) {
		if (node["GameObjects"] && node["GameObjects"].IsSequence()) {
			for (const auto& objNode : node["GameObjects"]) {
				std::unique_ptr<wolf::GameObject> gameObject;

				// Check the type and create the appropriate GameObject subclass if needed
				std::string type = "GameObject";	// Default type
				if (objNode["Type"]){
					type = objNode["Type"].as<std::string>();
				}

				// Create the correct subclass based on type
				if (type == "class DebugCube") {
					gameObject = std::make_unique<DebugCube>();
				} else {
					gameObject = std::make_unique<GameObject>();
				}

				gameObject->Deserialize(objNode);
				m_gameObjects.push_back(std::move(gameObject));
			}
		}
	}
}
