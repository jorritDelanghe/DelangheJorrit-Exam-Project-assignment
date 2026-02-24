#include "RenderComponent.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "GameObject.h" 
#include "Texture2D.h"

dae::RenderComponent::RenderComponent(GameObject* pOwner,const std::string& filename)
	:Component(pOwner)
{
    m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::Render() const
{
    if (!m_texture || !m_pOwner) return;

    auto transform = m_pOwner->GetComponent<TransformComponent>();
    if (!transform) return;

    dae::Renderer::GetInstance().RenderTexture(*m_texture,
        transform->GetPosition().x, transform->GetPosition().y);
}