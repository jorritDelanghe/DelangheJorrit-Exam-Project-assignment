#include "MoveDiggerCommand.h"
#include "GameObject.h"
#include "GameTime.h"

MoveDiggerCommand::MoveDiggerCommand(dae::GameObject* gameObject, float speed, const glm::vec3& direction, dae::GridComponent* grid)
	:GameObjectCommand(gameObject)
	, m_direction{ direction }
	, m_speed{ speed }
	, m_grid{ grid }
{

}
void MoveDiggerCommand::Execute()
{
	auto* gameObject{ GetGameObject() };
	glm::vec3 currentPos{ gameObject->GetLocalPosition() };

	if (m_grid)
	{
		const int col{ m_grid->WorldToCol(currentPos.x) };
		const int row{ m_grid->WorldToRow(currentPos.y) };

		m_grid->DiggedTile(col, row); //set tile digged
	}
	gameObject->SetLocalPosition(currentPos + (m_speed * m_direction * dae::GameTime::deltaTime));
}