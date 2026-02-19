#include "FPSComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>


void dae::FPSComponent::Update(float fixedDeltaTime) //goes trough this every frame
{
	++m_frameCount;
	m_accumulatedTime += fixedDeltaTime;

	if (m_accumulatedTime >= 1.f)
	{
		m_fps = static_cast<float>(m_frameCount)/ m_accumulatedTime;
	
		std::ostringstream oss;
		oss << std::fixed << std::setprecision(2) << m_fps << " FPS";

		auto textComponent = m_pOwner->GetComponent<TextComponent>();
		if (textComponent)
		{
			textComponent->SetText(oss.str());
		}

		m_frameCount = 0;
		m_accumulatedTime = 0.f;
	}
}

float dae::FPSComponent::GetFPS() const
{
	return m_fps;
}
