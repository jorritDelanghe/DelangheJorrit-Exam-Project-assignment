#include "DataTypes.h"
#include "EnemyHelpers.h"
#include "GameObject.h"
#include <queue>

bool EnemyMovement::MoveTowardsTile(dae::EnemyComponent* enemyComponent, const glm::vec3& targetPos,
	float speed, float deltaTime, float snapDistance)
{

	const glm::vec3 enemyPos{ enemyComponent->GetOwner()->GetLocalPosition() };
	const glm::vec3 direction{ targetPos - enemyPos };
	const float distance{ static_cast<float>(glm::length(direction)) };

	if (distance <= snapDistance)
	{
		enemyComponent->GetOwner()->SetLocalPosition(targetPos);
		return true;
	}
	enemyComponent->GetOwner()->SetLocalPosition(enemyPos + (glm::normalize(direction)) * speed * deltaTime);

	return false;
}
std::vector<glm::vec3> PathFinding::BFS(dae::GridComponent* grid, const glm::vec3& startPos, const glm::vec3& goalPos)
{
	const dae::GridPos start{ grid->WorldToCol(startPos.x)
						,grid->WorldToRow(startPos.y) };

	const dae::GridPos goal{ grid->WorldToCol(goalPos.x)
						,grid->WorldToRow(goalPos.y) };

	std::queue<dae::GridPos> unVisitedTiles;
	std::unordered_map<int, int> cameFromTiles;

	const int maxCols{ grid->GetGrid().GetCols() };
	const int startIndex{ start.row * maxCols + start.col };
	cameFromTiles[startIndex] = -1;
	unVisitedTiles.push(start);

	//BFS
	while (!unVisitedTiles.empty())
	{
		const dae::GridPos current = unVisitedTiles.front();
		unVisitedTiles.pop();

		if (current == goal) break;

		//check all neighbours
		constexpr std::pair<int, int> directions[] = { {1,0},{-1,0},{0,1},{0,-1} };

		for (auto [col, row] : directions)
		{
			const int nextCol{ current.col + col };
			const int nextRow{ current.row + row };
			if (grid->GetGrid().GetTile(nextCol, nextRow) == dae::TileType::Tunnel)
			{
				const int neighbourIndex{ nextRow * maxCols + nextCol };
				const int currentIndex{ current.row * maxCols + current.col };

				if (!cameFromTiles.contains(neighbourIndex))
				{
					cameFromTiles[neighbourIndex] = currentIndex;
					unVisitedTiles.push(dae::GridPos{ nextCol, nextRow });
				}
			}
		}
	}
	//reconstruct path
	std::vector<dae::GridPos> reversePath;
	int goalIdx = goal.row * maxCols + goal.col;
	int currentIdx = goalIdx;

	while (currentIdx != startIndex)
	{
		if (!cameFromTiles.contains(currentIdx)) return {};
		reversePath.push_back(dae::indexToGridPos(currentIdx, maxCols));
		currentIdx = cameFromTiles[currentIdx];
	}
	std::reverse(reversePath.begin(), reversePath.end());

	//convert to glm::vec3
	std::vector<glm::vec3> result;
	for (auto& gridpos : reversePath)
	{
		result.push_back({
			grid->ColToWorld(gridpos.col)
			,grid->RowToWorld(gridpos.row)
			,0.f
			});
	}

	return result;

}
std::vector<glm::vec3> PathFinding::GetNeighbouringTunnels(dae::GridComponent* grid, const glm::vec3& currentPos
	, std::function<bool(dae::TileType)>isAllowed)
{
	const int currentCol{ grid->WorldToCol(currentPos.x) };
	const int currentRow{ grid->WorldToRow(currentPos.y) };
	constexpr std::pair<int, int> direction[] = { {1,0},{-1,0},{0,1},{0,-1} };
	constexpr int maxTunnelOptions{ 4 };

	std::vector<glm::vec3> neighbouringTunnelPos{};
	neighbouringTunnelPos.reserve(maxTunnelOptions);

	for (auto [col, row] : direction)
	{
		const int neighbouringCol{ currentCol + col };
		const int neighbouringRow{ currentRow + row };


		const dae::TileType neighbourTile{
			grid->GetGrid().GetTile(
				neighbouringCol
				,neighbouringRow) };

		if (isAllowed(neighbourTile) )
		{
			neighbouringTunnelPos.push_back(glm::vec3{
				 grid->ColToWorld(neighbouringCol)
				 , grid->RowToWorld(neighbouringRow)
				,0.f
				});
		}

	}
	return neighbouringTunnelPos;
}
bool PathFinding::ChooseNewTargetTile(dae::GridComponent* grid, const glm::vec3& currentPos,std::function<bool(dae::TileType)>isAlllowed
	,glm::vec3& outTargetPos
	,glm::vec3& outPreviousPos
	,bool& outHasPreviousPos)
{
	auto tunnelPositions{ GetNeighbouringTunnels(grid,currentPos ,isAlllowed) };

	if (tunnelPositions.empty())
	{
		return false;
	}
	if (outHasPreviousPos && tunnelPositions.size() >= 2) //otherwise no options left
	{
		tunnelPositions.erase(std::remove(tunnelPositions.begin()
			, tunnelPositions.end()
			, outPreviousPos)
			, tunnelPositions.end());
	}
	outPreviousPos = currentPos;
	outHasPreviousPos = true;

	const int randNumber{ static_cast<int>(rand() % (tunnelPositions.size())) };
	outTargetPos = tunnelPositions[randNumber];
	return true;
}
