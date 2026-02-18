#pragma once
#include "Component.h"
#include <string>
#include <memory>
#include <SDL3_ttf/SDL_ttf.h>


class Font;
class Texture2D;
class TextComponent final : public Component
{
public:
	TextComponent(std::shared_ptr<Font> font, SDL_Color color);
	virtual ~TextComponent() override = default;

	virtual void Render(float extraPolation) const override;
	void SetText(const std::string& text);

	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) = delete;

private:

	void UpdateTexture();

	std::string m_text{};
	std::shared_ptr<Font> m_font{};
	SDL_Color m_color{};
	std::shared_ptr<Texture2D> m_textTexture{nullptr};
	bool m_updateTexture{true};
};