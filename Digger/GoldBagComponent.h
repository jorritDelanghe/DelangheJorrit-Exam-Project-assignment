#pragma once
#include "Component.h"

#include <memory>
#include "GoldBagState.h"
namespace dae
{
	class GridComponent;
	class GameObject;
	class GoldBagComponent final: public Component
	{
	public:

		explicit GoldBagComponent(GameObject*pGameObject);
		virtual ~GoldBagComponent() override = default;

		virtual void HandleInput( GridComponent* grid, glm::vec3 playerPos);
		virtual void Update(float deltaTime) override;
	private:
		std::unique_ptr<GoldBagState> m_state;
	};

}