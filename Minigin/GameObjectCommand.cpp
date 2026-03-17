#include "GameObjectCommand.h"
#include "HealthComponent.h"
#include "Time.h"
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
		,m_direction{direction}
		,m_speed{speed}
	{

	}
	void MoveGameObjectCommand::Execute()
	{
		GetGameObject()->SetLocalPosition(GetGameObject()->GetLocalPosition() + (m_speed * m_direction* dae::Time::deltaTime));
	}
	void DieCommand::Execute()
	{
		GetGameObject()->GetComponent<HealthComponent>()->Die();
	}
}