#include "Font.h"
#include "TextComponent.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "Texture2D.h"
#include "GameObject.h" 
#include <stdexcept>



dae::TextComponent::TextComponent(GameObject* pOwner,std::shared_ptr<Font> font, SDL_Color color)
	:Component(pOwner)
	,m_font(std::move(font))
	, m_color(color)
	,m_renderComponent(pOwner)
{

}
void dae::TextComponent::Render() const
{
	m_renderComponent.Render();
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

	SDL_Surface* surface = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), m_text.length(), m_color);
	if (surface == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surface);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_DestroySurface(surface);
	m_renderComponent.SetTexture(std::make_shared<Texture2D>(texture));
	m_updateTexture = false;
}
