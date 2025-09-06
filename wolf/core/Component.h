#pragma once

// Used to draw in Inspector
#include <imgui.h>

namespace wolf
{
    class GameObject;

	class Component
	{
	public:
		Component(){}
		~Component(){}

		virtual void Init() {}
		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;

		virtual void DrawInspector() = 0;

		void SetGameObjectOwner(GameObject* go){
			m_pGameObject = go;
		}

		GameObject* GetGameObjectOwner(){
			return m_pGameObject;
		}

	private:
		GameObject* m_pGameObject;
	};
}
