#include "CollisionSystem.h"
#include "Scene/Event.h"
#include "Subject.h"
#include <Windows.h>
#include <string>

void dae::CollisionSystem::AddCollider(RectColliderComponent* colliderRect)
{
#ifndef NDEBUG
	if (m_hasUpdaterCollsionComp == false)
	{
		OutputDebugStringA("Warning: Adding collider without CollisionUpdaterComponent in the scene, collisions wont be updated\n");
	}
#endif
	m_Colliders.push_back(colliderRect);
}

void dae::CollisionSystem::RemoveCollider(RectColliderComponent* colliderRect)
{
	if (m_Colliders.empty()) return;
	m_Colliders.erase(std::remove(m_Colliders.begin(), m_Colliders.end(), colliderRect), m_Colliders.end());
}

void dae::CollisionSystem::ClearCollideders()
{
	m_Colliders.clear();
}

std::vector <dae::CollisionSystem::CollidedObjects>  dae::CollisionSystem::CheckCollisions()
{
	std::vector<CollidedObjects> collisions;
	collisions.reserve(m_Colliders.size());

	for (const auto& collider : m_Colliders)
	{
		for(const auto& otherCollider : m_Colliders)
		{
			if (!collider || !otherCollider) continue;
			if (collider == otherCollider) continue; // Skip self-collision
			if (OverlappingRects(collider->GetBoundingBoxInWorld(), otherCollider->GetBoundingBoxInWorld()))
			{
				collisions.push_back({ collider, otherCollider });
			}
		}
	}

	return collisions;
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
