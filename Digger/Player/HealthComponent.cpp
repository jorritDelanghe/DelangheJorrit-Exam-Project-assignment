#include "HealthComponent.h"
#include "Subject.h"
#include "GameObject.h"
#include "Scene/Event.h"


dae::HealthComponent::HealthComponent(GameObject* gameObject, int lives)
	:Component(gameObject)
	,m_lives{lives}
	
{
}

void dae::HealthComponent::Update(float deltaTime)
{
	if (m_isHit)
	{
		m_cooldownTimer += deltaTime;
		constexpr float maxCooldown{ 1.f }; 
		if (m_cooldownTimer >= maxCooldown)
		{
			m_isHit = false;
			m_cooldownTimer = 0.f;
		}
	}
}

void dae::HealthComponent::Notify(GameEvent event, GameObject* pGameObject )
{
	if (pGameObject != Component::GetOwner()) return;

	if ((event == GameEvent::CollisionEnemy 
		|| event == GameEvent::CollisionFallingBag) 
		&& !m_isHit)
	{
		Die();
		m_isHit = true;
		m_cooldownTimer = 0.f;
	}
}
void dae::HealthComponent::Die()
{
	if (m_lives <= 0) return;
	--m_lives;
	m_onDied.NotifyObservers(GameEvent::PlayerDied, Component::GetOwner());
}

void dae::HealthComponent::Health(int lives)
{
	if (lives < 0)return;
	m_lives = lives;
	m_onDied.NotifyObservers(GameEvent::HealthChanged, Component::GetOwner());
}
