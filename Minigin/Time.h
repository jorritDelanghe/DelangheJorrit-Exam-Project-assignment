#pragma once
#include "Singleton.h"
namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:
		void SetDeltaTime(float deltaTime) { m_deltaTime = deltaTime; }
		float GetDeltaTime() const { return m_deltaTime; }
	private:
		float m_deltaTime{0.f};
	};
}