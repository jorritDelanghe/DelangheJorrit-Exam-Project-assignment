#pragma once
#include <string>
#include <memory>
#include <vector>
#include <typeindex>
#include "Component.h"

namespace dae
{
	class Component;
	class GameObject final
	{
	public:
		void Update(float fixedDeltaTime);
		void Render(float extraPolation) const;

		void AddComponent(std::unique_ptr<Component> component);
		bool RemoveComponent(Component* component);

		template <typename T> T* GetComponent() const
		{
			for (const auto& comp : m_components)
			{
				if (auto* typed = dynamic_cast<T*>(comp.get()))
					return typed;
			}
			return nullptr;
		}

		template <typename T> bool HasComponent() const
		{
			return GetComponent<T>() != nullptr;
		}

		GameObject() = default;
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	private:
		std::vector<std::unique_ptr<Component>> m_components{};
	};
	
}
