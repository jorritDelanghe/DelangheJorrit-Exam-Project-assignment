
#include "GameObject.h"
#include <algorithm>
#include <typeindex>

void dae::GameObject::Update(float fixedDeltaTime)
{
	for (auto& component : m_components)
	{
		component->Update(fixedDeltaTime);
	}
}

void dae::GameObject::Render(float extraPolation) const
{
	for (auto& component : m_components)
	{
		component->Render(extraPolation);
	}
}

void dae::GameObject::AddComponent(std::unique_ptr<Component> component)
{
	if (component->GetOwner()) return;
	component->SetOwner(this);
	m_components.push_back(std::move(component));

}

bool dae::GameObject::RemoveComponent(Component* component)
{
	return false;
}
