#pragma once
#include "Component.h"
#include "Subject.h"
#include "Observer.h"

namespace dae
{
	class GameObject;
	class PointsComponent final : public Component, public Observer<GameEvent>
	{
	public:
		explicit PointsComponent(GameObject* gameObject);

		virtual ~PointsComponent()noexcept override  = default;
		PointsComponent(const PointsComponent& other) = delete;
		PointsComponent(PointsComponent&& other) = delete;
		PointsComponent& operator=(const PointsComponent& other) = delete;
		PointsComponent& operator=(PointsComponent&& other) = delete;

		virtual void Notify(GameEvent event, GameObject* pGameObject) override;
		void AddEmerad();
		void AddScore(int points);
		int GetScore() const { return m_score; }
		Subject<GameEvent>& OnPointsChanged() { return m_onPointsChanged; }
	private:
		int m_emeraldStreak{};
		int m_score{};
		Subject<GameEvent> m_onPointsChanged;
	};

}