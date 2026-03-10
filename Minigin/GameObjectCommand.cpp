#include "GameObjectCommand.h"
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
	MoveGameObjectCommand::MoveGameObjectCommand(GameObject* gameObject, float speed, const glm::vec3& direction)
		:GameObjectCommand(gameObject)
		,m_speed{speed}
		,m_direction{direction}
	{

	}
	void MoveGameObjectCommand::Execute()
	{
		GetGameObject()->SetLocalPosition(GetGameObject()->GetLocalPosition() + (m_speed * m_direction));
	}
}