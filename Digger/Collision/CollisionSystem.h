#pragma once
#include "Singleton.h"
#include <vector>
#include "RectColliderComponent.h"
#include "Subject.h"
//singleton pattern

namespace dae
{

	class CollisionSystem final : public Singleton<CollisionSystem>
	{
		friend class Singleton<CollisionSystem>; //creates static the instance
	public:
		void AddCollider(RectColliderComponent* colliderRect);
		void RemoveCollider(RectColliderComponent* colliderRect);

		void CheckCollisions();
		Subject<GameEvent>& OnHitSubject() { return m_OnHit; }

	private:
		CollisionSystem() = default;
		static bool OverlappingRects(const Rect& rect1, const Rect& rect2);

		std::vector<RectColliderComponent*> m_Colliders;
		dae::Subject<GameEvent> m_OnHit{};
	};
}