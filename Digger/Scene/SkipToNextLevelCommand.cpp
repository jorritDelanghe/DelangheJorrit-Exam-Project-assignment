#include "SkipToNextLevelCommand.h"
#include "DiggerSceneManager.h"

dae::SkipToNextLevelCommand::SkipToNextLevelCommand(DiggerSceneManager* sceneManager)
	:m_sceneManager(sceneManager)
{
}

void dae::SkipToNextLevelCommand::Execute()
{
	m_sceneManager->LoadNextLevel();
}
