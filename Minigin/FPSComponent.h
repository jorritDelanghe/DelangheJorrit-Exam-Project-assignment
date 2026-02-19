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
		float GetFPS() const;

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

	private:
		int m_frameCount{};
		float m_fps{};
		float m_accumulatedTime{};
	};
}