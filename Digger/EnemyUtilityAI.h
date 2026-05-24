#pragma once
#include "EnemyState.h"
#include <memory>
#include "Component.h"
#include "PointsComponent.h"
#include <functional>
#include <string>
#include <glm/glm.hpp>

//Builds an AIContext from current world state
//Scores every registered UtilityAction using that context
//Finds the highest scorer
//Compares to the current active state name ,if different, creates new state
namespace dae
{

	class GameObject;
	class EnemyComponent;
	class GridComponent;
	class EnemyUtilityAI final :public Component
	{
	public:
		struct GameStats
		{
			int collectedPoints{};
			glm::vec3 enemyPos{};
			glm::vec3 playerPos{};
			float chasingRadius{ 150.f };
			float distancePlayer{ 0.f };
			bool isOnTunnel{ false };

		};

		struct UtilityAiAction
		{
			std::string nameAction{};
			std::function<float(const GameStats&)> scorer{};
			std::function<EnemyState* ()> createState{};
		};

		explicit EnemyUtilityAI(GameObject* pOwner, EnemyComponent* enemy, GridComponent* grid,
			GameObject* player, PointsComponent* pPoints);
		virtual ~EnemyUtilityAI() override = default;

		EnemyUtilityAI(const EnemyUtilityAI& other) = delete;
		EnemyUtilityAI(EnemyUtilityAI&& other) = delete;
		EnemyUtilityAI& operator=(const EnemyUtilityAI& other) = delete;
		EnemyUtilityAI& operator=(EnemyUtilityAI&& other) = delete;

		virtual void Update(float deltaTime) override;

		//curve helpers
		static float GetLinearCurve(float value, float maxValue); //0-1, geleidelijke acties
		static float GetScoringQuadraticCurve(float value, float maxValue); //around zero stays around zero, more extreem actions
		static float GetPercentage(int currentValue, int maxValue);

		//actions
		void RegisterNewAction(const std::string& nameAction,
			std::function<float(const GameStats&)> scorer,
			std::function<EnemyState* ()> createState);
		void RegisterNewAction(const UtilityAiAction& action);
	private:

		GameStats GetGameStats() const;
		float ScoreCurrent(const GameStats& gameStats)const;

		EnemyComponent* m_pEnemy{ nullptr };
		GridComponent* m_pGrid{ nullptr };
		GameObject* m_pPlayer{ nullptr };
		PointsComponent* m_pPoints{};

		const float m_oscillationThreshold{ 0.05f }; //prevents switching between states to rapidly

		std::vector<UtilityAiAction> m_actions{};
		std::string m_currentName{};
	};

}