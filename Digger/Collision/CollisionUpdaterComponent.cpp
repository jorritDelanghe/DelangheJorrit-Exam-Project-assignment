#include "CollisionUpdaterComponent.h"
#include "CollisionSystem.h"
dae::CollisionUpdaterComponent::CollisionUpdaterComponent(GameObject* pOwner)
	:Component(pOwner)
{
}
void dae::CollisionUpdaterComponent::Update(float)
{
	//skip first frame to avoid checking collisions before all colliders are added to the system
	if (m_firstFrame)
	{
		m_firstFrame = false; 
		return;
	}

	dae::CollisionSystem::GetInstance().CheckCollisions();
}