#pragma once

#include "DiggerSceneManager.h"
namespace dae
{
	class GameState
	{
	public:
		virtual ~GameState()= default;
		virtual OnEnter(DiggerSceneManager* pDiggerSceneManager) = 0;
		virtual OnExit(DiggerSceneManager* pDiggerSceneManager) = 0;
	};

}