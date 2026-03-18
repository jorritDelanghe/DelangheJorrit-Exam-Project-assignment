#pragma once
#include "Component.h"
#include "Observer.h"
#include <memory>
#include <SDL3/SDL.h>  

namespace dae
{
	class TextComponent;
	enum class GameEvent;
	class GameObject;
	class Font;

	class LivesDisplayComponent final : public Component, public Observer
	{
	public:
		explicit LivesDisplayComponent(GameObject* gameObject, std::shared_ptr<Font> font, SDL_Color color, int startLives);
		virtual ~LivesDisplayComponent() noexcept override = default;

		LivesDisplayComponent(const LivesDisplayComponent& other) = delete;
		LivesDisplayComponent(LivesDisplayComponent&& other) = delete;
		LivesDisplayComponent& operator=(const LivesDisplayComponent& other) = delete;
		LivesDisplayComponent& operator= (LivesDisplayComponent&& other) = delete;

		virtual void Notify(GameEvent event, GameObject* gameObject) override;
	private:
		TextComponent* m_text{nullptr};
	};

}