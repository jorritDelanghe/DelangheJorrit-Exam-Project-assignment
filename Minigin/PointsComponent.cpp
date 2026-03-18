#include "PointsComponent.h"
#include "GameObject.h"
#include "Event.h"

dae::PointsComponent::PointsComponent(GameObject* gameObject)
	:Component(gameObject)
{
}

void dae::PointsComponent::AddScore(int points)
{
	m_score += points;
	m_onPointsChanged.NotifyObservers(GameEvent::PlayerPickedUp, Component::GetOwner());
}
