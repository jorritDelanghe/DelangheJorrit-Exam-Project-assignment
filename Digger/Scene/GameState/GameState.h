#pragma once
#include "Scene/Event.h"
namespace dae
{
	class DiggerSceneManager;
	class GameState
	{
	public:
		virtual ~GameState()= default;
		virtual void OnEnter(DiggerSceneManager* pDiggerSceneManager) = 0;
		virtual void LoadScene(DiggerSceneManager* pDiggerSceneManager) =0;
		virtual void OnExit(DiggerSceneManager* pDiggerSceneManager) = 0;
		virtual void ProccessNotificationsScenes(GameEvent , DiggerSceneManager* ) {}
	};

}