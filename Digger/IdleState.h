#pragma once

#include <glm/glm.hpp>
#include "GoldBagState.h"
namespace dae
{
	class GoldBagComponent;
	class GridComponent;
	class IdleState : public GoldBagState
	{
	public:
		IdleState() = default;
		virtual ~IdleState() override = default;

		virtual GoldBagState* HandleInputs(GoldBagComponent* goldBagComponent, GridComponent* grid, glm::vec3 playerPos) override;
	private:
	};

}