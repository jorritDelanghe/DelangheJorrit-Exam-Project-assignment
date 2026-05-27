#pragma once
#include "Component.h"
//used to activate the collision system, so it can check for collisions and notify the observers
namespace dae
{
	class CollisionUpdaterComponent final : public dae::Component
	{
	public:
		explicit CollisionUpdaterComponent(GameObject* pOwner);

		~CollisionUpdaterComponent() override = default;
		CollisionUpdaterComponent(const CollisionUpdaterComponent& other) = delete;
		CollisionUpdaterComponent(CollisionUpdaterComponent&& other) = delete;
		CollisionUpdaterComponent& operator=(const CollisionUpdaterComponent& other) = delete;
		CollisionUpdaterComponent& operator=(CollisionUpdaterComponent&& other) = delete;

		void virtual Update(float deltaTime) override;
	private:
		bool m_firstFrame{ true };
	};

}
