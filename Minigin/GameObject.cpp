
#include "GameObject.h"
#include <algorithm>
#include <typeindex>

void dae::GameObject::Update(float deltaTime)
{
	for (auto& component : m_components)
	{
		component->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (auto& component : m_components)
	{
		component->Render();
	}
}

bool dae::GameObject::RemoveComponent(Component* component)
{
	auto it = std::find_if(m_components.begin(), m_components.end(),
		[component](const auto& comp) { return comp.get() == component; });
	if (it != m_components.end())
	{
		m_components.erase(it);
		return true;
	}
	return false;
}

