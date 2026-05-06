#include "GoldBagComponent.h"
#include "GameObject.h"
#include "IdleState.h"
dae::GoldBagComponent::GoldBagComponent(GameObject* pGameObject,GridComponent* grid,PointsComponent* points)
	:Component(pGameObject)
	,m_state(std::make_unique<IdleState>())
	,m_grid(grid)
	,m_points(points)
{

}
void dae::GoldBagComponent::HandleInput(glm::vec3 playerPos)
{
	GoldBagState* newState{ m_state->HandleInputs(this, m_grid, playerPos) };

	if (newState)
	{
		SetState(newState);
	}
}
void dae::GoldBagComponent::SetState(GoldBagState* newState)
{
	m_state.reset(newState);
}
void dae::GoldBagComponent::Update(float deltaTime)
{
	GoldBagState* newState{ m_state->Update(this, deltaTime) };

	if (newState)
	{
		SetState(newState);
	}
}