#include "EnemyChasingState.h"
#include "GridComponent.h"
#include "EnemyComponent.h"
#include <MovingState.h>
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
	m_playerPos = playerPos;
	m_maxCols = m_grid->GetGrid().GetCols();
	m_shortestPath = GetShortestPathToPlayer(enemyComponent);
	return nullptr;
}

dae::EnemyState* dae::EnemyChasingState::Update(EnemyComponent* enemyComponent, float deltaTime)
{
	if (m_shortestPathIdx >= m_shortestPath.size()) return new EnemyChasingState(100.f);

		constexpr float snapDistance{ 2.f };
		const glm::vec3 targetPos{ m_shortestPath[m_shortestPathIdx]};

		const glm::vec3 enemyPos{ enemyComponent->GetOwner()->GetLocalPosition() };
		const glm::vec3 direction{ targetPos - enemyPos };
		const float distance{ static_cast<float>(glm::length(direction)) };

		if (distance <= snapDistance)
		{
			enemyComponent->GetOwner()->SetLocalPosition(targetPos);
			++m_shortestPathIdx;
			return nullptr;
		}
		enemyComponent->GetOwner()->SetLocalPosition(enemyPos + (glm::normalize(direction)) * m_speed * deltaTime);
	
	return nullptr;
}

dae::EnemyState* dae::EnemyChasingState::OnExit(EnemyComponent*)
{
	m_playerPos = {};
	m_shortestPath.clear();
	m_shortestPathIdx = {};
	return nullptr;
}

std::vector<glm::vec3> dae::EnemyChasingState::GetShortestPathToPlayer(EnemyComponent* enemyComponent)
{
	const GridPos start{ m_grid->WorldToCol(enemyComponent->GetOwner()->GetLocalPosition().x)
						,m_grid->WorldToRow(enemyComponent->GetOwner()->GetLocalPosition().y) };

	const GridPos goal{ m_grid->WorldToCol(m_playerPos.x)
						,m_grid->WorldToRow(m_playerPos.y) };

	std::queue<GridPos> unVisitedTiles;
	std::unordered_map<int, int> cameFromTiles;

	const int maxCols{ m_grid->GetGrid().GetCols() };
	const int startIndex{ start.row * maxCols + start.col};
	cameFromTiles[startIndex] = -1;
	unVisitedTiles.push(start);

	//BFS
	while (!unVisitedTiles.empty())
	{
		const GridPos current = unVisitedTiles.front();
		unVisitedTiles.pop();

		if (current == goal) break;

		//check all neighbours
		constexpr std::pair<int, int> directions[] = { {1,0},{-1,0},{0,1},{0,-1} };

		for (auto [col, row] : directions)
		{
			const int nextCol{ current.col + col };
			const int nextRow{ current.row + row };
			if (m_grid->GetGrid().GetTile(nextCol, nextRow) == TileType::Tunnel)
			{
				const int neighbourIndex{ nextRow * maxCols + nextCol };
				const int currentIndex{ current.row * maxCols + current.col };

				if (!cameFromTiles.contains(neighbourIndex))
				{
					cameFromTiles[neighbourIndex] = currentIndex;
					unVisitedTiles.push(GridPos{ nextCol, nextRow });
				}
			}
		}
	}
		//reconstruct path
		std::vector<GridPos> reversePath;
		int goalIdx = goal.row * maxCols + goal.col;
		int currentIdx = goalIdx;

		while (currentIdx != startIndex)
		{
			if (!cameFromTiles.contains(currentIdx)) return {};
			reversePath.push_back(indexToGridPos(currentIdx));
			currentIdx = cameFromTiles[currentIdx];
		}
		std::reverse(reversePath.begin(), reversePath.end());

		//convert to glm::vec3
		std::vector<glm::vec3> result;
		for (auto& gridpos : reversePath)
		{
			result.push_back({
				m_grid->ColToWorld(gridpos.col)
				,m_grid->RowToWorld(gridpos.row)
				,0.f
				});
		}

		return result;

}
dae::GridPos dae::EnemyChasingState::indexToGridPos(int index)
{
	return GridPos{
		index% m_maxCols
		, index/ m_maxCols	};
}