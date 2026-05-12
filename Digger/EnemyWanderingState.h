#pragma once
#include "EnemyState.h"
#include <vector>
namespace dae
{
	class EnemyWanderingState final : public EnemyState
	{
	public:
		EnemyWanderingState(float moveSpeed);
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
		bool m_isTargettingTile{ false };
		GridComponent* m_grid{ nullptr };

		std::vector<glm::vec3> GetNeighbouringTunnels(const glm::vec3& enemyPos);
		void ChooseNewTargetTile(EnemyComponent* enemyComponent);
	};

}