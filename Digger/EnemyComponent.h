#pragma once
#include "Component.h"
#include <memory>
#include "EnemyState.h"
namespace dae
{
	class GridComponent;
	class EnemyComponent final : public Component
	{
	public:
		explicit EnemyComponent(GameObject* pGameObject, GridComponent* grid,GameObject* player);
		~EnemyComponent() = default;

		EnemyComponent(const EnemyComponent& other) = delete;
		EnemyComponent(EnemyComponent&& other) = delete;
		EnemyComponent& operator=(const EnemyComponent& other) = delete;
		EnemyComponent& operator=(EnemyComponent&& other) = delete;

		virtual void Update(float deltaTime) override;
		//virtual void Render() const;
	private:
		GridComponent* m_grid{};
		std::unique_ptr<EnemyState> m_state;
		bool m_pendingEnter{};
		GameObject* m_player{};

		void SetState(EnemyState* newState);

	};
}