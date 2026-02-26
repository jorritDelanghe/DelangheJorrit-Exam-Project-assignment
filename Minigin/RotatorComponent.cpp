#include "RotatorComponent.h"
#include <math.h>

dae::RotatorComponent::RotatorComponent(GameObject* pOwner, float speed, float radius)
	:Component(pOwner)
	, m_speed(speed)
	, m_radius(radius)
	, m_angle(0.f)
{
}

void dae::RotatorComponent::Update(float deltaTime)
{
	constexpr float twoPi{ 2.f * 3.14159265f };
	if (m_angle >= twoPi) m_angle = 0.f; //reset angle to prevent overflow
	m_angle += m_speed * deltaTime;
	float x = std::cos(m_angle) * m_radius;
	float y = std::sin(m_angle) * m_radius;
	m_pOwner->SetLocalPosition({x,y,0.f});
}
