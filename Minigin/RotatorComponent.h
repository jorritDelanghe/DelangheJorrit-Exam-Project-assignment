#pragma once
#include "Component.h"
#include "GameObject.h"

namespace dae
{
	class RotatorComponent final : public Component
	{
	public:
		RotatorComponent(GameObject* pOwner, float speed, float radius);
		virtual ~RotatorComponent() override = default;

		virtual void Update(float deltaTime) override;

		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent& operator=(const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;
	private:
		float m_speed;
		float m_radius;
		float m_angle;

	};
}
