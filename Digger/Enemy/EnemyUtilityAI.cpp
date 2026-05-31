#include "Enemy/EnemyUtilityAI.h"
#include <algorithm>
#include "GameObject.h"
#include "Grid/GridComponent.h"
#include "GameObject.h"
#include "EnemyComponent.h"
#include "Scene/PointsComponent.h"


dae::EnemyUtilityAI::EnemyUtilityAI(GameObject* pOwner, EnemyComponent* enemy, GridComponent* grid,
	GameObject* player, PointsComponent* pPoints)
	: Component(pOwner)
	, m_pEnemy(enemy)
	, m_pGrid(grid)
	, m_pPlayer(player)
	, m_pPoints(pPoints)
{

}

void dae::EnemyUtilityAI::Update(float deltaTime)
{
	if (m_actions.empty()) return;

	const GameStats gameStats{ GetGameStats() };
	//update time alive
	m_timeAlive += deltaTime;

	//score actions
	float bestScore{};
	std::string bestName{};
	int bestIdx{};

	for (int i{};i < m_actions.size();++i)
	{
		const float score = m_actions[i].scorer(gameStats);

		if (score > bestScore)
		{
			bestScore = score;
			bestName = m_actions[i].nameAction;
			bestIdx = i;
		}
	}

	if (bestName == m_currentName) return;

	const float currentScore{ ScoreCurrent(gameStats) };
	if (bestScore < currentScore + m_oscillationThreshold) return;

	m_currentName = bestName;
	m_pEnemy->SetState(m_actions[bestIdx].createState());
}

void dae::EnemyUtilityAI::RegisterNewAction(const std::string& nameAction, std::function<float(const GameStats&)> scorer, std::function<EnemyState* ()> createState)
{	
	m_actions.push_back(UtilityAiAction{ nameAction , std::move(scorer),std::move(createState) });
}

void dae::EnemyUtilityAI::RegisterNewAction(const UtilityAiAction& action)
{
	RegisterNewAction(action.nameAction,action.scorer, action.createState);
}

dae::EnemyUtilityAI::GameStats dae::EnemyUtilityAI::GetGameStats() const
{
	GameStats gameStats{};

	gameStats.collectedPoints = m_pPoints->GetScore();
	gameStats.timePlayerAlive = m_timeAlive;
	gameStats.enemyPos = m_pEnemy->GetOwner()->GetLocalPosition();
	gameStats.playerPos = m_pPlayer->GetLocalPosition();
	gameStats.distancePlayer = glm::length(gameStats.playerPos - gameStats.enemyPos);

	const int col = m_pGrid->WorldToCol(gameStats.enemyPos.x);
	const int row = m_pGrid->WorldToRow(gameStats.enemyPos.y);
	gameStats.isOnTunnel = (m_pGrid->GetGrid().GetTileType(col, row) == TileType::Tunnel);

	return gameStats;
}

float dae::EnemyUtilityAI::ScoreCurrent(const GameStats& gameStats) const
{
	for (auto currentAction : m_actions)
	{
		if (currentAction.nameAction == m_currentName)
		{
			return currentAction.scorer(gameStats);
		}
	}
	return 0.0f;
}

//curve helpers
float dae::EnemyUtilityAI::GetLinearCurve(float value, float maxValue)
{
	return std::clamp(value/maxValue,0.f,1.f);
}

float dae::EnemyUtilityAI::GetScoringQuadraticCurve(float value, float maxValue)
{
	const float linResult{ GetLinearCurve(value, maxValue) };
	return linResult* linResult;
}

float dae::EnemyUtilityAI::GetPercentage(int currentValue, int maxValue) 
{
	return static_cast<float>(currentValue)/maxValue;
}
