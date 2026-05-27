#include "EnemyWanderingState.h"
#include "Grid/GridComponent.h"
#include "EnemyComponent.h"
#include "EnemyHelpers.h"
#include <Windows.h>
#include <algorithm>
dae::EnemyWanderingState::EnemyWanderingState(float moveSpeed)
	:m_moveSpeed(moveSpeed)
{
}

dae::EnemyState* dae::EnemyWanderingState::OnEnter(EnemyComponent* enemyComponent, GridComponent* grid, glm::vec3)
{
	if (m_isTargettingTile) return nullptr;
	if (m_grid == nullptr)
	{
		m_grid = grid;
	}

	const glm::vec3 enemyPos{ enemyComponent->GetOwner()->GetLocalPosition()};

	m_isTargettingTile = PathFinding::ChooseNewTargetTile(grid, enemyPos, m_isAllowed, m_targetPos
		, m_previousPos, m_hasPreviousPos);

	return nullptr;
}

dae::EnemyState* dae::EnemyWanderingState::Update(EnemyComponent* enemyComponent, float deltaTime)
{
	if (!m_isTargettingTile) return nullptr;
	constexpr float snapDistance{ 2.f };
	
	if (EnemyMovement::MoveTowardsTile(enemyComponent,m_targetPos, m_moveSpeed,deltaTime,snapDistance))
	{

		const glm::vec3 enemyPos{ enemyComponent->GetOwner()->GetLocalPosition() };

		m_isTargettingTile = PathFinding::ChooseNewTargetTile(m_grid, enemyPos, m_isAllowed, m_targetPos
			, m_previousPos, m_hasPreviousPos);
	}
	return nullptr;
}

dae::EnemyState* dae::EnemyWanderingState::OnExit(EnemyComponent* )
{
	m_grid = nullptr;
	m_isTargettingTile = false;
	return nullptr;
}


