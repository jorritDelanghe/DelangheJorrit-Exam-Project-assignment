#include "EnemyDiggingState.h"
#include "EnemyHelpers.h"
#include "EnemyChasingState.h"
#include "RenderComponent.h"
#include "Collision/RectColliderComponent.h"

dae::EnemyDiggingState::EnemyDiggingState(
    float moveSpeed,
    const std::string& fileNameNormalEnemy, const std::string& fileNameDiggingEnemy, 
    float chasingRadius)

    : m_speed(moveSpeed)
    , m_fileNameNormalEnemy(fileNameNormalEnemy)
    , m_fileNameDiggingEnemy(fileNameDiggingEnemy)
    , m_chasingRadius(chasingRadius)
{
}

dae::EnemyState* dae::EnemyDiggingState::OnEnter(EnemyComponent* enemyComponent, GridComponent* grid, glm::vec3 playerPos)
{
    m_grid = grid;
    m_playerPos = playerPos;

	//set target tile for enemy
    const glm::vec3 enemyPos{ enemyComponent->GetOwner()->GetLocalPosition() };
    m_isTargettingTile = PathFinding::ChooseNewTargetTile(grid, enemyPos, m_isAllowed
        , m_targetPos, m_previousPos, m_hasPreviousPos);

	//change sprite to digging sprite
    RenderComponent* renderComponent{enemyComponent->GetOwner()->GetComponent<RenderComponent>()};
    renderComponent->SetTexture(m_fileNameDiggingEnemy);

    return nullptr;
}

dae::EnemyState* dae::EnemyDiggingState::Update(EnemyComponent* enemyComponent, float deltaTime)
{
    //UtilityAI already checks in player is close go to chasing
    if(!m_isTargettingTile) return nullptr;

	//needs to check every update otherwise problem overlap
	auto* rectColliderComponent{ enemyComponent->GetOwner()->GetComponent<RectColliderComponent>() };
	const auto enemyBoundingBox{ rectColliderComponent->GetBoundingBoxInWorld() };
	m_grid->DiggedTile(enemyBoundingBox);

    //move towards true if arrive, set new target after arrive
    if (EnemyMovement::MoveTowardsTile(enemyComponent, m_targetPos, m_speed, deltaTime))
    {
        const glm::vec3 enemyPos{ enemyComponent->GetOwner()->GetLocalPosition() };
        m_isTargettingTile = PathFinding::ChooseNewTargetTile(m_grid, enemyPos, m_isAllowed
            , m_targetPos, m_previousPos, m_hasPreviousPos);
    }
    return nullptr;
}

dae::EnemyState* dae::EnemyDiggingState::OnExit(EnemyComponent* enemyComponent)
{
	//reset all digging related variables
    m_isTargettingTile = false;
    m_hasPreviousPos = false;

    //change sprite to normal sprite
    RenderComponent* renderComponent{ enemyComponent->GetOwner()->GetComponent<RenderComponent>() };
    renderComponent->SetTexture(m_fileNameNormalEnemy);

    return nullptr;
}
