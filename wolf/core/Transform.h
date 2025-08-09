#pragma once

namespace wolf
{
	class Transform
	{
	public:
		Transform();
		~Transform();

		void SetPosition(const glm::vec3& position);
		void SetRotation(const glm::quat& rotation);
		void SetScale(const glm::vec3& scale);

		glm::vec3 GetPosition() const;
		glm::quat GetRotation() const;
		glm::vec3 GetScale() const;

	private:
		glm::vec3 m_position;
		glm::quat m_rotation;
		glm::vec3 m_scale;
	};
}
