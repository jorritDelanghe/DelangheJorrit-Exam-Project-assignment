#pragma once
#include "Event.h"
namespace dae
{
	class GameObject;

	class Observer
	{
	public:
		explicit Observer() = default;
		virtual ~Observer() = default;

		virtual void Notify(GameEvent event, GameObject* gameObject) = 0;
	};

}
