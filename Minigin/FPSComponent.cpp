#include "FPSComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include <string>
#include <iostream>


void dae::FPSComponent::Update(float /*fixedDeltaTime*/) //goes trough this every frame
{
	++m_frameCount;

	auto now = std::chrono::steady_clock::now();
	float elapsed = std::chrono::duration<float>(now - m_lastTime).count();

	if (elapsed >= 1.f)
	{
		m_fps = static_cast<int>(m_frameCount/ elapsed);
	
		m_frameCount = 0;
		m_lastTime = now;

		auto textComponent = m_pOwner->GetComponent<dae::TextComponent>();
		if (textComponent)
		{
			textComponent->SetText("FPS: " + std::to_string(m_fps));
		}
	}
}

int dae::FPSComponent::GetFPS() const
{
	return m_fps;
}
