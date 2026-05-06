//#include "FallingState.h"
//#include "GoldBagComponent.h"
//#include "GridComponent.h"
//#include "IdleState.h"
//dae::FallingState::FallingState(float fallSpeed)
//	:m_fallSpeed(fallSpeed)
//{
//}
//
//dae::GoldBagState* dae::FallingState::HandleInputs(GoldBagComponent* goldBagComponent, GridComponent* grid, glm::vec3 playerPos)
//{
//	const glm::vec2 GoldBagPos{
//		goldBagComponent->GetOwner()->GetLocalPosition().x
//		,goldBagComponent->GetOwner()->GetLocalPosition().y };
//
//	if (!((std::abs(playerPos.y - GoldBagPos.y)) <= grid->GetGrid().GetTileSize())) return new IdleState;
//
//	const GridPos BagOnGrid{
//		grid->WorldToCol(GoldBagPos.x)
//		, grid->WorldToRow(GoldBagPos.y) };
//}
//
//dae::GoldBagState* dae::FallingState::Update(GoldBagComponent* goldBagComponent, float deltaTime)
//{
//	return nullptr;
//}
