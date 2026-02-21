#include "Component.h"
#include "stdexcept"
#include "Gameobject.h"


void dae:: Component::Update(float)
{

}

void dae::Component::Render() const //not every game object needs a render so not virtual
{
}

void dae::Component::SetOwner(GameObject* owner)
{
	if (m_pOwner != nullptr)
	{
		throw std::logic_error("Component already has an owner");
	}
	m_pOwner = owner; 
}

dae::GameObject* dae::Component::GetOwner() const
{
	return m_pOwner;
}
