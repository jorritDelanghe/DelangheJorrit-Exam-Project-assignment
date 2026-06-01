#include "RectColliderComponent.h"
#include "Renderer.h"
#include "CollisionSystem.h"
#include "gameObject.h"
dae::RectColliderComponent::RectColliderComponent(GameObject* pOwner, const Size& size, CollisionTag tag)
	:Component(pOwner)
	,m_boundingBox({ m_pOwner->GetLocalPosition().x,m_pOwner->GetLocalPosition().y, size.width, size.height})
	,m_tag(tag)
{
	CollisionSystem::GetInstance().AddCollider(this);
}

dae::RectColliderComponent::~RectColliderComponent()
{
	CollisionSystem::GetInstance().RemoveCollider(this); //delete out of list
}

void dae::RectColliderComponent::Update(float )
{
	const auto& pos = m_pOwner->GetWorldPosition();
	m_boundingBox.x = pos.x;
	m_boundingBox.y = pos.y;
}

void dae::RectColliderComponent::Render() const
{
	SDL_FRect rect{ static_cast<float>(m_boundingBox.x),
		static_cast<float>(m_boundingBox.y),
		static_cast<float>(m_boundingBox.width),
		static_cast<float>(m_boundingBox.height)
	};

	SDL_Renderer* renderer = Renderer::GetInstance().GetSDLRenderer();

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderRect(renderer,  &rect);
}

void dae::RectColliderComponent::SetTag(CollisionTag tag)
{
	m_tag = tag;
}

const dae::Rect& dae::RectColliderComponent::GetBoundingBoxInWorld() const
{
	return m_boundingBox;
}
