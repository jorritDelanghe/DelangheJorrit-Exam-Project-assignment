#pragma once
#include "Singleton.h"
#include <vector>
#include "RectColliderComponent.h"
#include "Subject.h"
//singleton pattern
//dynamic objects only use (static objects handled by grid
namespace dae
{

	class CollisionSystem final : public Singleton<CollisionSystem>
	{
		friend class Singleton<CollisionSystem>; //creates static the instance
	public:

		struct CollidedObjects
		{
			RectColliderComponent* Object1{};
			RectColliderComponent* Object2{};
		};

		void AddCollider(RectColliderComponent* colliderRect);
		void RemoveCollider(RectColliderComponent* colliderRect);
		size_t GetNumberOfBoundingBoxes() const { return m_Colliders.size(); }

		void ClearCollideders();

		//sends vector that will be interpreted in the CollisionUpdaterComponent and send events to the observers
		std::vector <CollidedObjects> CheckCollisions();
		Subject<GameEvent>& OnHitSubject() { return m_OnHit; }

	private:
		CollisionSystem() = default;
		static bool OverlappingRects(const Rect& rect1, const Rect& rect2);

		std::vector<RectColliderComponent*> m_Colliders;
		dae::Subject<GameEvent> m_OnHit{};
	};
}