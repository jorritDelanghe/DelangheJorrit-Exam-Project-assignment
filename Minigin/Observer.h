#pragma once
namespace dae
{
	class GameObject;

	template<typename EventType> //needed so that event logic is in the game
	class Observer
	{
	public:
		explicit Observer() = default;
		virtual ~Observer() = default;

		virtual void Notify(EventType event, GameObject* gameObject) = 0;
	};

}
