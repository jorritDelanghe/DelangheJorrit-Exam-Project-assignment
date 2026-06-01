#include "FallingState.h"
#include "GoldBagComponent.h"
#include "Grid/GridComponent.h"
#include "IdleState.h"
#include "BrokenState.h"
#include "Collision/RectColliderComponent.h"
dae::FallingState::FallingState(float fallSpeed)
	:m_fallSpeed(fallSpeed)
{
}


dae::GoldBagState* dae::FallingState::OnEnter(GoldBagComponent* goldBagComponent)
{
   auto*rectCollComponent = goldBagComponent->GetOwner()->GetComponent<RectColliderComponent>();
   rectCollComponent->SetTag(CollisionTag::FallingGoldBag); //no need to reset, because desstroyed on ground
   return nullptr;
}

dae::GoldBagState* dae::FallingState::Update(GoldBagComponent* goldBagComponent, float deltaTime)
{
    const glm::vec3 currentPos = goldBagComponent->GetOwner()->GetLocalPosition();

    //falling
    const float fallStep = m_fallSpeed * deltaTime;
    m_fallDistance += fallStep;
    goldBagComponent->GetOwner()->SetLocalPosition({ currentPos.x, currentPos.y + fallStep, currentPos.z });

    GridComponent* grid = goldBagComponent->GetGrid(); 

    const glm::vec3 newPos = goldBagComponent->GetOwner()->GetLocalPosition();
    const int currentRow = grid->WorldToRow(newPos.y);
    const int currentCol = grid->WorldToCol(newPos.x);

    const TileType tileBelow = grid->GetGrid().GetTileType(currentCol, currentRow + 1);

    //STOP falling
    if (tileBelow != TileType::Tunnel) 
    {
        //fix pos
        goldBagComponent->GetOwner()->SetLocalPosition({
            grid->ColToWorld(currentCol),
            grid->RowToWorld(currentRow),
            0.f
            });

        //break goldbag
        constexpr float minBreakDistance{ 32.f }; // one tile
        if (m_fallDistance > minBreakDistance)
        {
            return new BrokenState();
        }

        return new IdleState();
    }

    return nullptr;
}
