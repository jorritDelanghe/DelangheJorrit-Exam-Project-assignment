#include "Component.h"
#include "stdexcept"

void Component::Update(float /*fixedDeltaTime*/)
{

}

void Component::Render(float /*extraPolation*/) const //not every game object needs a render so not virtual
{
}

void Component::SetOWner(GameObject* owner)
{
	if (m_pOwner != nullptr)
	{
		throw std::logic_error("Component already has an owner");
	}
	m_pOwner = owner; 
}
