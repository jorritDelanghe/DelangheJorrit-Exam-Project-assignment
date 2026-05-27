#pragma once
#include "Component.h"
#include "Subject.h"
#include "Observer.h"

namespace dae
{
	class GameObject;
	class HealthComponent : public Component, public Observer
	{
	public:
		explicit HealthComponent(GameObject* gameObject, int lives);
		virtual ~HealthComponent()override = default;

		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

		virtual void Update(float deltaTime) override;
		virtual void Notify(GameEvent event, GameObject* gameObject) override;
		void Die();
		int GetLives() const { return m_lives; }
		Subject& OnDied() { return m_onDied;  }

	private:
		int m_lives{};
		dae::Subject m_onDied{};
		float m_cooldownTimer{};
		bool m_isHit{ false };
	};

}