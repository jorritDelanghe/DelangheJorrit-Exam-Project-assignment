#include "GoldBagComponent.h"
#include "GameObject.h"
#include "IdleState.h"
//needed for nugget
#include "Scene.h"
#include "RenderComponent.h"
#include "Collision/RectColliderComponent.h"
dae::GoldBagComponent::GoldBagComponent(GameObject* pGameObject, GridComponent* pGrid, Scene& scene)
	:Component(pGameObject)
	,m_state(std::make_unique<IdleState>())
	,m_grid(pGrid)
	, m_scene(scene)
{

}
void dae::GoldBagComponent::HandleInput(glm::vec3 playerPos)
{
	GoldBagState* newState{ m_state->HandleInputs(this, m_grid, playerPos) };

	if (newState)
	{
		SetState(newState);
	}
}
void dae::GoldBagComponent::SetState(GoldBagState* newState)
{
	m_state.reset(newState);
}
void dae::GoldBagComponent::SpawnGoldNugget()
{
	auto goldNugget = std::make_unique<GameObject>();
	auto* img = goldNugget->AddComponent<RenderComponent>("Resources/SoloGold.png",20.f,20.f);
	goldNugget->AddComponent<RectColliderComponent>(Size{ img->GetSizeImage().width, img->GetSizeImage().height }, CollisionTag::GoldNugget);

	goldNugget->SetLocalPosition(GetOwner()->GetLocalPosition());
	m_scene.Add(std::move(goldNugget));
}
void dae::GoldBagComponent::Update(float deltaTime)
{
	GoldBagState* newState{ m_state->Update(this, deltaTime) };

	if (newState)
	{
		SetState(newState);
		m_state->OnEnter(this);
	}
}