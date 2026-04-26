#include "LivesDisplayComponent.h"
#include "TextComponent.h"
#include "HealthComponent.h"
#include "GameObject.h"
#include "Event.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <string>

dae::LivesDisplayComponent::LivesDisplayComponent(GameObject* gameObject, const std::string& fileName, float size, float spacing, int startLives)
	:Component(gameObject)
	,m_size(size)
	,m_spacing(spacing)
	, m_lives(startLives)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(fileName);
}

void dae::LivesDisplayComponent::Render() const
{
	DrawLives();
}

void dae::LivesDisplayComponent::Notify(GameEvent event, GameObject* gameObject)
{
	if (event == GameEvent::PlayerDied)
	{
		auto* health = gameObject->GetComponent<HealthComponent>();
		if (health)
		{
			m_lives = health->GetLives();
		}
	}
}

void dae::LivesDisplayComponent::DrawLives() const
{
	const auto pos{GetOwner()->GetLocalPosition()};

	for (int i{}; i < m_lives;++i)
	{
		const float x =pos.x + (m_spacing + m_size) * static_cast<float>(i);
		Renderer::GetInstance().RenderTexture(*m_texture,x,pos.y,m_size,m_size);
	}
}
