#pragma once

#include "GameState.h"
#include "Scene/ScoreBoard/HighScoreBoardManager.h"
namespace dae
{
	class DiggerSceneManager;
	class TextComponent;
	class EndScreenState final : public GameState
	{
	public:
		explicit EndScreenState(bool hasWon, int score);
		virtual ~EndScreenState()override = default;
		EndScreenState(const EndScreenState& other) = delete;
		EndScreenState(EndScreenState&& other) = delete;
		EndScreenState& operator=(const EndScreenState& other) = delete;
		EndScreenState& operator=(EndScreenState&& other) = delete;

		virtual void OnEnter(DiggerSceneManager* pDiggerSceneManager) override;
		virtual void LoadScene(DiggerSceneManager* pDiggerSceneManager) override;
		virtual void OnExit(DiggerSceneManager* pDiggerSceneManager) override;

	private:
		bool m_hasWon{ false };
		int m_score{};
		HighScoreBoardManager m_highScoreManager{ HighScoreBoardManager {"Data/Resources/HighScores.txt"} };
		TextComponent* m_nameHighScore{ nullptr };
	};

}