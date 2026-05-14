#include "EnemyDiggingState.h"
#include "EnemyHelpers.h"
#include "EnemyChasingState.h"

dae::EnemyDiggingState::EnemyDiggingState(float moveSpeed, float chasingRadius)
    :m_speed(moveSpeed)
    ,m_chasingRadius(chasingRadius)
{
}

dae::EnemyState* dae::EnemyDiggingState::OnEnter(EnemyComponent* enemyComponent, GridComponent* grid, glm::vec3 playerPos)
{
    m_grid = grid;
    m_playerPos = playerPos;

    const glm::vec3 enemyPos{ enemyComponent->GetOwner()->GetLocalPosition() };
    m_isTargettingTile = PathFinding::ChooseNewTargetTile(grid, enemyPos, m_isAllowed
        , m_targetPos, m_previousPos, m_hasPreviousPos);

    return nullptr;
}

dae::EnemyState* dae::EnemyDiggingState::Update(EnemyComponent* enemyComponent, float deltaTime)
{
    if (playerInRange(enemyComponent)) return new EnemyChasingState(m_speed);
    if(!m_isTargettingTile) return nullptr;

    if (EnemyMovement::MoveTowardsTile(enemyComponent, m_targetPos, m_speed, deltaTime))
    {
        const glm::vec3 enemyPos{ enemyComponent->GetOwner()->GetLocalPosition() };

        TryDiggingTile(enemyPos);
        m_isTargettingTile = PathFinding::ChooseNewTargetTile(m_grid, enemyPos, m_isAllowed
            , m_targetPos, m_previousPos, m_hasPreviousPos);

    }
    return nullptr;
}

dae::EnemyState* dae::EnemyDiggingState::OnExit(EnemyComponent* )
{
    m_isTargettingTile = false;
    m_hasPreviousPos = false;
    return nullptr;
}

bool dae::EnemyDiggingState::playerInRange(EnemyComponent* enemyComponent)
{
    const glm::vec3 enemyPos{ enemyComponent->GetOwner()->GetLocalPosition() };

    return (glm::length(m_playerPos -enemyPos)<=m_chasingRadius);
}

void dae::EnemyDiggingState::TryDiggingTile(const glm::vec3& pos)
{
    const GridPos currentTile{ m_grid->WorldToCol(pos.x), m_grid->WorldToRow(pos.y) };
    m_grid->DiggedTile(currentTile.col, currentTile.row);
}
