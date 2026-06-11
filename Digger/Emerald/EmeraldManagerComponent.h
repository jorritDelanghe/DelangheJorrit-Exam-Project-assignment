#pragma once
#include "Component.h"
#include"Scene/Event.h"
#include "Observer.h"
#include "Subject.h"

namespace dae
{
	class GameObject;
	class EmeraldManagerComponent : public Component, public Observer<GameEvent>
	{
	public:
		explicit EmeraldManagerComponent(GameObject* gameObject);
		virtual ~EmeraldManagerComponent()override = default;

		EmeraldManagerComponent(const EmeraldManagerComponent& other) = delete;
		EmeraldManagerComponent(EmeraldManagerComponent&& other) = delete;
		EmeraldManagerComponent& operator=(const EmeraldManagerComponent& other) = delete;
		EmeraldManagerComponent& operator=(EmeraldManagerComponent&& other) = delete;

		virtual void Notify(GameEvent event, GameObject* gameObject) override;
		Subject<GameEvent>& OnAllEmeraldsCollected() { return m_OnAllEmeraldsCollected; }
		void AddEmerald();

	private:
		int m_totalEmeraldCount{};
		int m_collectedEmeraldCount{};

		Subject<GameEvent> m_OnAllEmeraldsCollected{};
	};

}