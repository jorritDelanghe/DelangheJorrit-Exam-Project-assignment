#include "EnemyComponent.h"
#include "EnemyWanderingState.h"
#include "GridComponent.h"

dae::EnemyComponent::EnemyComponent(GameObject* pGameObject, GridComponent* grid)
	:Component(pGameObject)
	,m_grid(grid)
	,m_state(std::make_unique<EnemyWanderingState>(100.f))
	, m_pendingEnter{true}
{
}

void dae::EnemyComponent::Update(float deltaTime)
{
	if (m_pendingEnter)
	{
		m_state->OnEnter(this, m_grid, GetOwner()->GetLocalPosition());
		m_pendingEnter = false;
	}

	EnemyState* newState{m_state->Update(this, deltaTime)};
	if (newState)
	{
		SetState(newState);
	}
}

void dae::EnemyComponent::SetState(EnemyState* newState)
{
	m_state->OnExit(this);
	m_state.reset(newState);
	m_state->OnEnter(this, m_grid, {});

}
