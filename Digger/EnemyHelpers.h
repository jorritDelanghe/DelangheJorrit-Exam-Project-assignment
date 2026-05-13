#pragma once
#include <glm/glm.hpp>
#include "EnemyComponent.h"

namespace EnemyMovement
{
    bool MoveTowardsTile(dae::EnemyComponent* enemyComponent, const glm::vec3& targetPos,
        float speed, float deltaTime, float snapDistance = 2.f);
}

namespace PathFinding
{

}