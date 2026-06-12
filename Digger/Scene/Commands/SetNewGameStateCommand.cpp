#include "SetNewGameStateCommand.h"
#include"Scene/DiggerSceneManager.h"
#include "Scene/GameState/PlayingState.h"

dae::SetNewGameStateCommand::SetNewGameStateCommand(DiggerSceneManager* sceneManager)
	:m_sceneManager(sceneManager)
{
}

void dae::SetNewGameStateCommand::Execute()
{
	m_sceneManager->SetState(std::make_unique<PlayingState>());
}
