#include "SetNewGameStateCommand.h"
#include"Scene/DiggerSceneManager.h"
#include "Scene/GameState/PlayingState.h"

dae::SetNewGameStateCommand::SetNewGameStateCommand(DiggerSceneManager* sceneManager, std::unique_ptr<GameState> pGameState)
	:m_sceneManager(sceneManager)
	,m_gameState(std::move(pGameState))
{
}

void dae::SetNewGameStateCommand::Execute()
{
	m_sceneManager->SetState(std::move(m_gameState));
}
