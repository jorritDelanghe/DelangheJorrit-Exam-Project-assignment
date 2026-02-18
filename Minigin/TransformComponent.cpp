#include "TransformComponent.h"

void dae::TransformComponent::SetPosition(const glm::vec2& pos)
{
	m_position = pos;
}

void dae::TransformComponent::SetPosition(float x, float y)
{
	SetPosition(glm::vec2(x, y));
}

void dae::TransformComponent::SetRotation(float rot)
{
	m_rotation = rot;
}

void dae::TransformComponent::SetScale(const glm::vec2& scale)
{
	m_scale = scale;
}

void dae::TransformComponent::SetScale(float x, float y)
{
	SetScale(glm::vec2(x, y));
}

const glm::vec2& dae::TransformComponent::GetPosition() const
{
	return m_position;
}

float dae::TransformComponent::GetRotation() const
{
	return m_rotation;
}

const glm::vec2& dae::TransformComponent::GetScale() const
{
	return m_scale;
}
