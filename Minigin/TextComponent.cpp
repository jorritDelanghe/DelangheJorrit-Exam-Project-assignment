#include "Font.h"
#include "TextComponent.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "Texture2D.h"
#include "GameObject.h" 
#include <stdexcept>



dae::TextComponent::TextComponent(std::shared_ptr<Font> font, SDL_Color color)
	: m_font(std::move(font))
	, m_color(color)
{

}
void dae::TextComponent::Render() const
{
	if (!m_textTexture || !m_pOwner) return;

	auto transform = m_pOwner->GetComponent<TransformComponent>();
	if (!transform) return;
	dae::Renderer::GetInstance().RenderTexture(*m_textTexture
												, transform->GetPosition().x
												,transform->GetPosition().y);

}

void dae::TextComponent::SetText(const std::string& text)
{
	if (m_text == text) return;

	m_text = text;
	m_updateTexture = true;
	UpdateTexture();	
}

void dae::TextComponent::UpdateTexture()
{
	if (!m_updateTexture) return;
	if (!m_font) return;

	const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), m_text.length(), m_color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_DestroySurface(surf);
	m_textTexture = std::make_shared<Texture2D>(texture);
	m_updateTexture = false;
}
