#pragma once
#include "Component.h"
#include <chrono>
namespace dae
{
	class FPSComponent final : public Component
	{
	public:
		FPSComponent() = default;
		virtual ~FPSComponent() override = default;

		virtual void Update(float fixedDeltaTime) override;
		int GetFPS() const;

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

	private:
		std::chrono::time_point<std::chrono::steady_clock> m_lastTime{};
		int m_frameCount{};
		int m_fps{};
	};
}