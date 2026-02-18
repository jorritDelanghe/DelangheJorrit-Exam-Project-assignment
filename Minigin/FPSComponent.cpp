#include "FPSComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include <string>

void dae::FPSComponent::Update(float fixedDeltaTime) //goes trough this every frame
{
	++m_frameCount;
	m_accumulatedTime += fixedDeltaTime;

	if (m_accumulatedTime>=1.0f)
	{
		m_fps = static_cast<int>(m_frameCount);
		m_accumulatedTime = 0.0f;
		m_frameCount = 0;

		if (m_pOwner)
		{
			auto textComponent = m_pOwner->GetComponent<dae::TextComponent>();
			if (textComponent)
			{
				textComponent->SetText("FPS: " + std::to_string(m_fps));
			}
		}
	}
}

int dae::FPSComponent::GetFPS() const
{
	return m_fps;
}
