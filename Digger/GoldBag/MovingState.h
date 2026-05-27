#pragma once
#include "GoldBagState.h"
#include "DataTypes.h"

namespace dae
{
	class MovingState : public GoldBagState
	{
	public:
		MovingState(float moveSpeed);
		virtual ~MovingState() override = default;
		virtual GoldBagState* HandleInputs(GoldBagComponent* goldBagComponent, GridComponent* grid, glm::vec3 playerPos) override;
		virtual GoldBagState* Update(GoldBagComponent* goldBagComponent,float deltaTime) override;
	private:
		
		float m_moveSpeed{};
		glm::vec3 m_newPosition{};
		bool m_hasMoved{ false };

	};

}