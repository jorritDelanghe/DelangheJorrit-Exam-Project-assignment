#include "SkipToNextLevelCommand.h"
#include "Scene/DiggerSceneManager.h"
#include "SceneManager.h"

dae::SkipToNextLevelCommand::SkipToNextLevelCommand(DiggerSceneManager* sceneManager)
	:m_sceneManager(sceneManager)
{
}

void dae::SkipToNextLevelCommand::Execute()
{
	SceneManager::GetInstance().SetPendingAction([this]() {
		m_sceneManager->Notify(GameEvent::AllEmeraldsCollected, nullptr);
		});
}
