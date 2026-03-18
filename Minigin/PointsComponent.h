#pragma once
#include "Component.h"
#include "Subject.h"

namespace dae
{
	class GameObject;
	class PointsComponent final : public Component
	{
	public:
		explicit PointsComponent(GameObject* gameObject);

		virtual ~PointsComponent()noexcept override  = default;
		PointsComponent(const PointsComponent& other) = delete;
		PointsComponent(PointsComponent&& other) = delete;
		PointsComponent& operator=(const PointsComponent& other) = delete;
		PointsComponent& operator=(PointsComponent&& other) = delete;

		void AddScore(int points);
		int GetScore() const { return m_score; }
		Subject& OnPointsChanged() { return m_onPointsChanged; }
	private:
		int m_score{};
		Subject m_onPointsChanged;
	};

}