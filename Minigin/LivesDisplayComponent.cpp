#include "LivesDisplayComponent.h"
#include "TextComponent.h"
#include "HealthComponent.h"
#include "GameObject.h"
#include "Event.h"
#include <string>

dae::LivesDisplayComponent::LivesDisplayComponent(GameObject* gameObject, std::shared_ptr<Font> font, SDL_Color color, int startLives)
	:Component(gameObject)
{
	m_text = gameObject->AddComponent<TextComponent>(font, color);
	m_text->SetText("Lives: " + std::to_string(startLives));
}

void dae::LivesDisplayComponent::Notify(GameEvent event, GameObject* gameObject)
{
	if (event == GameEvent::PlayerDied)
	{
		auto* health = gameObject->GetComponent<HealthComponent>();
		if (health && m_text)
		{
			m_text->SetText("Lives: " + std::to_string(health->GetLives()));
		}
	}
}
