#pragma once
#include "Component.h"
#include <glm/glm.hpp>
namespace dae
{
	class TransformComponent final : public Component
	{
	public:
		TransformComponent() = default;
		virtual ~TransformComponent() override = default;

		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;

		//setters
		void SetPosition(const glm::vec2& pos);
		void SetPosition(float x, float y);
		void SetRotation(float rot);
		void SetScale(const glm::vec2& scale);
		void SetScale(float x, float y);

		//getter
		const glm::vec2& GetPosition() const;
		float GetRotation() const;
		const glm::vec2& GetScale() const;

	private:
		glm::vec2  m_position{}; //2D game 
		float m_rotation{};
		glm::vec2 m_scale{ 1.0f, 1.0f };

	};
}