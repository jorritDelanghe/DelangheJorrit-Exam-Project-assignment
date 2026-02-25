#include "RenderComponent.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "GameObject.h" 
#include "Texture2D.h"

dae::RenderComponent::RenderComponent(GameObject* pOwner)
    :Component(pOwner)
{
}
dae::RenderComponent::RenderComponent(GameObject* pOwner,const std::string& filename)
	:Component(pOwner)
{
	SetTexture(filename);
}
void dae::RenderComponent::Render() const
{
    RenderTexture(m_texture);
}
void dae::RenderComponent::RenderTexture(std::shared_ptr<dae::Texture2D> texture) const
{
    if (!texture || !m_pOwner) return;

    const auto& pos = m_pOwner->GetWorldPosition();
    Renderer::GetInstance().RenderTexture(*texture,
        pos.x, pos.y);
}
void dae::RenderComponent::SetTexture(const std::string& filename)
{
    m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}
void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
    m_texture = texture;
}