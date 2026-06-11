#include "EmeraldManagerComponent.h"

dae::EmeraldManagerComponent::EmeraldManagerComponent(GameObject* gameObject)
	:Component(gameObject)
{

}

void dae::EmeraldManagerComponent::Notify(GameEvent event, GameObject* gameObject)
{
	if (event == GameEvent::CollisionEmerald)
	{
		++m_collectedEmeraldCount;
		if (m_collectedEmeraldCount >= m_totalEmeraldCount)
		{
			m_OnAllEmeraldsCollected.NotifyObservers(GameEvent::AllEmeraldsCollected, gameObject);
		}
	}
}

void dae::EmeraldManagerComponent::AddEmerald()
{
	++m_totalEmeraldCount;
}
