#pragma once
#pragma once

#include <glm/glm.hpp>
#include "GoldBagState.h"
namespace dae
{
	class GoldBagComponent;
	class GridComponent;
	class WaitingToFallState : public GoldBagState
	{
	public:
		WaitingToFallState(float maxTimeToWait, float fallSpeed);
		virtual ~WaitingToFallState() override = default;

		virtual GoldBagState* Update(GoldBagComponent* goldBagComponent, float deltaTime) override;
	private:

		float m_maxTimeToWait{};
		float m_fallSpeed{};
		float m_timerTunnelUnderGoldBag{};
	};

}