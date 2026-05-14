#pragma once
#include "EnemyState.h"
#include <vector>
#include <functional>
#include "DataTypes.h"

namespace dae
{
	class EnemyWanderingState final : public EnemyState
	{
	public:
		explicit EnemyWanderingState(float moveSpeed);
		virtual~EnemyWanderingState() override = default;
		virtual EnemyState* OnEnter(EnemyComponent* enemyComponent, GridComponent* grid, glm::vec3)override;
		virtual EnemyState* Update(EnemyComponent* enemyComponent, float deltaTime)override; 
		virtual EnemyState* OnExit(EnemyComponent* enemyComponent)override;

		EnemyWanderingState(const EnemyWanderingState& other) = delete;
		EnemyWanderingState( EnemyWanderingState&& other) = delete;
		EnemyWanderingState& operator=(const EnemyWanderingState& other) = delete;
		EnemyWanderingState& operator=( EnemyWanderingState&& other) = delete;


	private:
		float m_moveSpeed{};
		glm::vec3 m_targetPos{};
		glm::vec3 m_previousPos{};
		bool m_isTargettingTile{ false };
		bool m_hasPreviousPos{ false };
		GridComponent* m_grid{ nullptr };

		std::function<bool(TileType)> m_isAllowed = [](TileType t)
			{
				return t == TileType::Tunnel;
			};
	};

}