#include "RotatorComponent.h"

dae::RotatorComponent::RotatorComponent(GameObject* pOwner, float speed, float radius)
	:Component(pOwner)
	, m_speed(speed)
	, m_radius(radius)
	, m_angle(0.f)
{
}

void dae::RotatorComponent::Update(float deltaTime)
{
	m_angle += m_speed * deltaTime;
	float x = std::cos(m_angle) * m_radius;
	float y = std::sin(m_angle) * m_radius;
	m_pOwner->SetLocalPosition({x,y,0.f});
}
