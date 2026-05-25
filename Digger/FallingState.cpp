#include "FallingState.h"
#include "GoldBagComponent.h"
#include "GridComponent.h"
#include "IdleState.h"
dae::FallingState::FallingState(float fallSpeed)
	:m_fallSpeed(fallSpeed)
{
}

dae::GoldBagState* dae::FallingState::Update(GoldBagComponent* goldBagComponent, float deltaTime)
{
    const glm::vec3 currentPos = goldBagComponent->GetOwner()->GetLocalPosition();

    const float fallStep = m_fallSpeed * deltaTime;
    m_fallDistance += fallStep;
    goldBagComponent->GetOwner()->SetLocalPosition({ currentPos.x, currentPos.y + fallStep, currentPos.z });

    GridComponent* grid = goldBagComponent->GetGrid(); 

    const glm::vec3 newPos = goldBagComponent->GetOwner()->GetLocalPosition();
    const int currentRow = grid->WorldToRow(newPos.y);
    const int currentCol = grid->WorldToCol(newPos.x);

    const TileType tileBelow = grid->GetGrid().GetTileType(currentCol, currentRow + 1);

    if (tileBelow != TileType::Tunnel)
    {
      
        goldBagComponent->GetOwner()->SetLocalPosition({
            grid->ColToWorld(currentCol),
            grid->RowToWorld(currentRow),
            0.f
            });
        return new IdleState();
    }

    return nullptr;
}
