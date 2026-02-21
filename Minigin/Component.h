#pragma once

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		explicit Component(GameObject*pOwner);
		virtual ~Component() = default;

		virtual void Update(float deltaTime);
		virtual void Render() const;

		GameObject* GetOwner() const;

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

	protected:
		void SetOwner(GameObject* owner);
		GameObject* m_pOwner{}; // pointer to the owning GameObject (namespaced)
	};
}

