#include "EnemyWanderingState.h"
#include "GridComponent.h"
#include "DataTypes.h"
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

	ChooseNewTargetTile(enemyComponent);
	 return nullptr;
}

dae::EnemyState* dae::EnemyWanderingState::Update(EnemyComponent* enemyComponent, float deltaTime)
{
	if (!m_isTargettingTile) return nullptr;
	constexpr float snapDistance{ 2.f };
	
	if (EnemyMovement::MoveTowardsTile(enemyComponent,m_targetPos, m_moveSpeed,deltaTime,snapDistance))
	{
		m_isTargettingTile = false;

		ChooseNewTargetTile(enemyComponent);
		return nullptr;
	}
	return nullptr;
}

dae::EnemyState* dae::EnemyWanderingState::OnExit(EnemyComponent* )
{
	m_grid = nullptr;
	m_isTargettingTile = false;
	return nullptr;
}

std::vector<glm::vec3> dae::EnemyWanderingState::GetNeighbouringTunnels(const glm::vec3& enemyPos)
{
	const int colEnemy{ m_grid->WorldToCol(enemyPos.x) };
	const int rowEnemy{ m_grid->WorldToRow(enemyPos.y) };
	constexpr std::pair<int, int> direction[] ={ {1,0},{-1,0},{0,1},{0,-1} };
	constexpr int maxTunnelOptions{ 4 };

	std::vector<glm::vec3> neighbouringTunnelPos{};
	neighbouringTunnelPos.reserve(maxTunnelOptions);

	for (auto [col, row] : direction)
	{
		const int neighbouringCol{ colEnemy + col };
		const int neighbouringRow{ rowEnemy + row };

		
		const TileType neighbourTile{
			m_grid->GetGrid().GetTile(
				neighbouringCol
				,neighbouringRow)};

		if (neighbourTile == TileType::Tunnel)
		{
			neighbouringTunnelPos.push_back(glm::vec3{
				 m_grid->ColToWorld(neighbouringCol)
				 , m_grid->RowToWorld(neighbouringRow)
				,0.f
				});
		}
		
	}
		return neighbouringTunnelPos;
}

void dae::EnemyWanderingState::ChooseNewTargetTile(EnemyComponent* enemyComponent)
{
	auto tunnelPositions{ GetNeighbouringTunnels(enemyComponent->GetOwner()->GetLocalPosition()) };

	if (tunnelPositions.empty())
	{
		m_isTargettingTile = false ;
		return;
	}
	if (m_hasPreviousPos&& tunnelPositions.size() >= 2) //otherwise no options left
	{
		tunnelPositions.erase(std::remove(tunnelPositions.begin()
			, tunnelPositions.end()
			,m_previousPos)
			, tunnelPositions.end());
	}
	m_previousPos = enemyComponent->GetOwner()->GetLocalPosition();
	m_hasPreviousPos = true;

	const int randNumber{ static_cast<int>(rand() % (tunnelPositions.size())) };
	m_targetPos = tunnelPositions[randNumber];
	m_isTargettingTile = true;
}


