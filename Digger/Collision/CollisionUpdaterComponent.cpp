#include "CollisionUpdaterComponent.h"
#include <Windows.h>
#include "Scene/Event.h"
#include "gameObject.h"
dae::CollisionUpdaterComponent::CollisionUpdaterComponent(GameObject* pOwner)
	:Component(pOwner)
{
#ifndef NDEBUG
	CollisionSystem::GetInstance().RegisterUpdaterComp(); 
#endif
}
dae::CollisionUpdaterComponent::~CollisionUpdaterComponent()
{
#ifndef NDEBUG
	CollisionSystem::GetInstance().UnRegisterUpdaterComp();
#endif
}
void dae::CollisionUpdaterComponent::Update(float)
{
	//skip first frame to avoid checking collisions before all colliders are added to the system
	if (m_firstFrame)
	{
		m_firstFrame = false; 
		return;
	}

	auto collisions = CollisionSystem::GetInstance().CheckCollisions();
	collisions.reserve(CollisionSystem::GetInstance().GetNumberOfBoundingBoxes());

	for (const auto& [collider, otherCollider] : collisions)
	{
		if (!collider || !otherCollider) continue;

		CollisionTag colliderTag = collider->GetTag();
		CollisionTag otherColliderTag = otherCollider->GetTag();

		//checkswhich collision happened
		auto compareTags = [colliderTag, otherColliderTag](CollisionTag tag1, CollisionTag tag2)
			{
				if ((colliderTag == tag1 && otherColliderTag == tag2) ||
					(colliderTag == tag2 && otherColliderTag == tag1))
				{
					return true;
				}
				return false;
			};

		if (compareTags(CollisionTag::Player, CollisionTag::Enemy))
		{
			CollisionSystem::GetInstance().OnHitSubject().NotifyObservers(GameEvent::CollisionEnemy, collider->GetOwner());
		}
		if (compareTags(CollisionTag::Player, CollisionTag::Border))
		{
			CollisionSystem::GetInstance().OnHitSubject().NotifyObservers(GameEvent::CollisionWall, collider->GetOwner());
		}
		if (compareTags(CollisionTag::Player, CollisionTag::GoldBag))
		{
			CollisionSystem::GetInstance().OnHitSubject().NotifyObservers(GameEvent::CollisionGoldBag, collider->GetOwner());
		}
		if (compareTags(CollisionTag::Player, CollisionTag::Emerald))
		{
			GameObject* emeraldObject = (colliderTag == CollisionTag::Emerald) ? 
				collider->GetOwner() : otherCollider->GetOwner();
			if (!emeraldObject->IsMarkedForDelete()) //if already picked up, dont send event again
			{
				CollisionSystem::GetInstance().OnHitSubject().NotifyObservers(GameEvent::CollisionEmerald, emeraldObject);
			}
		}

		OutputDebugStringA("hit\n");
	}
}