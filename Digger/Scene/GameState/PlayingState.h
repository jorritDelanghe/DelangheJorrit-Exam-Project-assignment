#pragma once

#include "GameState.h"
#include <vector>
#include "Scene/Leveldata.h"
#include "Scene/Event.h"
namespace dae
{
	class DiggerSceneManager;
	class GameObject;
	class PlayingState final : public GameState
	{
	public:
		explicit PlayingState() = default;
		virtual ~PlayingState()override = default;
		PlayingState(const PlayingState& other) = delete;
		PlayingState(PlayingState&& other) = delete;
		PlayingState& operator=(const PlayingState& other) = delete;
		PlayingState& operator=(PlayingState&& other) = delete;

		virtual void OnEnter(DiggerSceneManager* pDiggerSceneManager) override;
		virtual void LoadScene(DiggerSceneManager* pDiggerSceneManager) override;
		virtual void OnExit(DiggerSceneManager* pDiggerSceneManager) override;
		virtual void ProccessNotificationsScenes(GameEvent event, DiggerSceneManager* pDiggerSceneManager) override;

	private:
		bool m_hasWon{ false };
		DiggerSceneManager* m_pDiggerSceneManager{ nullptr };

		int m_currentScore{};
		int m_currentLives{ 3 };

		GameObject* m_currentPlayer{ nullptr };
		int m_currentLevelIndex{};
		std::vector<LevelData> m_Levels{
		LevelData{"Data/Resources/Level02Test.txt"}
		,LevelData{"Data/Resources/Level02Test.txt"}
		,LevelData{"Data/Resources/Level02Test.txt"}
		};

		void LoadNextLevel();
		void LoadDiggerLevel(const LevelData& levelData);
		void ResetCurrentLevel();
		void SaveCurrentGameData();
	};

}