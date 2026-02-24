#include "Component.h"
#include "stdexcept"
#include "Gameobject.h"


dae::Component::Component(GameObject* pOwner)
{
	SetOwner(pOwner);
}

void dae:: Component::Update(float) //not every game object needs an update so not pure virtual
{

}

void dae::Component::Render() const //not every game object needs a render so not pure virtual
{

}
dae::GameObject* dae::Component::GetOwner() const
{
	return m_pOwner;
}
void dae::Component::SetOwner(GameObject* owner)
{
	if (m_pOwner != nullptr)
	{
		throw std::logic_error("Component already has an owner");
	}
	m_pOwner = owner; 
}
