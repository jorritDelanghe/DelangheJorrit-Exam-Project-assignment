#pragma once
namespace dae
{
	class GameObject;
	enum class Event;

	class Observer
	{
	public:
		explicit Observer() = default;
		virtual ~Observer() = default;

		virtual void Notify(GameEvent event, GameObject* gameObject) = 0;
	};

}
