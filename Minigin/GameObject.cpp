
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

void dae::GameObject::SetParent(GameObject* parent)
{
	if (IsChild(parent) || parent == this || parent == m_parent)return;

	if (parent == nullptr)
	{
		SetLocalPosition(GetWorldPosition());
	}
	else
	{
		if (m_keepWorldPosition)
		{
			SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
		}
		SetPositionDirty();
	}
	if (m_parent) m_parent->RemoveChild(this); //if already exist delete from old parent
	m_parent = parent;
	if (m_parent)m_parent->AddChild(this); //if new parent exist add to new parent
}

void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_localPosition = pos;
	SetPositionDirty();
}

const glm::vec3& dae::GameObject::GetLocalPosition() const //if not used later on in the assigment delete it
{
	return m_localPosition;
}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
	if (m_positionDirty)
	{
		UpdateWorldPosition();
	}
	return m_worldPosition;
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_parent;
}

size_t dae::GameObject::GetChildCount() const
{
	return m_children.size();
}

dae::GameObject* dae::GameObject::GetChildAt(unsigned int index) const
{
	return m_children[index].get();
}

void dae::GameObject::AddChild(GameObject* child)
{
	m_children.emplace_back(child);
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	auto iterator = std::find_if(m_children.begin(), m_children.end(), [child](const auto& currentChild) {return currentChild.get() == child; });
	if (iterator != m_children.end())
	{
		m_children.erase(iterator);
	}
}

bool dae::GameObject::IsChild(GameObject* gameObject) const
{
	for (const auto& child : m_children)
	{
		if (child.get() == gameObject)return true;
		if(child->IsChild(gameObject))return true; //looks at the grand children
	}
	return false;
}

void dae::GameObject::SetPositionDirty()
{
	m_positionDirty = true;
	for (auto& child : m_children) //set position for all children also dirty
	{
		child->SetPositionDirty();
	}
}

void dae::GameObject::UpdateWorldPosition()
{
	if (m_parent == nullptr)
	{
		m_worldPosition = m_localPosition;

	}
	else
	{
		m_worldPosition = m_parent->GetWorldPosition() + m_localPosition;
	}
	m_positionDirty = false;
}

