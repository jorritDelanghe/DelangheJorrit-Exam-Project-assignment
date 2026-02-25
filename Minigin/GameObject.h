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
		void Render() const;

		bool RemoveComponent(Component* component);

		template<typename T, typename... Args>
		T* AddComponent(Args&&... args)
		{
			auto component = std::make_unique<T>(this, std::forward<Args>(args)...);
			T* ptr = component.get();
			m_components.emplace_back(std::move(component));
			return ptr;
		}
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
		void SetParent(GameObject* parent);
		GameObject* GetParent() const;

		GameObject() = default;
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	private:
		void AddChildren(GameObject* child);
		void RemoveChildren(GameObject* child);
		std::vector<std::unique_ptr<Component>> m_components{};

		GameObject* m_parent{ nullptr };
		std::vector<std::unique_ptr<GameObject>> m_children{};
	};
	
}
