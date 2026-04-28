#pragma once

#include "GameObjectCommand.h"
#include "GridComponent.h"
#include <glm/glm.hpp>

using namespace dae;
class GridComponent;
class GameObject;
class MoveDiggerCommand final : public GameObjectCommand
{
public:
	explicit MoveDiggerCommand(dae::GameObject* gameObject, float speed, const glm::vec3& direction, dae::GridComponent* grid);
	virtual ~MoveDiggerCommand() noexcept override = default;

	MoveDiggerCommand(const MoveDiggerCommand& other) = delete;
	MoveDiggerCommand(MoveDiggerCommand&& other) = delete;
	MoveDiggerCommand& operator= (const MoveDiggerCommand& other) = delete;
	MoveDiggerCommand& operator= (MoveDiggerCommand&& other) = delete;

	virtual void Execute() override;

private:
	glm::vec3 m_direction;
	float m_speed;
	dae::GridComponent* m_grid;

};