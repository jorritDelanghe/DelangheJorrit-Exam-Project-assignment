#include "EnemyComponent.h"
#include "EnemyWanderingState.h"
#include "Grid/GridComponent.h"
#include "EnemyChasingState.h"
#include "EnemyDiggingState.h"

dae::EnemyComponent::EnemyComponent(GameObject* pGameObject, GridComponent* grid, GameObject*player)
	:Component(pGameObject)
	,m_grid(grid)
	,m_state(std::make_unique<EnemyWanderingState>(100.f))
	, m_pendingEnter{true}
	,m_player(player)
{
}

void dae::EnemyComponent::Update(float deltaTime)
{
	if (m_pendingEnter)
	{
		m_state->OnEnter(this, m_grid, m_player->GetLocalPosition());
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
	m_state->OnEnter(this, m_grid, m_player->GetLocalPosition());

}
