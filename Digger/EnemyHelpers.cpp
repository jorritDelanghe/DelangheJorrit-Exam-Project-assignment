#include "EnemyHelpers.h"
#include "GameObject.h"

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