#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class GridComponent;
	class GoldBagComponent;
	class GoldBagState
	{
	public:
		virtual ~GoldBagState() = default;
		virtual GoldBagState* HandleInputs(GoldBagComponent* /*goldBagComponent*/, GridComponent* /*grid*/, glm::vec3 /*playerPos*/) { return nullptr; }
		virtual GoldBagState* Update(GoldBagComponent* /*goldBagComponent*/, float /*deltaTime*/) { return nullptr;  }
	};

}