#include "TransformComponent.h"

void TransformComponent::SetPosition(const glm::vec2& pos)
{
	m_position = pos;
}

void TransformComponent::SetPosition(float x, float y)
{
	SetPosition(glm::vec2(x, y));
}

void TransformComponent::SetRotation(float rot)
{
	m_rotation = rot;
}

void TransformComponent::SetScale(const glm::vec2& scale)
{
	m_scale = scale;
}

void TransformComponent::SetScale(float x, float y)
{
	SetScale(glm::vec2(x, y));
}

const glm::vec2& TransformComponent::GetPosition() const
{
	return m_position;
}

float TransformComponent::GetRotation() const
{
	return m_rotation;
}

const glm::vec2& TransformComponent::GetScale() const
{
	return m_scale;
}
