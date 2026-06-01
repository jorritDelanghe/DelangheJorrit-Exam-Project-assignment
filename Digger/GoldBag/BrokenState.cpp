#include "BrokenState.h"
#include "GoldBagComponent.h"
#include "GameObject.h"

dae::GoldBagState* dae::BrokenState::OnEnter(GoldBagComponent* goldBagComponent)
{
	goldBagComponent->SpawnGoldNugget();
	goldBagComponent->GetOwner()->MarkForDelete(); //destroy goldbag after spawning nugget
	return nullptr;
}
