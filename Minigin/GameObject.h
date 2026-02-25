#pragma once
#include <string>
#include <memory>
#include <vector>
#include <typeindex>
#include "Component.h"
#include <glm/glm.hpp>

namespace dae
{
	class Component;
	class GameObject final
	{
	public:
		//rule of 5
		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

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
		//scene graph
		void SetParent(GameObject* parent);
		GameObject* GetParent() const;

		size_t GetChildCount() const;
		GameObject* GetChildAt(unsigned int index)const;

		//transform
		void SetLocalPosition(const glm::vec3& pos);
		const glm::vec3& GetLocalPosition() const;
		const glm::vec3& GetWorldPosition();

	private:
		void AddChildren(GameObject* child);
		void RemoveChildren(GameObject* child);
		bool IsChild(GameObject* gameObject)const;
		void SetPositionDirty();
		void UpdateWorldPosition();


		GameObject* m_parent{ nullptr };
		std::vector<GameObject*> m_children{};

		std::vector<std::unique_ptr<Component>> m_components{};

		glm::vec3 m_localPosition{};
		glm::vec3 m_worldPosition{};
		bool m_positionDirty{ true };
	};
	
}
