#pragma once
#include <glm/glm.hpp>
namespace dae
{
	class GridComponent;
	class EnemyComponent;
	class EnemyState
	{
	public:
		virtual ~EnemyState() = default;
		virtual EnemyState* OnEnter(EnemyComponent* /*enemyComponent*/, GridComponent* /*grid*/, glm::vec3 /*playerPos*/) { return nullptr; }
		virtual EnemyState* Update(EnemyComponent* /*enemyComponent*/, float /*deltaTime*/) { return nullptr; }
		virtual EnemyState* OnExit(EnemyComponent* /*enemyComponent*/) { return nullptr; }
	};

}