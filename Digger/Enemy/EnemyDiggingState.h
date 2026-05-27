#pragma once
#include "EnemyState.h"
#include "DataTypes.h"

namespace dae
{
	class GridComponent;
	class EnemyDiggingState final : public EnemyState
	{
	public:
		explicit EnemyDiggingState(float moveSpeed, float chasingRadius = 150.0f);
		virtual~EnemyDiggingState() override = default;
		virtual EnemyState* OnEnter(EnemyComponent* enemyComponent, GridComponent* grid, glm::vec3 playerPos)override;
		virtual EnemyState* Update(EnemyComponent* enemyComponent, float deltaTime)override;
		virtual EnemyState* OnExit(EnemyComponent* enemyComponent)override;

		EnemyDiggingState(const EnemyDiggingState& other) = delete;
		EnemyDiggingState(EnemyDiggingState&& other) = delete;
		EnemyDiggingState& operator=(const EnemyDiggingState& other) = delete;
		EnemyDiggingState& operator=(EnemyDiggingState&& other) = delete;

	private:
		float m_speed{};
		float m_chasingRadius{};

		glm::vec3 m_targetPos{};
		glm::vec3 m_playerPos{};
		glm::vec3 m_previousPos{};
		bool m_isTargettingTile{ false };
		bool m_hasPreviousPos{ false };
		GridComponent* m_grid{ nullptr };

		std::function<bool(TileType)> m_isAllowed = [](TileType t)
			{
				return t == TileType::Tunnel || t == TileType::DirtWall;
			};

		bool playerInRange(EnemyComponent* enemyComponent);
		void TryDiggingTile(const glm::vec3& pos);

	};

}