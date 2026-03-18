#pragma once
#include "Observer.h"
#include <vector>
#include <memory>
namespace dae
{
	enum class GameEvent;
	class GameObject;
	class Subject final
	{
	public: 
		explicit Subject() = default;
		~Subject() = default;

		Subject(const Subject& other) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator= (Subject && other) = delete;

		void AddObservers(Observer* observer)
		{
			m_observers.push_back(observer);
		}
		void RemoveObserver(Observer* observer)
		{
			m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
		}

		void NotifyObservers(GameEvent event, GameObject* gameObject)
		{
			for (const auto& observer : m_observers)
			{
				observer->Notify(event, gameObject);
			}
		}

	private:
		std::vector<Observer*> m_observers{};
	};

}