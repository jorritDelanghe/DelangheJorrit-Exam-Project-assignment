#pragma once

#include "GameState.h"
namespace dae
{
	class DiggerSceneManager;
	class PlayingState final : public GameState
	{
	public:
		explicit PlayingState(bool hasWon, int score);
		virtual ~PlayingState()override = default;
		PlayingState(const PlayingState& other) = delete;
		PlayingState(PlayingState&& other) = delete;
		PlayingState& operator=(const PlayingState& other) = delete;
		PlayingState& operator=(PlayingState&& other) = delete;

		virtual void OnEnter(DiggerSceneManager* pDiggerSceneManager) override;
		virtual void OnExit(DiggerSceneManager* pDiggerSceneManager) override;

	private:
		bool m_hasWon{ false };
		int m_score{};
	};

}