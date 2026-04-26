#pragma once
#include "Component.h"
#include "Observer.h"
#include <memory>
#include <SDL3/SDL.h>  
#include "Texture2D.h"

namespace dae
{
	class TextComponent;
	enum class GameEvent;
	class GameObject;
	class Font;

	class LivesDisplayComponent final : public Component, public Observer
	{
	public:
		explicit LivesDisplayComponent(GameObject* gameObject, const std::string& fileName, float size, float spacing, int startLives);
		virtual ~LivesDisplayComponent() noexcept override = default;

		LivesDisplayComponent(const LivesDisplayComponent& other) = delete;
		LivesDisplayComponent(LivesDisplayComponent&& other) = delete;
		LivesDisplayComponent& operator=(const LivesDisplayComponent& other) = delete;
		LivesDisplayComponent& operator= (LivesDisplayComponent&& other) = delete;

		virtual void Render() const override;
		virtual void Notify(GameEvent event, GameObject* gameObject) override;
	private:
		void DrawLives() const;

		std::shared_ptr<Texture2D>m_texture;
		float m_size{};
		float m_spacing{};
		int m_lives{};
	};

}