#include "MovingState.h"
#include "GridComponent.h"
#include "GameObject.h"
#include "GoldBagComponent.h"
#include "IdleState.h"


dae::MovingState::MovingState(float moveSpeed)
	: m_moveSpeed(moveSpeed)
{

}
dae::GoldBagState* dae::MovingState::HandleInputs(GoldBagComponent* goldBagComponent, GridComponent* grid, glm::vec3 playerPos)
{

	const glm::vec2 GoldBagPos{ 
		goldBagComponent->GetOwner()->GetLocalPosition().x
		,goldBagComponent->GetOwner()->GetLocalPosition().y };

	const GridPos BagOnGrid{ 
		grid->WorldToCol(GoldBagPos.x)
		, grid->WorldToRow(GoldBagPos.y) };

	const float directionX{ GoldBagPos.x - playerPos.x };
	const int colOffset{ (directionX > 0) ? 1 : -1 };

	const GridPos targetTile{ 
		BagOnGrid.col + colOffset, 
		BagOnGrid.row };

	//bounds
	if (targetTile.col<0
		|| targetTile.col > grid->GetGrid().GetCols())
	{
		return new IdleState();
	}

	const TileType typeTargetTile{ grid->GetGrid().GetTile(targetTile.col,targetTile.row) };

	if (typeTargetTile == TileType::Tunnel)
	{
		m_newPosition = {
			grid->ColToWorld(targetTile.col)
			, grid->RowToWorld(targetTile.row),0.f};
		m_hasMoved = true;

	}
	else
	{
		return new IdleState();
	}
	return nullptr;
}
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