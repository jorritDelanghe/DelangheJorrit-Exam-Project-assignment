#include "MovingState.h"
#include "Grid/GridComponent.h"
#include "GameObject.h"
#include "GoldBagComponent.h"
#include "IdleState.h"
#include "FallingState.h"
#include "Collision/RectColliderComponent.h"

dae::MovingState::MovingState(float moveSpeed)
	: m_moveSpeed(moveSpeed)
{

}
dae::GoldBagState* dae::MovingState::OnEnter(GoldBagComponent* goldBagComponent)
{
	//needed for chaining pushing goldbags
	goldBagComponent->GetOwner()->GetComponent<RectColliderComponent>()->SetTag(CollisionTag::MovingGoldBag);
	return nullptr;
}
dae::GoldBagState* dae::MovingState::HandleInputs(GoldBagComponent* goldBagComponent, GridComponent* grid, glm::vec3 playerPos)
{
	const glm::vec2 GoldBagPos{ 
		goldBagComponent->GetOwner()->GetLocalPosition().x
		,goldBagComponent->GetOwner()->GetLocalPosition().y };

	if (!((std::abs(playerPos.y - GoldBagPos.y)) <= grid->GetGrid().GetTileSize())) return new IdleState;

	const GridPos BagOnGrid{ 
		grid->WorldToCol(GoldBagPos.x)
		, grid->WorldToRow(GoldBagPos.y) };

	const float directionX{ playerPos.x- GoldBagPos.x  };
	const int colOffset{ (directionX > 0) ? -1 : 1 };

	const GridPos targetTile{ 
		BagOnGrid.col + colOffset, 
		BagOnGrid.row };


	//bounds
	if (targetTile.col<0
		|| targetTile.col >= grid->GetGrid().GetCols())
	{
		return new IdleState();
	}

	const TileType typeTargetTile{ grid->GetGrid().GetTileType(targetTile.col,targetTile.row) };
	const TileType typeTargetFallTile{ grid->GetGrid().GetTileType(targetTile.col,targetTile.row+1) };

	if (typeTargetTile == TileType::Tunnel || typeTargetTile == TileType::DirtWall)
	{
		m_newPosition = {
			grid->ColToWorld(targetTile.col)
			, grid->RowToWorld(targetTile.row),0.f};
		m_hasMoved = true;

	}
	else if (typeTargetFallTile == TileType::Tunnel)
	{
		constexpr float fallSpeed{ 100.f };
		return new FallingState(fallSpeed);
	}
	else
	{
		return new IdleState();
	}
	return nullptr;
}
//void dae::MovingState::Notify(GameEvent event, GameObject* )
//{
//	if (event == GameEvent::CollisionGoldBag)
//	{
//
//	}
//}
dae::GoldBagState* dae::MovingState::Update(GoldBagComponent* goldBagComponent, float /*deltaTime*/)
{
	if (m_hasMoved)
	{
		goldBagComponent->GetOwner()->SetLocalPosition(m_newPosition);
		m_hasMoved = false;
		return new IdleState();
	}
	return nullptr;
}

dae::GoldBagState* dae::MovingState::OnExit(GoldBagComponent* goldBagComponent)
{
	goldBagComponent->GetOwner()->GetComponent<RectColliderComponent>()->SetTag(CollisionTag::GoldBag);
	return nullptr;
}
