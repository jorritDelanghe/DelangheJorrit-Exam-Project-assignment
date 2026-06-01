#include "MoveDiggerCommand.h"
#include "GameObject.h"
#include "GameTime.h"
#include "ServiceLocator.h"
#include "Collision/RectColliderComponent.h"

dae::MoveDiggerCommand::MoveDiggerCommand(dae::GameObject* gameObject, float speed, const glm::vec3& direction
	, dae::GridComponent* grid,dae::SoundID soundID, dae::SoundID gemSound, PointsComponent* pPoints)
	:GameObjectCommand(gameObject)
	, m_direction{ direction }
	, m_speed{ speed }
	, m_grid{ grid }
	, m_digSound{ soundID }
	, m_gemSound{ gemSound }
	,m_pPoints{pPoints}
{

}
void dae::MoveDiggerCommand::Execute()
{
	auto* gameObject{ GetGameObject() };
	const glm::vec3 currentPos{ gameObject->GetLocalPosition() };
	glm::vec3 newPos{ currentPos + (m_speed * m_direction * dae::GameTime::deltaTime) };

	if (m_grid)
	{
		auto* rectCollider = gameObject->GetComponent<RectColliderComponent>();
		if (!rectCollider) return;

		const auto boundingBox{ rectCollider->GetBoundingBoxInWorld() };
		const auto newBoundinBox = Rect{ newPos.x,newPos.y, boundingBox.width, boundingBox.height };

		const TileType destinationTile{ m_grid->GetCollisionTileType(newBoundinBox) };

		switch (destinationTile)
		{
			case TileType::BorderWallGame:
				newPos = currentPos;
				break;
			case TileType::DirtWall:
				m_grid->DiggedTile(newBoundinBox);
				dae::ServiceLocator::GetSoundSystem().Play(m_digSound, 0.8f);
				break;

			case TileType::Emerald:
				dae::ServiceLocator::GetSoundSystem().Play(m_gemSound, 0.8f);
				m_grid->DiggedTile(newBoundinBox);
				break;

			case TileType::GoldBag:
				dae::ServiceLocator::GetSoundSystem().Play(m_gemSound, 0.8f);
				m_grid->DiggedTile(newBoundinBox);
				break;
		}
		gameObject->SetLocalPosition(newPos);
	}	
}