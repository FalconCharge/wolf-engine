#pragma once


namespace wolf
{
    class GameObject;

	class Component
	{
	public:
		Component(){}
		~Component(){}

		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;

	private:
		GameObject* m_pGameObject;
	};
}
