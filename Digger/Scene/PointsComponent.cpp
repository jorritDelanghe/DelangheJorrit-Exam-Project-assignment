#include "PointsComponent.h"
#include "GameObject.h"
#include "Event.h"

dae::PointsComponent::PointsComponent(GameObject* gameObject)
	:Component(gameObject)
{
}

void dae::PointsComponent::Notify(GameEvent event, GameObject* pGameObject)
{
	if (event == GameEvent::CollisionEmerald)
	{
		pGameObject->MarkForDelete();
		AddEmerad();
	}
	if (event == GameEvent::CollisionEmerald)
	{
		constexpr int goldNuggetPoints{ 50 };
		pGameObject->MarkForDelete();
		AddScore(goldNuggetPoints);
	}
}

void dae::PointsComponent::AddEmerad()
{
	constexpr int streakMax{ 5 };
	constexpr int streakBonus{ 100 };
	constexpr int emeraldPoints{ 20 };

	++m_emeraldStreak;
	AddScore(emeraldPoints);

	if (m_emeraldStreak >= streakMax)
	{
		AddScore(streakBonus);
		m_emeraldStreak = 0;
	}
}

void dae::PointsComponent::AddScore(int points)
{
	m_score += points;
	m_onPointsChanged.NotifyObservers(GameEvent::PlayerPickedUp, Component::GetOwner());
}
