#include "CollisionSystem.h"
#include "Subject.h"

void dae::CollisionSystem::AddCollider(RectColliderComponent* colliderRect)
{
	m_Colliders.push_back(colliderRect);
}

void dae::CollisionSystem::RemoveCollider(RectColliderComponent* colliderRect)
{
	m_Colliders.erase(std::remove(m_Colliders.begin(), m_Colliders.end(), colliderRect), m_Colliders.end());
}

void dae::CollisionSystem::CheckCollisions()
{
	for (const auto& collider : m_Colliders)
	{
		for(const auto& otherCollider : m_Colliders)
		{
			if (collider == otherCollider) continue; // Skip self-collision
			if (OverlappingRects(collider->GetBoundingBoxInWorld(), otherCollider->GetBoundingBoxInWorld()))
			{
				m_OnHit.NotifyObservers(GameEvent::Collision, collider->GetOwner());
			}
		}
	}
}

bool dae::CollisionSystem::OverlappingRects(const Rect& rect1, const Rect& rect2)
{
	if(rect1.x < rect2.x + rect2.width &&
		rect1.x + rect1.width > rect2.x &&
		rect1.y < rect2.y + rect2.height &&
		rect1.y + rect1.height > rect2.y)
	{
		return true;
	}
	return false;
}
