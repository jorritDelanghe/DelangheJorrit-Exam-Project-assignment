#pragma once
#include "Component.h"
#include <SDL3/SDL.h>
#include <memory>
#include "Observer.h"
namespace dae
{
	class TextComponent;
	class GameObject;
	class Font;
	class PointsDisplayComponent final : public Component ,public Observer
	{
	public:
		explicit PointsDisplayComponent(GameObject* pGameObject,
			std::shared_ptr<Font> font, SDL_Color color);
		virtual ~PointsDisplayComponent() noexcept override = default;
		PointsDisplayComponent(const PointsDisplayComponent& other) = delete;
		PointsDisplayComponent(PointsDisplayComponent&& other) = delete;
		PointsDisplayComponent& operator= (const PointsDisplayComponent& other) = delete;
		PointsDisplayComponent& operator= (PointsDisplayComponent&& other) = delete;

		virtual void Notify(GameEvent event, GameObject* pGameObject) override;
	private:
		TextComponent* m_pText{nullptr};
	};

}
