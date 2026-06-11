#pragma once

#include "GameState.h"
namespace dae
{
	class DiggerSceneManager;
	class StartScreenState final : public GameState
	{
	public:
		explicit StartScreenState() = default;
		virtual ~StartScreenState()override = default;
		StartScreenState(const StartScreenState& other) = delete;
		StartScreenState(StartScreenState&& other) = delete;
		StartScreenState& operator=(const StartScreenState& other) = delete;
		StartScreenState& operator=( StartScreenState&& other) = delete;

		virtual void OnEnter(DiggerSceneManager* pDiggerSceneManager) override;
		virtual void OnExit(DiggerSceneManager* pDiggerSceneManager) override;
	};

}