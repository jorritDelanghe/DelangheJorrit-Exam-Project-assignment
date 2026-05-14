#include "EnemyChasingState.h"
#include "GridComponent.h"
#include "EnemyComponent.h"
#include "EnemyHelpers.h"
dae::EnemyChasingState::EnemyChasingState(float moveSpeed)
	:m_speed(moveSpeed)
{
}

dae::EnemyState* dae::EnemyChasingState::OnEnter(EnemyComponent* enemyComponent, GridComponent* grid, glm::vec3 playerPos)
{
	if (m_grid == nullptr)
	{
		m_grid = grid;
	}

	const glm::vec3 enemyPos{ enemyComponent->GetOwner()->GetLocalPosition() };
	m_shortestPath = PathFinding::BFS(grid, enemyPos, playerPos);
	return nullptr;
}

dae::EnemyState* dae::EnemyChasingState::Update(EnemyComponent* enemyComponent, float deltaTime)
{
	if (m_shortestPathIdx >= m_shortestPath.size()) return new EnemyChasingState(100.f);

		constexpr float snapDistance{ 2.f };
		const glm::vec3 targetPos{ m_shortestPath[m_shortestPathIdx]};

		if (EnemyMovement::MoveTowardsTile(enemyComponent, targetPos,m_speed, deltaTime,snapDistance))
		{
			++m_shortestPathIdx;
			return nullptr;
		}	
	return nullptr;
}

dae::EnemyState* dae::EnemyChasingState::OnExit(EnemyComponent*)
{
	m_shortestPath.clear();
	m_shortestPathIdx = {};
	return nullptr;
}


