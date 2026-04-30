#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class GridComponent;
	class GameObject;
	class GoldBagComponent;
	class GoldBagState
	{
	public:
		virtual ~GoldBagState() {};
		virtual void HandleInputs(GoldBagComponent* goldBagComponent, GridComponent* grid, glm::vec3 playerPos) {};
		virtual void Update(GoldBagComponent* goldBagComponent, float deltaTime) {};
	};

}