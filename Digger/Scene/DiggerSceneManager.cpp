
#include "DiggerSceneManager.h"
#include "DiggerScene.h"

//sound
#include "ServiceLocator.h"
#include "SDLSoundSystem.h"

//input
#include <SDL3/SDL.h> //needs to be above inputmanager otherwise it doesnt know it
#include "InputManager.h"
#include "MuteSoundCommand.h"
#include "SkipToNextLevelCommand.h"
#include "SceneManager.h"

//collision
#include "Collision/CollisionSystem.h"
#include "PointsComponent.h"
#include "Player/HealthComponent.h"

#include "SkipToNextLevelCommand.h"

dae::DiggerSceneManager::DiggerSceneManager()
{
	InitSound(); //all sounds for the game
	InitInput();
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

void dae::DiggerSceneManager::ResetCurrentLevel()
{
	LoadDiggerLevel(m_Levels[m_currentLevelIndex]);
}

void dae::DiggerSceneManager::LoadDiggerLevel(const LevelData& levelData)
{
	DiggerScene diggerScene{ levelData, this };
	diggerScene.LoadScene();
	m_currentPlayer = diggerScene.GetPlayer();

	if (m_currentPlayer)
	{
		if (auto* score = m_currentPlayer->GetComponent<PointsComponent>())
			score ->AddScore(m_currentScore);


		if (auto* health = m_currentPlayer->GetComponent<HealthComponent>())
		{
			health->Health(m_currentLives);
		}
	}
}
void dae::DiggerSceneManager::InitSound() const
{
	ServiceLocator::RegisterSounSystem(std::make_unique<SDLSoundSystem>());
	ServiceLocator::GetSoundSystem().AddSound("Data/Resources/DeathSound.wav");
	ServiceLocator::GetSoundSystem().AddSound("Data/Resources/piano2.wav");
}

void dae::DiggerSceneManager::InitInput()
{
	//controls
	InputManager::GetInstance().BindKeyboardCommand(SDL_SCANCODE_F1,
		InputManager::TriggerType::IsDownThisFrame,
		std::make_unique<SkipToNextLevelCommand>(this));

	InputManager::GetInstance().BindKeyboardCommand(SDL_SCANCODE_F2
		, InputManager::TriggerType::IsDownThisFrame
		, std::make_unique<MuteSoundCommand>());
}

void dae::DiggerSceneManager::Notify(GameEvent event, GameObject*  )
{
	if (event == GameEvent::AllEmeraldsCollected)
	{
		if (m_currentPlayer)
		{
			if (auto* score = m_currentPlayer->GetComponent<PointsComponent>())
				m_currentScore = score->GetScore();
			if (auto* health = m_currentPlayer->GetComponent<HealthComponent>())
				m_currentLives = health->GetLives();
		}

		SceneManager::GetInstance().SetPendingAction([this]() { LoadNextLevel(); });
	}
	if (event == GameEvent::PlayerDied)
	{
		SceneManager::GetInstance().SetPendingAction([this]() { ResetCurrentLevel(); });
	}
}
