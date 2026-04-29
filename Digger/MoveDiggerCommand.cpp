#include "MoveDiggerCommand.h"
#include "GameObject.h"
#include "GameTime.h"
#include "ServiceLocator.h"

MoveDiggerCommand::MoveDiggerCommand(dae::GameObject* gameObject, float speed, const glm::vec3& direction, dae::GridComponent* grid,dae::SoundID soundID, dae::SoundID gemSound)
	:GameObjectCommand(gameObject)
	, m_direction{ direction }
	, m_speed{ speed }
	, m_grid{ grid }
	, m_digSound{ soundID }
	, m_gemSound{ gemSound }
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

		switch (m_grid->DiggedTile(col, row))
		{
		case TileType::DirtWall:
			dae::ServiceLocator::GetSoundSystem().Play(m_digSound, 0.8f);
			break;

		case TileType::Emerald:
			dae::ServiceLocator::GetSoundSystem().Play(m_gemSound, 0.8f);
			break;
		}
		
	}
	gameObject->SetLocalPosition(currentPos + (m_speed * m_direction * dae::GameTime::deltaTime));
}