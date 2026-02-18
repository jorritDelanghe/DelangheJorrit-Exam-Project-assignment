#include "FPSComponent.h"
#include <string>

void dae::FPSComponent::Update(float fixedDeltaTime) //goes trough this every frame
{
	++m_frameCount;
	m_accumulatedTime += fixedDeltaTime;

	if (m_accumulatedTime>=1.0f)
	{
		m_fps = static_cast<int>(m_frameCount / m_accumulatedTime);
		m_accumulatedTime = 0.0f;
		m_frameCount = 0;

		if (m_pOwner)
		{
			/*auto textComponent = m_pOwner->GetComponent<TextObject>();
			if (textComponent)
			{
				textComponet->SetText("FPS: " + std::to_string(m_fps));
			}*/
		}
	}
}

int dae::FPSComponent::GetFPS() const
{
	return m_fps;
}
