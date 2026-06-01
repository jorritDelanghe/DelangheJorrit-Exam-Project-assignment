#pragma once
#include "GoldBagState.h"
#include "DataTypes.h"
#include "Observer.h"
#include "Scene/Event.h"

namespace dae
{
	class MovingState : public GoldBagState //, public Observer<GameEvent>
	{
	public:
		MovingState(float moveSpeed);
		virtual ~MovingState() override = default;
		virtual GoldBagState* HandleInputs(GoldBagComponent* goldBagComponent, GridComponent* grid, glm::vec3 playerPos) override;
		//virtual void Notify(GameEvent event, GameObject* gameObject)override;
		virtual GoldBagState* Update(GoldBagComponent* goldBagComponent,float deltaTime) override;
	private:
		
		float m_moveSpeed{};
		glm::vec3 m_newPosition{};
		bool m_hasMoved{ false };

	};

}