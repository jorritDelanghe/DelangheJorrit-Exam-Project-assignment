#pragma once

#include "GoldBagState.h"
namespace dae
{
	class FallingState : public GoldBagState
	{
	public:
		FallingState(float fallSpeed);
		virtual ~FallingState() override = default;
		virtual GoldBagState* Update(GoldBagComponent* goldBagComponent, float deltaTime) override;
	private :
		float m_fallSpeed{};
		float m_fallDistance{};
	};

}