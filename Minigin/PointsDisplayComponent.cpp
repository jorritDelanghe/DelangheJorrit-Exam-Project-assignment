# include "PointsDisplayComponent.h"
#include "TextComponent.h"
#include "PointsComponent.h"
#include "GameObject.h"
#include "Event.h"
#include <string>

dae::PointsDisplayComponent::PointsDisplayComponent(GameObject* pGameObject,
    std::shared_ptr<Font> font, SDL_Color color)
    : Component(pGameObject)
{
    m_pText = pGameObject->AddComponent<TextComponent>(font, color);
    m_pText->SetText("00000");
}

void dae::PointsDisplayComponent::Notify(GameEvent event, GameObject* pGameObject)
{
    if (event != GameEvent::PlayerPickedUp) return;
    auto* points = pGameObject->GetComponent<PointsComponent>();
    if (points && m_pText)
    {
        const std::string score{ std::to_string(points->GetScore()) };
        const std::string scoreText{ std::string(5 - std::min(score.size(),size_t(5)),'0') + score};

        m_pText->SetText("Points: " + std::to_string(points->GetScore()));
    }
}
