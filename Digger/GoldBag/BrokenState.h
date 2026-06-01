#pragma once
#include "GoldBagState.h"
namespace dae
{
	class GoldBagComponent;
	class BrokenState : public GoldBagState
	{
	public:
		BrokenState() = default;
		virtual ~BrokenState() override = default;

		virtual GoldBagState* OnEnter(GoldBagComponent* goldBagComponent) override;
	};

}
