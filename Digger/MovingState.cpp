#include "MovingState.h"
#include "GridComponent.h"
#include "GameObject.h"
#include "GoldBagComponent.h"


dae::MovingState::MovingState(float moveSpeed)
	: m_moveSpeed(moveSpeed)
{

}
void dae::MovingState::HandleInputs(GoldBagComponent* goldBagComponent, GridComponent* grid, glm::vec3 playerPos)
{

	const glm::vec2 GoldBagPos{ goldBagComponent->GetOwner()->GetLocalPosition().x
		,goldBagComponent->GetOwner()->GetLocalPosition().y };
	const float tileSize{ grid->GetGrid().GetTileSize() };

	if (std::abs(GoldBagPos.x - playerPos.x) <= tileSize)
	{
		m_isDirty = true;
	}

		
	if (!m_isDirty)
	{

		const GridPos playerOnGrid{ grid->WorldToCol(playerPos.x), grid->WorldToRow(playerPos.y) };
		m_gridPosGoldBag = {
			grid->WorldToCol(GoldBagPos.x)
			,grid->WorldToRow(GoldBagPos.y) };
		m_isDirty = true;


		const glm::vec2 direction{ glm::normalize(GoldBagPos - glm::vec2(playerPos)) };
		const int colOffset{ (direction.x > 0) ? 1 : -1 };

		if ((m_gridPosGoldBag.col + 1) <= grid->GetGrid().GetCols() && m_gridPosGoldBag.col >= 0)
		{
			if (GridPos newGridPos{ m_gridPosGoldBag.col + colOffset, m_gridPosGoldBag.row };
				grid->GetGrid().GetTile(newGridPos.col, newGridPos.row) == TileType::Tunnel)
			{
				m_newPosition =
				{ grid->ColToWorld(newGridPos.col)
				, grid->RowToWorld(newGridPos.row),0.f };
			}

	}
}



}
void dae::MovingState::Update(GoldBagComponent* goldBagComponent , float deltaTime)
{
	if (m_isDirty)
	{
		goldBagComponent->GetOwner()->SetLocalPosition(m_newPosition);
		m_isDirty = false;
	}
}