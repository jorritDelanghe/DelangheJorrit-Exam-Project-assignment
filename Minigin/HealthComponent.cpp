#include "HealthComponent.h"
#include "Subject.h"
#include "GameObject.h"
#include "Event.h"

dae::HealthComponent::HealthComponent(GameObject* gameObject, int lives)
	:Component(gameObject)
	,m_lives{lives}
	
{
}

void dae::HealthComponent::Die()
{
	if (m_lives < 0) return;
	--m_lives;
	m_onDied.NotifyObservers(GameEvent::PlayerDied, Component::GetOwner());
}
