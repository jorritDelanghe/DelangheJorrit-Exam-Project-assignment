#pragma once

#include "EnemyState.h"
#include "DataTypes.h"
namespace dae
{
	class GridComponent;
	class EnemyChasingState final : public EnemyState
	{
	public:
		explicit EnemyChasingState(float moveSpeed);
		virtual~EnemyChasingState() override = default;
		virtual EnemyState* OnEnter(EnemyComponent* enemyComponent, GridComponent* grid, glm::vec3 playerPos)override;
		virtual EnemyState* Update(EnemyComponent* enemyComponent, float deltaTime)override;
		virtual EnemyState* OnExit(EnemyComponent* enemyComponent)override;

		EnemyChasingState(const EnemyChasingState& other) = delete;
		EnemyChasingState(EnemyChasingState&& other) = delete;
		EnemyChasingState& operator=(const EnemyChasingState& other) = delete;
		EnemyChasingState& operator=(EnemyChasingState&& other) = delete;
	
	private:
		float m_speed{};
		GridComponent* m_grid{};

		std::vector<glm::vec3> m_shortestPath{};
		int m_shortestPathIdx{};
	};

}