#pragma once
#include "GoldBagState.h"

namespace dae
{
	class MovingState : public GoldBagState
	{
	public:
		MovingState(float moveSpeed);
		virtual ~MovingState() override = default;
		virtual void HandleInputs(GoldBagComponent* goldBagComponent, GridComponent* grid, glm::vec3 playerPos) override;
		virtual void Update(GoldBagComponent* goldBagComponent, float deltaTime) override;
	private:
		struct GridPos
		{
			int row;
			int col;

		};
		float m_moveSpeed{};
		GridPos m_gridPosGoldBag{};
		glm::vec3 m_newPosition{};
		glm::vec3 m_oldPlayerPos{};
		bool m_isDirty{ false };

	};

}