#include "CollisionUpdaterComponent.h"
#include <Windows.h>
#include "Scene/Event.h"
#include "Goldbag/GoldBagComponent.h"
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

		//get tags
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

		//get player otherwise a lot of extra code
		GameObject* player{};
		if (colliderTag == CollisionTag::Player || otherColliderTag == CollisionTag::Player)
		{
			player = (colliderTag == CollisionTag::Player) ? collider->GetOwner() : otherCollider->GetOwner();
		}

		//colision player with...
		if (player)
		{
			if (compareTags(CollisionTag::Player, CollisionTag::Enemy))
			{
				CollisionSystem::GetInstance().OnHitSubject().NotifyObservers(GameEvent::CollisionEnemy, player);
			}
			if (compareTags(CollisionTag::Player, CollisionTag::Border))
			{
				CollisionSystem::GetInstance().OnHitSubject().NotifyObservers(GameEvent::CollisionWall, player);
			}
			if (compareTags(CollisionTag::Player, CollisionTag::GoldBag))
			{
				GameObject* goldBagObject = (colliderTag == CollisionTag::GoldBag) ?
					collider->GetOwner() : otherCollider->GetOwner();

				auto* goldBagComponent = goldBagObject->GetComponent<GoldBagComponent>();

				if (goldBagComponent) //if goldbag is falling, player dies
				{
					goldBagComponent->HandleInput(player->GetLocalPosition());
				}
			}
			if (compareTags(CollisionTag::Player, CollisionTag::Emerald))
			{
				//emerald needs to be destroyed
				GameObject* emeraldObject = (colliderTag == CollisionTag::Emerald) ? 
					collider->GetOwner() : otherCollider->GetOwner();
				if (!emeraldObject->IsMarkedForDelete()) //if already picked up, dont send event again
				{
					CollisionSystem::GetInstance().OnHitSubject().NotifyObservers(GameEvent::CollisionEmerald, emeraldObject);
				}
			}
			if (compareTags(CollisionTag::Player, CollisionTag::GoldNugget))
			{
				GameObject* goldNuggetObject = (colliderTag == CollisionTag::GoldNugget) ?
					collider->GetOwner() : otherCollider->GetOwner();
				if (!goldNuggetObject->IsMarkedForDelete()) //if already picked up, dont send event again
				{
					CollisionSystem::GetInstance().OnHitSubject().NotifyObservers(GameEvent::CollisionGoldNugget, goldNuggetObject);
				}
			}
		}

		//collision Golbag with...
		if (compareTags(CollisionTag::Player, CollisionTag::FallingGoldBag)
			|| compareTags(CollisionTag::Enemy, CollisionTag::FallingGoldBag))
		{
			auto* victim = (colliderTag == CollisionTag::FallingGoldBag) ? otherCollider->GetOwner() : collider->GetOwner();
			CollisionSystem::GetInstance().OnHitSubject().NotifyObservers(GameEvent::CollisionFallingBag, victim);
		}

		OutputDebugStringA("hit\n");
	}
}