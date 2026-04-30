#include "GoldBagComponent.h"
#include "GameObject.h"
dae::GoldBagComponent::GoldBagComponent(GameObject* pGameObject)
	:Component(pGameObject)
{

}
void dae::GoldBagComponent::HandleInput( GridComponent* grid, glm::vec3 playerPos)
{
	m_state.HandleInputs(this, grid, playerPos);
}
void dae::GoldBagComponent::Update()
{
	m_state.Update(this);
}