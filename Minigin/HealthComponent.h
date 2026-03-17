#pragma once
#include "Component.h"
#include "Subject.h"

namespace dae
{
	class GameObject;
	class HealthComponent : public Component
	{
	public:
		explicit HealthComponent(GameObject* gameObject, int lives);
		virtual ~HealthComponent()override = default;

		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

		void Die();
		int GetLives() const { return m_lives; }
		Subject& OnDied() { return m_onDied;  }

	private:
		int m_lives{};
		bool m_isDead{ false };
		dae::Subject m_onDied{};
	};

}