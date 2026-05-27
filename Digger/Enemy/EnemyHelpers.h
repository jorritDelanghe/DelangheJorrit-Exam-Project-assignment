#pragma once
#include <glm/glm.hpp>
#include "EnemyComponent.h"
#include "Grid/GridComponent.h"
#include "DataTypes.h"
#include <vector>

namespace EnemyMovement
{
    bool MoveTowardsTile(dae::EnemyComponent* enemyComponent, const glm::vec3& targetPos,
        float speed, float deltaTime, float snapDistance = 2.f);
}

namespace PathFinding
{
    std::vector<glm::vec3> BFS(dae::GridComponent* grid, const glm::vec3& start, const glm::vec3& goal);

    std::vector<glm::vec3> GetNeighbouringTunnels(dae::GridComponent* grid
        ,const glm::vec3& currentPos
        ,std::function<bool(dae::TileType)>isAllowed);

    bool ChooseNewTargetTile(dae::GridComponent* grid, const glm::vec3& currentPos, std::function<bool(dae::TileType)>isAlllowed
        , glm::vec3& outTargetPos
        , glm::vec3& outPreviousPos
        , bool& outHasPreviousPos);

}