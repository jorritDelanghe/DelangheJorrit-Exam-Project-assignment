#include "IdleState.h"
#include "GoldBagComponent.h"
#include "GridComponent.h"
#include "MovingState.h"

dae::GoldBagState* dae::IdleState::HandleInputs(GoldBagComponent* goldBagComponent, GridComponent* grid, glm::vec3 playerPos)
{
	constexpr float speed{ 100.f };
	const glm::vec2 goldBagPos{
		goldBagComponent->GetOwner()->GetLocalPosition().x
		,goldBagComponent->GetOwner()->GetLocalPosition().y
	};

	const float tileSize{ grid->GetGrid().GetTileSize() };

	const bool isOnSameRow{ std::abs(playerPos.y - goldBagPos.y) < tileSize };
	const bool isNextToGoldBag{ std::abs(playerPos.x - goldBagPos.x) < tileSize };

	if (isOnSameRow && isNextToGoldBag)
	{
		return new MovingState(speed);
	}
	return nullptr;
}

