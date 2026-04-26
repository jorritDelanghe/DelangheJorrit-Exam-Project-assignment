#include "GameObjectCommand.h"
#include "HealthComponent.h"
#include "PointsComponent.h"
#include "GameTime.h"
#include "GridComponent.h"
namespace dae
{
	GameObjectCommand::GameObjectCommand(GameObject* gameObject)
		:m_pGameObject{ gameObject }
	{
	}
	GameObject* GameObjectCommand::GetGameObject() const
	{
		return m_pGameObject;
	}
	MoveGameObjectCommand::MoveGameObjectCommand(GameObject* gameObject, float speed, const glm::vec3& direction, GridComponent* grid)
		:GameObjectCommand(gameObject)
		,m_direction{direction}
		,m_speed{speed}
		,m_grid{grid}
	{

	}
	void MoveGameObjectCommand::Execute()
	{
		auto* gameObject {GetGameObject()};
		glm::vec3 currentPos{ gameObject->GetLocalPosition() };

		if (m_grid)
		{
			const int col{ m_grid->WorldToCol(currentPos.x) };
			const int row{ m_grid->WorldToRow(currentPos.y) };

			m_grid->DiggedTile(col, row); //set tile digged
		}
		gameObject->SetLocalPosition(currentPos + (m_speed * m_direction* dae::GameTime::deltaTime));
	}
	DieCommand::DieCommand(GameObject* gameObject)
		:GameObjectCommand(gameObject)
	{
	}
	void DieCommand::Execute()
	{
		GetGameObject()->GetComponent<HealthComponent>()->Die();
	}
	GainPointsCommand::GainPointsCommand(GameObject* gameObject, int points)
		: GameObjectCommand(gameObject)
		,m_points(points)
	{
	}
	void GainPointsCommand::Execute()
	{
		GetGameObject()->GetComponent<PointsComponent>()->AddScore(m_points);
	}
}