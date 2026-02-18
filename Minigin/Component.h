#pragma once
class GameObject;
class Component
{
public:
	Component() = default;
	virtual ~Component() = default;

	virtual void Update(float fixedDeltaTime); 
	virtual void Render(float extraPolation) const;
	
	void SetOWner(GameObject* owner);

	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

private:
	GameObject* m_pOwner{}; //easy to pass components that the gameobject has to other components, components dont care by each others existance
};