#pragma once
#include "Component.h"

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
	float m_accumulatedTime{};
	int m_frameCount{};
	int m_fps{};
};