#pragma once
#include "Component.h"

#include <memory>
#include "GoldBagState.h"
namespace dae
{
	class GridComponent;
	class GameObject;
	class PointsComponent;
	class GoldBagComponent final: public Component
	{
	public:

		explicit GoldBagComponent(GameObject*pGameObject, GridComponent* grid, PointsComponent* points);
		virtual ~GoldBagComponent() override = default;

		virtual void HandleInput(glm::vec3 playerPos);
		virtual void Update(float deltaTime) override;
		void SetState(GoldBagState* newState);
	private:
		std::unique_ptr<GoldBagState> m_state;
		GridComponent* m_grid{ nullptr };   
		PointsComponent* m_points{ nullptr };
	};

}