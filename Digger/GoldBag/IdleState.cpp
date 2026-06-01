#include "IdleState.h"
#include "GoldBagComponent.h"
#include "Grid/GridComponent.h"
#include "MovingState.h"
#include "FallingState.h"

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
dae::GoldBagState* dae::IdleState::Update(GoldBagComponent* goldBagComponent, float /*deltaTime*/)
{
	GridComponent* grid = goldBagComponent->GetGrid();
	const glm::vec3 pos = goldBagComponent->GetOwner()->GetLocalPosition();

	const int col = grid->WorldToCol(pos.x);
	const int row = grid->WorldToRow(pos.y);

	const TileType tileBelow = grid->GetGrid().GetTileType(col, row + 1);

	//set falling state if no tile below the goldbag
	if (tileBelow == TileType::Tunnel)
	{
		constexpr float fallSpeed{ 100.f };
		return new FallingState(fallSpeed);
	}
	return nullptr;
}

