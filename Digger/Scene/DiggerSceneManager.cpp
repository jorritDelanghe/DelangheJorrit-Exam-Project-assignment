#include "DiggerSceneManager.h"
#include "DiggerScene.h"

//sound
#include "ServiceLocator.h"
#include "SDLSoundSystem.h"

//collision
#include "Collision/CollisionSystem.h"

dae::DiggerSceneManager::DiggerSceneManager()
{
	InitSound(); //all sounds for the game
}

void dae::DiggerSceneManager::LoadNextLevel()
{
	if(m_currentLevelIndex >= m_Levels.size())
	{
		m_currentLevelIndex = 0;
	}

	LoadDiggerLevel(m_Levels[m_currentLevelIndex]);
	++m_currentLevelIndex;
}

void dae::DiggerSceneManager::LoadDiggerLevel(const LevelData& levelData)
{
	//clear the current colliders
	CollisionSystem::GetInstance().ClearCollideders(); // reset observers

	DiggerScene diggerScene{ levelData };
	diggerScene.LoadScene();
}
void dae::DiggerSceneManager::InitSound() const
{
	ServiceLocator::RegisterSounSystem(std::make_unique<SDLSoundSystem>());
	ServiceLocator::GetSoundSystem().AddSound("Data/Resources/DeathSound.wav");
	ServiceLocator::GetSoundSystem().AddSound("Data/Resources/piano2.wav");
}