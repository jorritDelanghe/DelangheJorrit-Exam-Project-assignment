#include "MoveDiggerCommand.h"
#include "GameObject.h"
#include "GameTime.h"
#include "ServiceLocator.h"

dae::MoveDiggerCommand::MoveDiggerCommand(dae::GameObject* gameObject, float speed, const glm::vec3& direction
	, dae::GridComponent* grid,dae::SoundID soundID, dae::SoundID gemSound, PointsComponent* pPoints
	, std::vector<GoldBagComponent*> goldBags)
	:GameObjectCommand(gameObject)
	, m_direction{ direction }
	, m_speed{ speed }
	, m_grid{ grid }
	, m_digSound{ soundID }
	, m_gemSound{ gemSound }
	,m_pPoints{pPoints}
	,m_bags(goldBags)
{

}
void dae::MoveDiggerCommand::Execute()
{
	auto* gameObject{ GetGameObject() };
	const glm::vec3 currentPos{ gameObject->GetLocalPosition() };
	const glm::vec3 newPos{ currentPos + (m_speed * m_direction * dae::GameTime::deltaTime) };

	if (m_grid)
	{
		const int newCol{ m_grid->WorldToCol(newPos.x) };
		const int newRow{ m_grid->WorldToRow(newPos.y) };

		const TileType destinationTile{ m_grid->GetGrid().GetTileType(newCol, newRow) };
		if (!m_grid->GetGrid().IsInGrid(newCol, newRow) || destinationTile == TileType::BorderWallGame)
		{
			return;
		}
		
		constexpr int gemPoints{ 40 };
		constexpr int goldBagPoints{ 80 };

		switch (destinationTile)
		{
		case TileType::DirtWall:
			dae::ServiceLocator::GetSoundSystem().Play(m_digSound, 0.8f);
			break;

		case TileType::Emerald:
			dae::ServiceLocator::GetSoundSystem().Play(m_gemSound, 0.8f);
			m_pPoints->AddScore(gemPoints);
			break;

		case TileType::GoldBag:
			dae::ServiceLocator::GetSoundSystem().Play(m_gemSound, 0.8f);
			m_pPoints->AddScore(goldBagPoints);
			break;
		}
		for (auto* bag : m_bags)
		{
			bag->HandleInput(currentPos);
		}
		m_grid->DiggedTile(newCol, newRow);
	}
	gameObject->SetLocalPosition(newPos);
}