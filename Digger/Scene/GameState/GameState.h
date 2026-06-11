#pragma once

#include "Scene/DiggerSceneManager.h"
namespace dae
{
	class GameState
	{
	public:
		virtual ~GameState()= default;
		virtual void OnEnter(DiggerSceneManager* pDiggerSceneManager) = 0;
		virtual void OnExit(DiggerSceneManager* pDiggerSceneManager) = 0;
	};

}